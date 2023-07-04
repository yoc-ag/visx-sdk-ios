(function () {
    var isIOS = (/iphone|ipad|ipod/i).test(window.navigator.userAgent);
    if (isIOS && typeof console === 'undefined') {
        console = {};
        console.log = function (log) {
            var iframe = document.createElement('iframe');
            iframe.setAttribute('src', 'ios-log: ' + log);
            document.documentElement.appendChild(iframe);
            iframe.parentNode.removeChild(iframe);
            iframe = null;
        };
        console.debug = console.info = console.warn = console.error = console.groupCollapsed = console.groupEnd = console.log;
    }
}());
(function () {
    var mraid = window.mraid = {};
    var mraid_bridge = window.mraid_bridge = {};
    window.open = function(url) {mraid.open(url)}
    //////////////////////////////////////////////////////////////////////////////////////
    var VERSION = mraid.VERSION = '3.0';
    var APIVERSION = '2.0';
    // Placeholder, to be filled on Content Injection
    window.MRAID_ENV;

    var STATES = mraid.STATES = {
        LOADING: 'loading',
        DEFAULT: 'default',
        EXPANDED: 'expanded',
        RESIZED: 'resized',
        HIDDEN: 'hidden'
    };
    var EVENTS = mraid.EVENTS = {
        /** MRAID 3.0 Events */
        ERROR: 'error',
        READY: 'ready',
        SIZECHANGE: 'sizeChange',
        STATECHANGE: 'stateChange',
        EXPOSURECHANGE: 'exposureChange',
        AUDIOVOLUMECHANGE: 'audioVolumeChange',
        VIEWABLECHANGE: 'viewableChange',
        /** non-MRAID 3.0 Events */
        SUCCESS: 'success',
        WARNING: 'warning',
        VISXONSCROLL: 'visxOnScroll',
        VISXSTICKYISCLOSED: 'visxStickyIsClosed',
        VISXSTICKYISDISPLAYED: 'visxStickyIsDisplayed'
    };
    var PLACEMENT_TYPES = mraid.PLACEMENT_TYPES = {
        INLINE: 'inline',
        INTERSTITIAL: 'interstitial'
    };
    var FEATURES = mraid.FEATURES = {
        SMS: 'sms',
        TEL: 'tel',
        CALENDAR: 'calendar',
        VIDEO: 'inlineVideo',
        PICTURE: 'storePicture'
    };
    var supports = {
        'sms': false,
        'tel': false,
        'calendar': false,
        'storePicture': true,
        'inlineVideo': true
    };
    var expandProperties = {
        width: -1,
        height: -1,
        useCustomClose: false,
        isModal: true
    };
    var orientationProperties = {
        allowOrientationChange: false,
        forceOrientation: "none"
    };
    var currentAppOrientationProperties = {
        locked: true,
        orientation: "none"
    };
    var resizeProperties = {
        width: -1,
        height: -1,
        customClosePosition: 'top-right',
        offsetX: 0,
        offsetY: 0,
        allowOffscreen: false
    };
    var stickyProperties = {
        width: 0,
        height: 0,
        threshold: 50,
        position: 'auto',
        mode: 'auto'
    };
    var listeners = {};
    var state = STATES.LOADING;
    var isViewable = false;
    var screenSize = {
        width: -1,
        height: -1
    };
    var defaultPosition = {
        x: 0,
        y: 0,
        width: -1,
        height: -1
    };
    var isMediationAdView = false;
    var density = 1;
    var currentPosition = {
        x: 0,
        y: 0,
        width: -1,
        height: -1
    };
    var maxSize = {
        width: -1,
        height: -1
    };
    var absoluteSize = {
        x: 0,
        y: 0,
        width: 0,
        height: 0
    };
    var placementEffect = '';
    var webViewDimension = {
        width: 0,
        height: 0
    };
    var viewportDimension = {
        width: 0,
        height: 0
    };
    var volumePercentage = null;
    var placementType = PLACEMENT_TYPES.INLINE;

    var location = {
        lat: -1,
        lon: -1,
        type: -1,
        accuracy: -1,
        lastFix: -1,
        ipservice: -1
    };
    var startingTimeInSeconds = 0;
    var isUniversalAd = false;
    var canUseScrollEvent = false;
    var EventListeners = function (event) {
        this.event = event;
        this.count = 0;
        var listeners = {};
        this.add = function (func) {
            var id = String(func);
            if (!listeners[id]) {
                listeners[id] = func;
                this.count++;
            }
        };
        this.remove = function (func) {
            var id = String(func);
            if (listeners[id]) {
                listeners[id] = null;
                delete listeners[id];
                this.count--;
                return true;
            } else {
                return false;
            }
        };
        this.removeAll = function () {
            for (var id in listeners) {
                if (listeners.hasOwnProperty(id)) this.remove(listeners[id]);
            }
        };
        this.broadcast = function (args) {
            for (var id in listeners) {
                if (listeners.hasOwnProperty(id)) listeners[id].apply({}, args);
            }
        };
        this.toString = function () {
            var out = [event, ':'];
            for (var id in listeners) {
                if (listeners.hasOwnProperty(id)) out.push('|', id, '|');
            }
            return out.join('');
        };
    };
    var broadcastEvent = function () {
        var args = new Array(arguments.length);
        var l = arguments.length;
        for (var i = 0; i < l; i++) args[i] = arguments[i];
        var event = args.shift();
        if (listeners[event]) listeners[event].broadcast(args);
    };
    var contains = function (value, array) {
        for (var i in array) {
            if (array[i] === value) return true;
        }
        return false;
    };
    var stringify = function (obj) {
        if (typeof obj === 'object') {
            var out = [];
            if (obj.push) { // Array.
                for (var p in obj) out.push(obj[p]);
                return '[' + out.join(',') + ']';
            } else { // Other object.
                for (var p in obj) out.push("'" + p + "': " + obj[p]);
                return '{' + out.join(',') + '}';
            }
        } else return String(obj);
    };

    function executeNativeCall(command) {
        var call = 'mraid://' + command;
        var key, value;
        var isFirstArgument = true;
        for (var i = 1; i < arguments.length; i += 2) {
            key = arguments[i];
            value = arguments[i + 1];
            if (value === null) continue;
            if (isFirstArgument) {
                call += '?';
                isFirstArgument = false;
            } else {
                call += '&';
            }
            call += key + '=' + encodeURI(value);
        }
        window.webkit.messageHandlers.nativeapp.postMessage(call);
    };

    //////////////////////////////////////////////////////////////////////
    //MARK: MRAID Methods
    //////////////////////////////////////////////////////////////////////
    mraid.getVersion = function () {
        return mraid.VERSION;
    };

    mraid.getVisxApiVersion = function () {
        return APIVERSION;
    };

    mraid.addEventListener = function (event, listener) {
        if (!event || !listener) {
            broadcastEvent(EVENTS.ERROR, 'Both event and listener are required.', 'addEventListener');
        } else if (!contains(event, EVENTS)) {
            broadcastEvent(EVENTS.ERROR, 'Unknown MRAID event: ' + event, 'addEventListener');
        } else {
            if (!listeners[event]) listeners[event] = new EventListeners(event);
            listeners[event].add(listener);
            if (event == EVENTS.VOLUMECHANGE) {
                executeNativeCall('enableVolumeControl', 'setting', 'true');
            }
        }
    };

    mraid.removeEventListener = function (event, listener) {
        if (!event) {
            broadcastEvent(EVENTS.ERROR, 'Event is required.', 'removeEventListener');
            return;
        }
        if (listener) {
            // If we have a valid event, we'll try to remove the listener from it.
            var success = false;
            if (listeners[event]) {
                success = listeners[event].remove(listener);
            }
            // If we didn't have a valid event or couldn't remove the listener from the event, broadcast an error and return early.
            if (!success) {
                broadcastEvent(EVENTS.ERROR, 'Listener not currently registered for event.', 'removeEventListener');
                return;
            }
        } else if (!listener && listeners[event]) {
            listeners[event].removeAll();
        }
        if (listeners[event] && listeners[event].count === 0) {
            listeners[event] = null;
            delete listeners[event];
        }
    };

    mraid.open = function (URL) {
        executeNativeCall('open', 'url', encodeURI(URL));
    };

    mraid.close = function () {
        executeNativeCall('close');
    };

    mraid.useCustomClose = function (shouldUseCustomClose) {
        broadcastEvent(EVENTS.ERROR, 'UseCustomClose has been deprecated, and will be ignored.', 'useCustomClose');
    };

    mraid.unload = function () {
        executeNativeCall('unload');
    }

    mraid.expand = function (URL) {
        executeNativeCall('expand', 'w', expandProperties.width, 'h', expandProperties.height);
    };

    mraid.isViewable = function () {
        return isViewable;
    };

    mraid.playVideo = function (data) {
        executeNativeCall('playVideo', 'url', data);
    };

    mraid.resize = function () {
        executeNativeCall('resize',
                          'width', resizeProperties.width,
                          'height', resizeProperties.height,
                          'offsetX', resizeProperties.offsetX,
                          'offsetY', resizeProperties.offsetY,
                          'allowOffscreen', resizeProperties.allowOffscreen);
    };

    mraid.storePicture = function (url) {
        executeNativeCall('storePicture', 'url', url);
    };

    mraid.createCalendarEvent = function (data) {
        broadcastEvent(EVENTS.ERROR, 'createCalendarEvent not supported', 'createCalendarEvent');
    };

    //////////////////////////////////////////////////////////////////////
    //MARK: MRAID Properties
    //////////////////////////////////////////////////////////////////////
    mraid.supports = function (feature) {
        if (supports[feature]) {
            return true;
        } else {
            return false;
        }
    };

    mraid.getPlacementType = function () {
        return placementType;
    };

    mraid.getOrientationProperties = function () {
        var properties = {
            allowOrientationChange: orientationProperties.allowOrientationChange,
            forceOrientation: orientationProperties.forceOrientation,
        };
        return properties;
    };

    mraid.setOrientationProperties = function (properties) {
        executeNativeCall('setOrientationProperties',
                          'allowOrientationChange', orientationProperties.allowOrientationChange,
                          'forceOrientation', orientationProperties.forceOrientation);
    };

    mraid.getCurrentAppOrientation = function () {
        return currentAppOrientationProperties;
    };

    mraid.getCurrentPosition = function () {
        executeNativeCall('getCurrentPosition');
        return currentPosition;
    };

    mraid.getDefaultPosition = function () {
        return defaultPosition;
    };

    mraid.getState = function () {
        return state;
    };

    mraid.getExpandProperties = function () {
        var properties = {
            width: expandProperties.width,
            height: expandProperties.height,
            useCustomClose: false,
            isModal: expandProperties.isModal
        };
        return properties;
    };

    mraid.setExpandProperties = function (properties) {
        expandProperties.width = properties['width'];
        expandProperties.height = properties['height'];
        expandProperties.useCustomClose = properties['useCustomClose'];
        expandProperties.isModal = properties['isModal'];
    };

    mraid.getMaxSize = function () {
        return maxSize;
    };

    mraid.getScreenSize = function () {
        return screenSize;
    };

    mraid.getResizeProperties = function () {
        var properties = {
            width: resizeProperties.width,
            height: resizeProperties.height,
            offsetX: resizeProperties.offsetX,
            offsetY: resizeProperties.offsetY,
            customClosePosition: resizeProperties.customClosePosition,
            allowOffscreen: resizeProperties.allowOffscreen
        };
        return properties;
    };

    mraid.setResizeProperties = function (properties) {
        resizeProperties.width = properties['width']
        resizeProperties.height = properties['height']
        resizeProperties.offsetX = properties['offsetX']
        resizeProperties.offsetY = properties['offsetY']
        resizeProperties.allowOffscreen = properties['allowOffscreen']
    };

    mraid.getLocation = function () {
        var currentTime = Math.floor(Date.now() / 1000);
        var timeInSeconds = currentTime - startingTimeInSeconds;
        location.lastFix = timeInSeconds;
        return location;
    };

    //////////////////////////////////////////////////////////////////////
    //MARK: Javascript functions that are called from native code
    //////////////////////////////////////////////////////////////////////
    mraid_bridge.fireEventSizeChange = function (val) {
        console.log('Ad Size changed to: ' + stringify(val));
        broadcastEvent(EVENTS.SIZECHANGE, val.width, val.height);
    }

    mraid_bridge.fireEventViewable = function (val) {
        console.log("Viewable(" + val + ")");
        isViewable = val;
        console.log('Set isViewable to ' + stringify(val));
        broadcastEvent(EVENTS.VIEWABLECHANGE, isViewable);
    }

    mraid_bridge.fireEventError = function (val) {
        broadcastEvent(EVENTS.ERROR, val);
    }

    mraid_bridge.fireEventSuccess = function (val) {
        broadcastEvent(EVENTS.SUCCESS, val);
    }

    mraid_bridge.fireEventReady = function () {
        broadcastEvent(EVENTS.READY);
    }

    mraid_bridge.fireEventWarning = function (val) {
        broadcastEvent(EVENTS.WARNING, val);
    }

    mraid_bridge.fireEventStateChange = function (val) {
        if (state === STATES.LOADING) {
            console.log('Native SDK initialized.');
        }
        state = val;
        console.log("State was changed state = " + state);
        broadcastEvent(EVENTS.STATECHANGE, state);
    }

    mraid_bridge.fireScrollEvent = function (initialScrollViewHeight, currentScrollViewHeight, currentScrollPosition, scrollPositionDelta) {
        broadcastEvent(EVENTS.VISXONSCROLL, initialScrollViewHeight, currentScrollViewHeight, currentScrollPosition, scrollPositionDelta);
    };

    mraid_bridge.fireCloseEventOfCompanion = function () {
        broadcastEvent(EVENTS.VISXSTICKYISCLOSED);
    }

    mraid_bridge.fireOpenEventOfCompanion = function () {
        broadcastEvent(EVENTS.VISXSTICKYISDISPLAYED);
    }

    mraid_bridge.fireAudioChangeEvent = function (properties) {
        volumePercentage = properties;
        broadcastEvent(EVENTS.AUDIOVOLUMECHANGE, volumePercentage);
    };

    mraid_bridge.fireExposureEvent = function (properties) {
        mraid.exposureChange(properties.exposedPercentage,
            properties.visibleRectangle,
            properties.occlusionRectangles);
    };

    mraid_bridge.setCurrentAppOrientation = function (orientation, locked) {
        currentAppOrientationProperties.orientation = orientation;
        currentAppOrientationProperties.locked = locked == 1 ? true : false;
    }

    mraid_bridge.setIsMediationAdView = function (val) {
        isMediationAdView = val;
    };

    mraid_bridge.setAbsoluteSize = function (val) {
        console.log('Set absolute size to: ' + stringify(val));
        absoluteSize.width = val['width'];
        absoluteSize.height = val['height'];
    };

    mraid_bridge.setPlacementType = function (val) {
        console.log('Set placementType to ' + stringify(val));
        placementType = val;
    }

    mraid_bridge.setMaxSize = function (val) {
        console.log('Setting maximum size the ad can expand to ' + stringify(val));
        maxSize.width = val['width'];
        maxSize.height = val['height'];
    }

    mraid_bridge.setDensity = function (val) {
        density = val;
    }

    mraid_bridge.setScreenSize = function (val) {
        console.log('Set screenSize to ' + stringify(val));
        screenSize.width = val['width'];
        screenSize.height = val['height'];
    }

    mraid_bridge.setDefaultPosition = function (val) {
        console.log('Setting default position ' + stringify(val));
        defaultPosition.x = val['x'];
        defaultPosition.y = val['y'];
        defaultPosition.width = val['width'];
        defaultPosition.height = val['height'];
    }

    mraid_bridge.setCurrentPosition = function (val) {
        currentPosition.x = val['x'];
        currentPosition.y = val['y'];
        currentPosition.width = val['width'];
        currentPosition.height = val['height'];
    }

    mraid_bridge.setLocation = function (val) {
        console.log('Setting location ' + stringify(val));
        location.lat = val['lat'];
        location.lon = val['lon'];
        location.type = val['type'];
        location.accuracy = val['accuracy'];
        startingTimeInSeconds = val['lastFix'];
    };

    mraid_bridge.modifyMraidSupports = function (sms, tel, storedPic, calendar) {
        supports["sms"] = sms;
        supports["tel"] = tel;
        supports["storePicture"] = storedPic;
        supports["calendar"] = calendar;
    };

    mraid_bridge.getOrientationProperties = function () {
        var properties = mraid.getOrientationProperties();
        var jsonStr = JSON.stringify(properties);
        return jsonStr;
    };

    mraid_bridge.setIsUniversalAd = function (val) {
        isUniversalAd = val;
    };

    mraid_bridge.setCanUseOnScrollEvent = function (val) {
        canUseScrollEvent = val;
    };

    //////////////////////////////////////////////////////////////////////
    //MARK: Visx Methods
    //////////////////////////////////////////////////////////////////////
    mraid.visxShowAdvertisementMessageAbove = function (htmlData) {
        executeNativeCall('visxShowMessageAbove', 'htmlData', btoa(htmlData));
    };

    mraid.visxShowAdvertisementMessageBelow = function (htmlData) {
        executeNativeCall('visxShowMessageBelow', 'htmlData', btoa(htmlData));
    };

    mraid.visxShowBrandedTakeoverSticky = function (html, width, height, animationStyle, direction) {
        executeNativeCall('visxShowBrandedTakeoverSticky', 'html', btoa(html), 'stickyWidth', width, 'stickyHeight', height, 'animationStyle', animationStyle, 'direction', direction);
    }

    mraid.visxHideBrandedTakeoverSticky = function (animationStyle, direction) {
        executeNativeCall('visxhidebrandedtakeoversticky', 'animationStyle', animationStyle, 'direction', direction);
    }

    mraid.visxSetPlacementDimension = function (webViewWidth, webViewHeight, viewportWidth, viewportHeight) {
        webViewDimension.width = webViewWidth;
        webViewDimension.height = webViewHeight;
        viewportDimension.width = viewportWidth;
        viewportDimension.height = viewportHeight;
        executeNativeCall('visxSetPlacementDimension', 'webViewWidth', webViewWidth, 'webViewHeight', webViewHeight, 'viewportWidth', viewportWidth, 'viewportHeight', viewportHeight);
    };

    mraid.visxSetPlacementEffect = function (effect, webViewWidth, webViewHeight, viewportWidth, viewportHeight) {
        placementEffect = effect;
        webViewDimension.width = webViewWidth;
        webViewDimension.height = webViewHeight;
        viewportDimension.width = viewportWidth;
        viewportDimension.height = viewportHeight;
        executeNativeCall('visxSetPlacementEffect', 'effect', effect, 'webViewWidth', webViewWidth, 'webViewHeight', webViewHeight, 'viewportWidth', viewportWidth, 'viewportHeight', viewportHeight);
    };
    
    mraid.visxGetPlacementEffect = function () {
        return placementEffect;
    };

    mraid.visxGetPlacementDimension = function () {
        return {
            webViewDimension: {
                width: webViewDimension.width,
                height: webViewDimension.height
            },
            viewportDimension: {
                width: viewportDimension.width,
                height: viewportDimension.height
            }
        }
    };

    mraid.visxClosePlacement = function () {
        broadcastEvent(EVENTS.WARNING, 'visxClosePlacement() is deprecated use mraid.close()');
        executeNativeCall('close')
    };

    mraid.visxClearPlacement = function () {
        broadcastEvent(EVENTS.WARNING, 'visxClearPlacement() is deprecated use mraid.unload()');
        executeNativeCall('unload');
    };

    mraid.visxRefreshPlacement = function () {
        executeNativeCall('visxRefreshPlacement')
    };

    mraid.visxVideoFinished = function () {
        executeNativeCall('visxVideoFinished');
    };

    mraid.visxVideoWasCanceled = function () {
        executeNativeCall('visxVideoWasCanceled');
    };

    mraid.visxVideoWasMuted = function () {
        executeNativeCall('visxVideoWasMuted');
    };

    mraid.visxVideoWasUnmuted = function () {
        executeNativeCall('visxVideoWasUnmuted');
    };

    mraid.visxEnableOnScrollEvent = function () {
        executeNativeCall('visxEnableOnScrollEvent');
    };

    mraid.visxIsUniversalAd = function () {
        return isUniversalAd;
    }
    
    mraid.visxToSticky = function() {
        executeNativeCall('visxToSticky',
                          'width', stickyProperties.width,
                          'height', stickyProperties.height,
                          'threshold', stickyProperties.threshold,
                          'position', stickyProperties.position,
                          'mode', stickyProperties.mode);
    };
    
    mraid.visxGetStickyProperties = function() {
        var properties = {
            'width': stickyProperties.width,
            'height': stickyProperties.height,
            'threshold': stickyProperties.threshold,
            'position': stickyProperties.position,
            'mode': stickyProperties.mode
        };
        return properties;
    };
    
    mraid.visxSetStickyProperties = function(properties) {
        stickyProperties.width = properties.width;
        stickyProperties.height = properties.height;
        stickyProperties.threshold = properties.threshold;
        stickyProperties.position = properties.position;
        stickyProperties.mode = properties.mode;
    };
    
    mraid.visxCloseSticky = function () {
        executeNativeCall('visxCloseSticky')
    };

    //////////////////////////////////////////////////////////////////////
    //MARK: NON MRAID Properties
    //////////////////////////////////////////////////////////////////////
    mraid.exposureChange = function (exposedPercentage, visibleRectangle, occlusionRectangles) {
        if (exposedPercentage == 0) {
            visibleRectangle = null;
        }
        broadcastEvent(EVENTS.EXPOSURECHANGE, exposedPercentage, visibleRectangle, occlusionRectangles);
    };

    mraid.getDensity = function () {
        return density;
    };

    mraid.getIsMediationAdView = function () {
        return isMediationAdView;
    };

    mraid.getAbsoluteScreenSize = function () {
        return absoluteSize;
    };

    mraid.getExposureChangeAvailability = function () {
        return true;
    };

    mraid.canUseOnScrollEvent = function () {
        return canUseScrollEvent;
    }

}());

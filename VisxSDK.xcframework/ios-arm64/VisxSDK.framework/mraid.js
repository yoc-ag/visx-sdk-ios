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
        'calendar': true,
        'storePicture': true,
        'inlineVideo': true
    };

    // External MRAID state: may be directly or indirectly modified by the ad JS.
    ////////////////////
    // Properties which define the behavior of an expandable ad.
    var expandProperties = {
        width: -1,
        height: -1,
        useCustomClose: false,
        isModal: true
    };

    // Properties wich control the orientation of an expandable and interstitial ad.
    var orientationProperties = {
        allowOrientationChange: false,
        forceOrientation: "none"
    };

    var currentAppOrientationProperties = {
        locked: true,
        orientation: "none"
    };

    // Properties which define the behavior of a resizeable ad.
    var resizeProperties = {
        width: -1,
        height: -1,
        customClosePosition: 'top-right',
        offsetX: 0,
        offsetY: 0,
        allowOffscreen: false
    };

    var listeners = {};
    // Internal MRAID state. Modified by the native SDK.
    // /////////////////////////////////////////////
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

    var isExposureChangeEnabled = true;
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

    mraid_bridge.fireEvent = function (type) {
        var args = Array.prototype.slice.call(arguments);
        args.shift();
        switch (type) {
            case 'error':
                broadcastEvent(EVENTS.ERROR, args);
                break;
            case 'success':
                broadcastEvent(EVENTS.SUCCESS, args);
                break;
            case 'ready':
                broadcastEvent(EVENTS.READY);
                break;
            case 'change':
                var properties = args[0];
                for (var p in properties) {
                    if (properties.hasOwnProperty(p)) {
                        var handler = changeHandlers[p];
                        handler(properties[p]);
                    }
                }
                break;
        }

    };

    // ////////////////////////////////////////////////////////////////////////////////////////////////
    // / SUPPORT DYNAMIC VALUES CHANGING FOR MRAID 2.0 //
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

    mraid_bridge.fireExposureEvent = function (properties) {
        mraid.exposureChange(properties.exposedPercentage,
            properties.visibleRectangle,
            properties.occlusionRectangles);
    };

    mraid_bridge.fireAudioChangeEvent = function (properties) {
        volumePercentage = properties;
        broadcastEvent(EVENTS.AUDIOVOLUMECHANGE, volumePercentage);
    };

    mraid_bridge.setCurrentAppOrientation = function (orientation, locked) {
        currentAppOrientationProperties.orientation = orientation;
        currentAppOrientationProperties.locked = locked == 1 ? true : false;
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
    var clone = function (obj) {
        if (obj === null) return null;
        var f = function () { };
        f.prototype = obj;
        return new f();
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
    var trim = function (str) {
        return str.replace(/^\s+|\s+$/g, '');
    };
    var concatArguments = function (eventName, data) {
        var args = [eventName];
        for (obj in data) {
            args = args.concat([obj, data[obj]]);
        }
        return args;
    };
    // Functions that will be invoked by the native SDK whenever a "change" event occurs.
    var changeHandlers = {
        //TODO: This part can be improved. The VisxJavascriptBridge can communicate directly now
        state: function (val) {
            if (state === STATES.LOADING) {
                console.log('Native SDK initialized.');
            }
            state = val;
            console.log("state was changed state=" + state);
            broadcastEvent(EVENTS.STATECHANGE, state);
        },
        viewable: function (val) {
            console.log("mraid.js function viewable(" + val + ")");
            isViewable = val;
            console.log('Set isViewable to ' + stringify(val));
            broadcastEvent(EVENTS.VIEWABLECHANGE, isViewable);
        },
        placementType: function (val) {
            console.log('Set placementType to ' + stringify(val));
            placementType = val;
        },
        screenSize: function (val) {
            console.log('Set screenSize to ' + stringify(val));
            for (var key in val) {
                if (val.hasOwnProperty(key)) screenSize[key] = val[key];
            }
        },
        success: function (val) {
            console.log("fire success broadcast with " + val);
            broadcastEvent(EVENTS.SUCCESS, val);
        },
        defaultPosition: function (val) {
            console.log('Setting default position ' + stringify(val));
            defaultPosition['x'] = val['x'];
            defaultPosition['y'] = val['y'];
            defaultPosition['width'] = val['width'];
            defaultPosition['height'] = val['height'];
        },
        currentPosition: function (val) {
//            console.log('Setting current position ' + stringify(val));
            currentPosition['x'] = val['x'];
            currentPosition['y'] = val['y'];
            currentPosition['width'] = val['width'];
            currentPosition['height'] = val['height'];
        },
        maxSize: function (val) {
            console.log('Setting maximum size the ad can expand to ' + stringify(val));
            maxSize['width'] = val['width'];
            maxSize['height'] = val['height'];
        },
        size: function (val) {
            console.log('Ad Size changed to: ' + stringify(val));
            broadcastEvent(EVENTS.SIZECHANGE, val.width, val.height);
        },
        expandProperties: function (val) {
            for (var key in val) {
                if (val.hasOwnProperty(key)) expandProperties[key] = val[key];
            }
        }
    };

    var validate = function (obj, validators, action, merge) {
        if (!merge) {
            // Check to see if any required properties are missing.
            if (obj === null) {
                broadcastEvent(EVENTS.ERROR, 'Required object not provided.', action);
                return false;
            } else {
                for (var i in validators) {
                    if (validators.hasOwnProperty(i) && obj[i] === undefined) {
                        broadcastEvent(EVENTS.ERROR, 'Object is missing required property: ' + i + '.', action);
                        return false;
                    }
                }
            }
        }
        for (var prop in obj) {
            var validator = validators[prop];
            var value = obj[prop];
            if (validator && !validator(value)) { // Failed validation.
                broadcastEvent(EVENTS.ERROR, 'Value of property ' + prop + ' is invalid.', action);
                return false;
            }
        }
        return true;
    };

    var expandPropertyValidators = {
        width: function (v) {
            return !isNaN(v) && v >= 0;
        },
        height: function (v) {
            return !isNaN(v) && v >= 0;
        },
        useCustomClose: function (v) {
            return (typeof v === 'boolean');
        }
    };

    var orientationPropertyValidators = {
        forceOrientation: function (v) {
            return (v == 'portrait' || v == 'landscape' || v == 'none');
        },
        allowOrientationChange: function (v) {
            return (typeof v === 'boolean');
        }
    };

    var resizePropertyValidators = {
        width: function (v) {
            return !isNaN(v) && v >= 0;
        },
        height: function (v) {
            return !isNaN(v) && v >= 0;
        },
        offsetX: function (v) {
            return !isNaN(v);
        },
        offsetY: function (v) {
            return !isNaN(v);
        },
        customClosePosition: function (v) {
            return 'top-right';
        },
        allowOffscreen: function (v) {
            return (typeof v === 'boolean');
        }
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

    mraid.close = function () {
        executeNativeCall('close');
        console.log("executeNativeCall('close')");
    };

    mraid.visxShowAdvertisementMessageAbove = function (htmlData) {
        executeNativeCall('visxshowmessageabove', 'htmlData', btoa(htmlData));
    };

    mraid.visxShowAdvertisementMessageBelow = function (htmlData) {
        executeNativeCall('visxshowmessagebelow', 'htmlData', btoa(htmlData));
    };

    mraid.visxShowBrandedTakeoverSticky = function (html, width, height, animationStyle, direction) {
        executeNativeCall('visxshowbrandedtakeoversticky', 'html', btoa(html), 'stickyWidth', width, 'stickyHeight', height, 'animationStyle', animationStyle, 'direction', direction);
    }

    mraid.visxHideBrandedTakeoverSticky = function (animationStyle, direction) {
        executeNativeCall('visxhidebrandedtakeoversticky', 'animationStyle', animationStyle, 'direction', direction);
    }

    mraid.getDensity = function () {
        console.log("mraid.getDensity() density=" + density);
        return density;
    };

    mraid.setDensity = function (dens) {
        //TODO: Move to mraid_bridge? It's not meant to be changed by the client
        if (dens <= 0) {
            broadcastEvent(EVENTS.ERROR, 'Density can\'t be set to a value <= 0', 'setDensity');
            return;
        }
        density = dens;
        console.log("mraid.setDensity() successful changed density=" + density);
    };

    mraid.setIsMediationAdView = function (val) {
        isMediationAdView = val;
    };

    mraid.getIsMediationAdView = function () {
        return isMediationAdView;
    };

    mraid.expand = function (URL) {
        if (state == STATES.DEFAULT || state == STATES.RESIZED) {
            var args = ['expand'];
            if (expandProperties.width >= 0 && expandProperties.height >= 0) {
                args = args.concat(['w', expandProperties.width, 'h', expandProperties.height]);
            } else {
                broadcastEvent(EVENTS.ERROR, 'expandProperties invalid.', 'expand');
                return;
            }
            args = args.concat(['expandPosition', 'center']);
            if (URL && URL != "") {
                args = args.concat(['url', URL]);
            }
            executeNativeCall.apply(this, args);
        } else {
            broadcastEvent(EVENTS.ERROR, 'Ad can only be expanded from the default state.', 'expand');
        }
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

    mraid.getOrientationProperties = function () {
        var properties = {
            allowOrientationChange: orientationProperties.allowOrientationChange,
            forceOrientation: orientationProperties.forceOrientation,
        };
        return properties;
    };

    mraid.resize = function () {
        if (state == STATES.EXPANDED) {
            broadcastEvent(EVENTS.ERROR, 'Ad can only be resized from the default state.', 'resize');
        } else {
            var args;
            args = ['resize'];
            args = args.concat(['width', resizeProperties.width, 'height', resizeProperties.height]);
            args = args.concat(['offsetX', resizeProperties.offsetX, 'offsetY', resizeProperties.offsetY]);
            args = args.concat(['customClosePosition', resizeProperties.customClosePosition, 'allowOffscreen', resizeProperties.allowOffscreen]);
            //TODO: Remove 'animated' from native part, not part of the specs and animation is not required here
            args = args.concat(['animated', 'true']);
            executeNativeCall.apply(this, args);
        }
    };

    mraid.getResizeProperties = function () {
        var properties = {
            width: resizeProperties.width,
            height: resizeProperties.height,
            offsetX: resizeProperties.offsetX,
            offsetY: resizeProperties.offsetY,
            customClosePosition: "top-right",
            allowOffscreen: resizeProperties.allowOffscreen
        };
        return properties;
    };

    mraid.getPlacementType = function () {
        return placementType;
    };

    mraid.getState = function () {
        return state;
    };

    mraid.getCurrentAppOrientation = function () {
        return currentAppOrientationProperties;
    };

    mraid.getAbsoluteScreenSize = function () {
        return absoluteSize;
    };

    mraid.getVersion = function () {
        return mraid.VERSION;
    };

    mraid.getDefaultPosition = function () {
        return defaultPosition;
    };

    mraid.getCurrentPosition = function () {
        executeNativeCall('getcurrentposition');
        return currentPosition;
    };

    mraid.getMaxSize = function () {
        return maxSize;
    };

    mraid.isViewable = function () {
        return isViewable;
    };

    mraid.getScreenSize = function () {
        return screenSize;
    };

    mraid.getExposureChangeAvailability = function () {
        return true;
    };

    mraid.storePicture = function (url) {
        if (url === null || url.match(/^ *$/) !== null) {
            broadcastEvent(EVENTS.ERROR, 'Url request cannot be empty.', 'storePicture');
        } else {
            //TODO: Check if it requires camel case
            executeNativeCall('storepicture', 'url', url);
        }
    };

    mraid.createCalendarEvent = function (data) {
        var jsonStr = JSON.stringify(data);
        //TODO: Check if it requires camel case
        executeNativeCall('createcalendarevent', 'data', jsonStr);
    };

    mraid.playVideo = function (data) {
        if (!supports[FEATURES.VIDEO]) {
            broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'playVideo');
        } else if (!data) {
            broadcastEvent(EVENTS.ERROR, 'Request must specify a url.', 'playVideo');
        } else if (typeof data == 'string') {
            executeNativeCall('playVideo', 'url', data);
        } else if (typeof data == 'object') {
            executeNativeCall.apply(this, concatArguments('playVideo', data));
        }
    };

    mraid.supports = function (feature) {
        if (supports[feature]) {
            return true;
        } else {
            return false;
        }
    };

    mraid.setAbsoluteSize = function (width, height) {
        absoluteSize.width = width;
        absoluteSize.height = height;
    };

    mraid.exposureChange = function (exposedPercentage, visibleRectangle, occlusionRectangles) {
        if (exposedPercentage == 0) {
            visibleRectangle = null;
        }
        broadcastEvent(EVENTS.EXPOSURECHANGE, exposedPercentage, visibleRectangle, occlusionRectangles);
    };

    mraid.visxSetPlacementDimension = function (webviewWidth, webviewHeight, viewportWidth, viewportHeight) {
        //TODO: webViewDimension obj requires a camelcased V on javascript, let's make it consistent in native part as well
        webViewDimension.width = webviewWidth;
        webViewDimension.height = webviewHeight;
        viewportDimension.width = viewportWidth;
        viewportDimension.height = viewportHeight;
        executeNativeCall('visxSetPlacementDimension', 'webviewWidth', webviewWidth, 'webviewHeight', webviewHeight, 'viewportWidth', viewportWidth, 'viewportHeight', viewportHeight);
    };

    mraid.visxSetPlacementEffect = function (effect, webviewWidth, webviewHeight, viewportWidth, viewportHeight) {
        placementEffect = effect;
        webViewDimension.width = webviewWidth;
        webViewDimension.height = webviewHeight;
        viewportDimension.width = viewportWidth;
        viewportDimension.height = viewportHeight;
        executeNativeCall('visxSetPlacementEffect', 'effect', effect, 'webviewWidth', webviewWidth, 'webviewHeight', webviewHeight, 'viewportWidth', viewportWidth, 'viewportHeight', viewportHeight);
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
        executeNativeCall('visxClosePlacement')
    };

    mraid.visxClearPlacement = function () {
        executeNativeCall('visxClearPlacement')
    };

    mraid.visxRefreshPlacement = function () {
        if (mraid.getState() == STATES.DEFAULT || STATES.HIDDEN) {
            executeNativeCall('visxRefreshPlacement')
        } else {
            broadcastEvent(EVENTS.ERROR, 'visxRefreshPlacement requires state to be default or hidden.', 'visxRefreshPlacement');
        }
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

    mraid.setIsUniversalAd = function (val) {
        isUniversalAd = val;
    }

    mraid.visxIsUniversalAd = function () {
        return isUniversalAd;
    }

    mraid.open = function (URL) {
        if (!URL) {
            broadcastEvent(EVENTS.ERROR, 'URL is required.', 'open');
        } else {
            executeNativeCall('open', 'url', encodeURI(URL));
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

    mraid.setExpandProperties = function (properties) {
        if (validate(properties, expandPropertyValidators, 'setExpandProperties', true)) {
            var desiredProperties = ['width', 'height', 'useCustomClose'];
            var length = desiredProperties.length;
            for (var i = 0; i < length; i++) {
                var propname = desiredProperties[i];
                if (properties.hasOwnProperty(propname)) expandProperties[propname] = properties[propname];
            }
        }
    };

    mraid.setOrientationProperties = function (properties) {
        if (validate(properties, orientationPropertyValidators, 'setOrientationProperties', true)) {
            var desiredProperties = ['allowOrientationChange', 'forceOrientation'];
            var length = desiredProperties.length;
            for (var i = 0; i < length; i++) {
                var propname = desiredProperties[i];
                if (properties.hasOwnProperty(propname)) {
                    orientationProperties[propname] = properties[propname];
                }
            }
        }
        var args = ['setorientationproperties'];
        args = args.concat(['allowOrientationChange', orientationProperties.allowOrientationChange]);
        args = args.concat(['forceOrientation', orientationProperties.forceOrientation]);

        executeNativeCall.apply(this, args);
    };

    mraid.setResizeProperties = function (properties) {
        if (validate(properties, resizePropertyValidators, 'setResizeProperties', true)) {
            var desiredProperties = ['width', 'height', 'offsetX', 'offsetY', 'customClosePosition', 'allowOffscreen'];
            var length = desiredProperties.length;
            for (var i = 0; i < length; i++) {
                var propname = desiredProperties[i];
                if (properties.hasOwnProperty(propname)) resizeProperties[propname] = properties[propname];
            }
        }
    };

    mraid.useCustomClose = function (shouldUseCustomClose) {
        broadcastEvent(EVENTS.ERROR, 'UseCustomClose has been deprecated, and will be ignored.', 'useCustomClose');
    };

    //TODO: Not a MRAID function, forceOrientation will be handled in setOrientationProperties
    mraid.forceOrientation = function (orientation) {
        executeNativeCall('forceorientation', 'orientation', orientation);
    };

    mraid.setCloseButtonPosition = function (value) {
        //MRAID 3.0 enforces close button to be top-right
        //TODO: Remove from VisxCommand, VisxMRAdViewController, VisxMRAdViewDisplayController, VisxMRAdView
        //Having a static property for this is enough
        value = "top-right";
        executeNativeCall('setCloseButtonPosition', 'position', value);
    };

    mraid.getLocation = function () {
        var currentTime = Math.floor(Date.now() / 1000);
        var timeInSeconds = currentTime - startingTimeInSeconds;
        location.lastFix = timeInSeconds;
        return location;
    };

    mraid_bridge.setLocation = function (lat, lon, type, accuracy, lastFix) {
        if (lat != 0 && lon != 0) {
            location.lat = lat;
            location.lon = lon;
            location.type = type;
            location.accuracy = accuracy;
            startingTimeInSeconds = lastFix;
        }
    };

    mraid.unload = function () {
        executeNativeCall('visxUnloadCreative');
    }

}());

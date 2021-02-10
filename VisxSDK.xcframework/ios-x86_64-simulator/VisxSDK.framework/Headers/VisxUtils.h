//
//  VisxUtils.h
//  VisxSDK
//
//  Created by Balint Gyemant & Rob Siwek on 13.08.12.
//
//  Copyright 2012 YOC AG. All rights reserved.
//

#import <VisxSDK/VisxAdSize.h>
#import <VisxSDK/VisxPlacementTypes.h>

typedef NS_ENUM(NSInteger, VisxAccurateNetworkReachability) {
    VisxNetworkReachabilityOffline,
    VisxNetworkReachabilityMobile2G,
    VisxNetworkReachabilityMobile3G,
    VisxNetworkReachabilityMobile4G,
    VisxNetworkReachabilityMobileWiFi
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    VisxAdViewAnimationTypeNone = 0,
    VisxAdViewAnimationTypeSlideFromTop = 1,
    VisxAdViewAnimationTypeSlideFromBottom = 2,
    VisxAdViewAnimationTypeSlideFromLeft = 3,
    VisxAdViewAnimationTypeSlideFromRight = 4,
    VisxAdViewAnimationTypeFadeIn = 5
} VisxAdViewAnimationType;

@interface VisxUtils : NSObject
VisxAccurateNetworkReachability VisxGetInternetReachabilityWithHostName( NSString *hostName);
VisxAccurateNetworkReachability VisxGetAccurateNetworkReachability(void);

UIInterfaceOrientation VisxDeviceOrientation(void);
/// Helper for retrieving CGSizes from VisxAdSizes
CGSize CGSizeFromVisxAdSize(VisxAdSize size);
/// Returns the status bar orientation.
UIInterfaceOrientation VisxInterfaceOrientation(void);
/// Returns a Boolean value that indicates whether the receiver is the key window for the application.
UIWindow *VisxKeyWindow(void);
/// Returns the frame rectangle defining the area of the status bar.
CGFloat VisxStatusBarHeight(void);
/// Returns the frame rectangle defining the area of the application w/o status bar.
CGRect VisxApplicationFrame(void);
/// Returns the actual screen bounds.
CGRect VisxScreenBounds(void);
///Returns current position offset from left edge of the rectangle defining getMaxSize()
CGRect VisxCurrentPosition(UIView *view);
/// Transforms banner view related to its placementType
CGRect VisxScaleFrameForPlacementEffect(CGRect frame, VisxPlacementEffect placementEffect);
/// Prepare banner view for animationType
CGRect VisxPrepareViewForAnimation(UIView *view, VisxAdViewAnimationType animation);
/// Helper to determine placementType
NSString *VisxPlacementTypeForAdSize(VisxAdSize size);
/// Returns a NSDictionary created from a URL-Parameter-String.
NSDictionary *VisxDictionaryFromQueryString(NSString *query);
/// Clean log w/o timestamps
void VisxLog(NSString *format, ...);
/// UIColor from CSS HEX
UIColor *colorWithHexString(NSString* hex);
/// Enable view animations to particular point
void VisxAnimateAdViewToPoint(UIView *view, CGPoint point, float duration);
/// Returns the natural scale factor associated with the screen
CGFloat VisxScaleScreen(void);
/// Prints out the response or error
void VisxResponseLog(id response, NSError *error);
/// Returns width of the main screen bounds
NSString *VisxPhysicalWidth(void);
/// Returns height of the main screen bounds
NSString *VisxPhysicalHeight(void);
/// Returns the natural scale factor associated with the screen in string format
NSString *VisxPxRatio(void);
/// Checks if the NSdata is valid
NSData *VisxDataContent(NSData *data);
/// Checks if data is valid JSON format
BOOL VisxValidateJSON(NSData *data);
/// Retruns NSString from NSData
NSString *VisxDataToString(NSData *data);
/// Creates and returns NSDictionary from NSData
NSDictionary *VisxCreateDictionary(NSData *data);
/// Creates and returns error NSDictionary from NSData
NSDictionary *VisxCreateErrorDictionary(NSData *data);
/// Returns NSString of the placement effect of the creative
NSString *VisxPlacementEffectToString(VisxPlacementEffect effect);
/// Returns VisxPlacementEffect from NSSString
VisxPlacementEffect EffectStringToVisxPlacementEffect(NSString *param);
/// Checks if VisxMRAdView exist as a subview
BOOL VisxCheckSubViewExist(UIView *adView);
/// Returns placement type from placement effect
VisxPlacementType VisxPlacementEffectToPlacementType(VisxPlacementEffect effect);
/// Returns placement effect from placement type
VisxPlacementEffect VisxPlacementTypeToDefaultEffect(VisxPlacementType type);
/// Returns default placement effect from visxAdSize type
VisxPlacementEffect VisxPlacementEffectForAdSize(VisxAdSize size);
/// Returns creative Id from google response
NSString *VisxGetGoogleAUID(NSString *serverParameter);
/// Returns publisher app domian from google response
NSString *VisxGetGoogleAppDomain(NSString *serverParameter);
/// Returns visxAdSize from google response
VisxAdSize VisxGetGoogleAdSize(NSString *serverParameter);
/// Returns width of the creative from google response
CGFloat VisxGetGoogleWidth(NSString *serverParameter);
/// Returns height of the creative from google response
CGFloat VisxGetGoogleHeight(NSString *serverParameter);
/// Returns NSString const for notification center
NSString *VisxGoogleAdUpdatedViewString(void);
/// Returns the top most view controller
UIViewController *topMostController(void);
/// Returns the visible view currently on the screen
UIView *visibleView(void);
/// Returns width and height of the scrollview in which creative is inserted
CGRect getScrollViewSize(UIViewController *controllerView);
/// Returns max size of the view in which creative can be displayed
CGRect maxSize(BOOL isInterstital, BOOL isUniversal, CGSize originalSize, CGFloat containerWidth, CGRect anchorViewFrame);
/// Returns advertising label from NSData
NSString *VisxGetAdvertisingLabel(NSData *data);
/// Returns location data (lat, lon, type, accuracy, lastfix and ipservice)
NSMutableDictionary *VisxLocationProperties(void);
/// Returns boolean value if html string is valid
BOOL isHtmlString(NSString *htmlString);
/// Returns current app orientation
NSDictionary *setCurrentAppOrientation(void);
@end

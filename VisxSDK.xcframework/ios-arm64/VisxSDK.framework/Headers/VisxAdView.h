//
//  VisxAdView.h
//  VisxSDK
//
//  Created by Balint Gyemant & Rob Siwek on 06.07.12.
//
//  Copyright 2012 YOC AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <VisxSDK/VisxAdSize.h>
#import <WebKit/WebKit.h>

#define kVisxAdViewTag 999998

@class VisxAdViewWrapper;
@class Mediation;

@protocol VisxAdViewDelegate;

/// Like in newSDK2 and not like above
@interface VisxAdView : UIView <WKUIDelegate, WKNavigationDelegate>
/// delegate for the VisxAdViewDelegate. Should implemented in publisher app.
@property(nonatomic, weak) id <VisxAdViewDelegate> delegate;
/// determines the animationDuration for ads in seconds
@property(nonatomic, assign) CGFloat animationDuration;
/// webview of the creative
@property (nonatomic, strong) WKWebView *webView;
/// creative content as a NSString
@property(nonatomic, copy) NSString *adViewContent;
/// creative content as a NSData
@property(nonatomic, copy) NSData *adContentData;
/// determines whether the type is an inline or interstitial @see VisxPlacementTypes.h
@property (readonly, assign) VisxPlacementType placementType;
/// determines wether the placement effect is banner, understitial, undferstitial mini, sticky or interstitial. @see VisxPlacementTypes.h
@property (nonatomic, assign) VisxPlacementEffect placementEffect;
/// determines whether the YOC TAG communication uses SSL encryption (YES) or not (NO). Default setting is NO.
@property (nonatomic) BOOL enableSSL;
// ** Add from newSDK2 **
@property (getter = locationServicesEnabled) BOOL enableLocationServices;
// Boolean flag for creatives with mini understitial placementEffect
@property BOOL isMiniUnderstitial;
// Boolean flag for creatives with understitial placementEffect
@property BOOL isUnderstitial;
/// CGFloat property for the container width, which containes the creative.
@property CGFloat parentViewWidth;
/// when using mediation this is the current mediation adapter
@property (nonatomic) id currentMediationAdapter;
/// determines if the visxAdView is mediation
@property (nonatomic) BOOL isMediationAdView;
/// determines if the creative is universal
@property (nonatomic) BOOL isUniversal;
/// visxAdView wrapper for diplaying adView and advertising labels
@property (nonatomic) VisxAdViewWrapper *adViewWrapper;
/// height of the adView
@property CGFloat adHeight;
/// advertising label
@property (nonatomic, copy) NSString *advLabel;
/// CGRect which holds resized dimensions of the visxAdView
@property CGRect resizedViewRect;

/// Initializes visxAdView
/// @param auid creative ID
/// @param domain publisher domain
/// @param adViewDelegate adViewDelegate, viewcontroller which is implementing VisxAdViewDelegate protocol
/// @param adSize dimensions of the creative. see VisxAdSize.h
/// @param universal Boolean flag which determines if the creative is universal or not
- (id)initWithAdUnit:(NSString *)auid appDomain:(NSString *)domain delegate:(id<VisxAdViewDelegate>)adViewDelegate size:(VisxAdSize)adSize isUniversal:(BOOL)universal;

/// Initializes simple banner visxAdView
/// @param adSize dimensions of the creative. see VisxAdSize.h
/// @param auid creative ID
/// @param domain publisher domain
/// @param container UIView container where creative will be displayed
- (instancetype)initSimpleBannerWithFixedSize:(VisxAdSize)adSize adUnit:(NSString *)auid appDomain:(NSString *)domain container:(UIView *)container;

/// Initializes universal visxAdView
/// @param auid creative ID
/// @param domain publisher domain
/// @param container UIView container where creative will be displayed
/// @param adSize dimensions of the creative. see VisxAdSize.h
/// @param anchorView UIScrollView in which container is placed, this value can be nil
- (instancetype)initUniversalAdWithAdUnit:(NSString *)auid appDomain:(NSString *)domain container:(UIView *)container size:(VisxAdSize)adSize anchorView:(UIScrollView *)anchorView;

/// Creates advertising label above the creative, this method is optional
/// @param label input paramater as a NSString, it could be regular string or html one.
- (void)advertisingLabelText:(NSString *)label;

/// Creates advertising label above the creative, this method is optional, if not used, BOOL useLabel is false
/// @param useLabel Boolean flag which determines if external advertising label should be used or not.
- (void)useExternalAdvertisingLabel:(BOOL)useLabel;

/// Loads an ad for the visxAdView object with the given custom targeting parameters.
/// The custom targeting parameters are only set once at the first time. For any additional
/// reload the given Dictionary params are ignored.
/// Use for reload the method load instead of loadWithCustomTargetingParameters:.
/// @param params the custom targeting in app
- (void)loadWithCustomTargetingParameters:(NSDictionary *)params;

///  Loads an ad for the visxAdView object. If this method is called for the first ad request, the custom targeting is set to empty.
///  Otherwise for any additional reload the first custom targeting parameters are taken (empty or values from loadWithCustomTargetingParameters:).
///  @see VisxAdView#loadWithCustomTargetingParameters
- (void)load;

/// This method adds creative in UITableView
/// @param tableView tableview in which we are adding the creative
/// @param cell tableview cell in which we are adding the creative
/// @param row indexpath.row of the cell
- (void)showCreativeInTableview:(UITableView *)tableView withCell:(UITableViewCell *)cell withRow:(NSInteger)row;

/// This methods returns creative view. It must be used together with container view.
/// @param scroll scrollview in which we are adding the creative
- (UIView *)getCreativeInScrollview:(UIScrollView *)scroll;

/// This methods updates Understitial creative position while scrolling in UITableView or UIScrollView.
- (void)scrollViewDidScroll;

/// This method creates reactive scrolling effect.
- (void)reactiveScrollDidScroll:(UIScrollView *)scroll;

/// Releases the visxAdView. Should only be called, if the visxAdView is no longer needed.
- (void)deallocAdView;

///  Refreshes the creative
- (void)refreshPlacement;

/// Provides the version of the SDK currently in use. @return Version of the SDK
+ (NSString*)getSdkVersion;

/// When using mediation this method is called whenever google banner view is received
/// @param bannerView google mediation banner view
- (void)adViewDidReceiveAd:(UIView *)bannerView;

/// When using mediation this method is called if error is occured when trying to get google banner view.
/// @param bannerView google mediation banner view
/// @param error error detail information about the error that occurred
- (void)adView:(UIView *)bannerView didFailToReceiveAdWithError:(NSError *)error;

/// Method wich resets UI elemnts
- (void)resetUIElements;

/// Presents the interstitial from the default view controller.
- (void)showInterstitial;

/// Sets custom color for Mystery creative, default is transparent.
/// @param color UIColor
- (void)setInterstitialBackgroundColor:(UIColor *)color;

/// Presents the reactive scrolling creative from the default view controller.
- (UIView *)getReactiveCreative;

/// Presents the interstitial from the custom view controller.
/// @param controller viewcontroller which will present interstitial creative
- (void)showInterstitialFromViewController:(UIViewController *)controller;

/// Returns boolean for creative placementEffect
- (BOOL)isInterstitial;

/// Returns boolean for creative placementEffect changed
- (BOOL)isPlacementChanged;

/// Method which will resize visxAdView to fit newly fetched mediation creative
/// @param webViewDimensions webView dimension
/// @param viewportDimensions viewPort dimension
- (void)mediationResizeView:(CGSize)webViewDimensions andViewPort:(CGSize)viewportDimensions;
@end

@protocol VisxAdViewDelegate <NSObject>
@required
/// ViewController for presenting VisxAdView
- (UIViewController *)viewControllerForPresentingVisxAdView;

/// Delegate method is called when the ad content is received for the first time and the VisxAdView has finished rendering the content.
/// @param visxAdView visxAdView with content
/// @param effect placement effect of the creative
- (void)visxAdViewDidInitialize:(VisxAdView *)visxAdView withPlacementEffect:(VisxPlacementEffect)effect;

@optional
/// Delegate method is called when the ad content is received. Was implemented to support Custom-Events in Mediation
/// @param visxAdView visxAdView with data
- (void)visxAdDidReceivedAd:(VisxAdView *)visxAdView;

/// Delegate method is called when the ad view is loaded and will be presented to screen
/// @param visxAdView visxAdView with data
- (void)visxAdWillPresentScreen:(VisxAdView *)visxAdView;

/// Delegate method is called when the ad view is loaded and its on screen
/// @param visxAdView visxAdView with data
- (void)visxAdDidPresentScreen:(VisxAdView *)visxAdView;

/// Delegate method called when universal creative changes placement effect
/// @param visxAdView visxAdView with data
/// @param effect visxPlacement Effect
- (void)visxAdViewDidChangePlacementEffect:(VisxAdView *)visxAdView withPlacementEffect:(VisxPlacementEffect)effect;

/// Delegate method called when universal creative changes dimensions
/// @param visxAdView visxAdView with data
- (void)visxAdViewDidChangePlacementDimension:(VisxAdView *)visxAdView;

/// Delegate method is called when retrieving the ad content has failed for any reason and provides a detail error message.
/// @param visxAdView visxAdView the corresponding VisxAdView
/// @param error error detail information about the error that occurred
- (void)visxAdView:(VisxAdView *)visxAdView didFailWithError:(NSError *)error;

/// Delegate method is called when the ad content has been reloaded and VisxAdView has finished rendering the content.
/// @param visxAdView visxAdView with content
- (void)visxAdViewDidReload:(VisxAdView *)visxAdView;

/// Delegate method is called when the VisxAdView is about to be hidden by an internal web browser overlay.
/// @param visxAdView visxAdView which will be hidden.
- (void)visxAdWillHide:(VisxAdView *)visxAdView;

/// Delegate method is called when the VisxAdView has been hidden by an internal web browser overlay.
/// @param visxAdView visxAdView which has been hidden.
- (void)visxAdViewDidHide:(VisxAdView *)visxAdView;

/// Delegate method is called when the VisxAdView is about to be expanded.
/// @param visxAdView the expanding visxAdView
/// @param frame the new size of the frame
/// @param animated indicates whether the resize animation is animated
- (void)willExpandYocAd:(VisxAdView *)visxAdView toFrame:(CGRect)frame animated:(BOOL)animated;

/// Delegate method is called when the VisxAdView has been expanded.
/// @param visxAdView the visxAdView, which is expanded.
/// @param frame the new frame size of the visxAdView
- (void)didExpandYocAd:(VisxAdView *)visxAdView toFrame:(CGRect)frame;

/// Delegate method is called when the VisxAdView is about to resize its own frame.
/// @param frame the new frame size
/// @param animated indicates whether the resize animation will be animated
- (void)visxAdWillResize:(CGRect)frame animated:(BOOL)animated;

/// Delegate method is (optional) called, if the visxAdView will resize the own frame.
/// @param frame new frame size
/// @param animated the BOOL value indicates, whether the resize action is animated or not
/// deprecated in verison 2.0 (only for backward compability with old ads)
- (void)visxAdWillResizeToFrame:(CGRect)frame animated:(BOOL)animated;

/// Delegate method is called when the close button has been pressed and the ad is about to be closed.
/// @param visxAdView the visxAdView which will be closed.
- (void)visxAdWillClose:(VisxAdView *)visxAdView;

/// Delegate method is called when the ad has been closed.
/// @param visxAdView the visxAdView which is closed.
- (void)visxAdDidClose:(VisxAdView *)visxAdView;

/// Delegate method is called when the ad has been tapped.
/// @param visxAdView the visxAdView which is tapped.
- (void)visxAdWasTapped:(VisxAdView *)visxAdView;

/// Delegate method is (optional) called before showing a modal view controller.
/// @param visxAdView visxAdView the calling adView.
/// deprecated in version 2.0
/// @see VisxAdView#visxAdViewWillPresentModalViewController
- (void)appShouldSuspendForAd:(VisxAdView *)visxAdView;

/// Delegate method is (optional) called after dismissing a modal view controller.
/// @param visxAdView the origin visxAdView which called the modal view
/// deprecated in version 2.0
/// @see VisxAdView#visxAdViewWillDismissModalViewController
- (void)appShouldResumeFromAd:(VisxAdView *)visxAdView;

/// Delegate method is called when a modal view controller is about to be shown.
/// @param visxAdView the calling adView.
- (void)visxAdViewWillPresentModalViewController:(VisxAdView *)visxAdView;

/// Delegate method is called when a modal view controller has been dismissed.
/// @param visxAdView the VisxAdView which has originally opened the modal view
- (void)visxAdViewWillDismissModalViewController:(VisxAdView *)visxAdView;
@end

/// Protocol that needs to be implemented in mediation for understitial effect.
@protocol VisxUnderstitialScrollDelegate <NSObject>
/// Delegate method for registering listeners
/// @param visxAdView the VisxAdView used in mediation
- (void)registerScrollListener:(VisxAdView *)visxAdView;
/// Delegate method for unregistering listeners
- (void)unregisterScrollListener:(VisxAdView *)visxAdView;
@end

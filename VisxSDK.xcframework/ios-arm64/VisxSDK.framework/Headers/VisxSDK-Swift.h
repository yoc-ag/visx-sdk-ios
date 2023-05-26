#if 0
#elif defined(__arm64__) && __arm64__
// Generated by Apple Swift version 5.7.2 (swiftlang-5.7.2.135.5 clang-1400.0.29.51)
#ifndef VISXSDK_SWIFT_H
#define VISXSDK_SWIFT_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wduplicate-method-match"
#pragma clang diagnostic ignored "-Wauto-import"
#if defined(__OBJC__)
#include <Foundation/Foundation.h>
#endif
#if defined(__cplusplus)
#include <cstdint>
#include <cstddef>
#include <cstdbool>
#else
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#endif

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(ns_consumed)
# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
# define SWIFT_RELEASES_ARGUMENT
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if defined(__OBJC__)
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#endif
#if !defined(SWIFT_EXTERN)
# if defined(__cplusplus)
#  define SWIFT_EXTERN extern "C"
# else
#  define SWIFT_EXTERN extern
# endif
#endif
#if !defined(SWIFT_CALL)
# define SWIFT_CALL __attribute__((swiftcall))
#endif
#if defined(__cplusplus)
#if !defined(SWIFT_NOEXCEPT)
# define SWIFT_NOEXCEPT noexcept
#endif
#else
#if !defined(SWIFT_NOEXCEPT)
# define SWIFT_NOEXCEPT 
#endif
#endif
#if defined(__cplusplus)
#if !defined(SWIFT_CXX_INT_DEFINED)
#define SWIFT_CXX_INT_DEFINED
namespace swift {
using Int = ptrdiff_t;
using UInt = size_t;
}
#endif
#endif
#if defined(__OBJC__)
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import AVKit;
@import CoreFoundation;
@import Foundation;
@import ObjectiveC;
@import UIKit;
#endif

#endif
#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="VisxSDK",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif

#if defined(__OBJC__)

@interface AVPlayerViewController (SWIFT_EXTENSION(VisxSDK))
- (void)viewWillDisappear:(BOOL)animated;
@end


SWIFT_CLASS("_TtC7VisxSDK16LayoutConstraint")
@interface LayoutConstraint : NSLayoutConstraint
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

@class NSString;

@interface LayoutConstraint (SWIFT_EXTENSION(VisxSDK))
@property (nonatomic, readonly, copy) NSString * _Nonnull description;
@end


SWIFT_CLASS("_TtC7VisxSDK9Mediation")
@interface Mediation : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@class NSIndexPath;
@class VisxCollectionViewCell;

@interface UICollectionView (SWIFT_EXTENSION(VisxSDK))
- (VisxCollectionViewCell * _Nonnull)dequeueVisxCellFor:(NSIndexPath * _Nonnull)indexPath reuseIdentifier:(NSString * _Nonnull)reuseIdentifier SWIFT_WARN_UNUSED_RESULT;
@end




@class VisxTableViewCell;

@interface UITableView (SWIFT_EXTENSION(VisxSDK))
- (VisxTableViewCell * _Nonnull)dequeueVisxCellFor:(NSIndexPath * _Nonnull)indexPath reuseIdentifier:(NSString * _Nonnull)reuseIdentifier SWIFT_WARN_UNUSED_RESULT;
@end






enum VisxPlacementType : NSInteger;

SWIFT_CLASS("_TtC7VisxSDK10VisxAdSize")
@interface VisxAdSize : NSObject
- (nonnull instancetype)initWithAdSize:(CGSize)adSize type:(enum VisxPlacementType)type OBJC_DESIGNATED_INITIALIZER;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kSmartphoneBanner300x50;)
+ (VisxAdSize * _Nonnull)kSmartphoneBanner300x50 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kSmartphoneBanner300x75;)
+ (VisxAdSize * _Nonnull)kSmartphoneBanner300x75 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kSmartphoneBanner300x150;)
+ (VisxAdSize * _Nonnull)kSmartphoneBanner300x150 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kSmartphoneBanner320x50;)
+ (VisxAdSize * _Nonnull)kSmartphoneBanner320x50 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kBillboard970x250;)
+ (VisxAdSize * _Nonnull)kBillboard970x250 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kLeaderboard728x90;)
+ (VisxAdSize * _Nonnull)kLeaderboard728x90 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kPushdown970x90;)
+ (VisxAdSize * _Nonnull)kPushdown970x90 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kHalfpage300x600;)
+ (VisxAdSize * _Nonnull)kHalfpage300x600 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kPortrait300x1050;)
+ (VisxAdSize * _Nonnull)kPortrait300x1050 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kSkyscraper160x600;)
+ (VisxAdSize * _Nonnull)kSkyscraper160x600 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kUnderstitial320x480;)
+ (VisxAdSize * _Nonnull)kUnderstitial320x480 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kUnderstitial300x600;)
+ (VisxAdSize * _Nonnull)kUnderstitial300x600 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kMediumRectangle300x150;)
+ (VisxAdSize * _Nonnull)kMediumRectangle300x150 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kMediumRectangle300x250;)
+ (VisxAdSize * _Nonnull)kMediumRectangle300x250 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kUnderstitial300x250;)
+ (VisxAdSize * _Nonnull)kUnderstitial300x250 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kInterstitial1x1;)
+ (VisxAdSize * _Nonnull)kInterstitial1x1 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kInterstitial320x480;)
+ (VisxAdSize * _Nonnull)kInterstitial320x480 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kInterstitial300x600;)
+ (VisxAdSize * _Nonnull)kInterstitial300x600 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kStickyBanner300x50;)
+ (VisxAdSize * _Nonnull)kStickyBanner300x50 SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VisxAdSize * _Nonnull kStickyBanner320x50;)
+ (VisxAdSize * _Nonnull)kStickyBanner320x50 SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@class NSCoder;

SWIFT_CLASS("_TtC7VisxSDK10VisxAdView")
@interface VisxAdView : UIView <UIScrollViewDelegate>
@property (nonatomic) BOOL isMediationAdView;
@property (nonatomic) CGFloat adHeight;
@property (nonatomic, readonly, copy) NSString * _Nonnull adUnit;
@property (nonatomic) BOOL hasMessageAbove;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder SWIFT_UNAVAILABLE;
- (nonnull instancetype)initWithFrame:(CGRect)frame SWIFT_UNAVAILABLE;
@end




@protocol VisxAdViewDelegate;
@class UIScrollView;
@class UIViewController;
@class UIColor;
@class NSError;

@interface VisxAdView (SWIFT_EXTENSION(VisxSDK))
/// VisxAdView - Default initializer
- (nonnull instancetype)initWithAdUnit:(NSString * _Nonnull)adUnit appDomain:(NSString * _Nonnull)appDomain adViewDelegate:(id <VisxAdViewDelegate> _Nonnull)adViewDelegate adSize:(VisxAdSize * _Nonnull)adSize universal:(BOOL)universal;
/// VisxAdView - Adaptive banner initializer with dynamic size
- (nonnull instancetype)initWithAdUnit:(NSString * _Nonnull)adUnit appDomain:(NSString * _Nonnull)appDomain adViewDelegate:(id <VisxAdViewDelegate> _Nonnull)adViewDelegate;
/// VisxAdView - Fixed size banner initializer
- (nonnull instancetype)initWithAdUnit:(NSString * _Nonnull)adUnit appDomain:(NSString * _Nonnull)appDomain adSize:(VisxAdSize * _Nonnull)adSize container:(UIView * _Nonnull)container delegate:(id <VisxAdViewDelegate> _Nonnull)delegate SWIFT_DEPRECATED_MSG("Please use -> \"Default initializer\"");
/// VisxAdView - Universal ad initializer
- (nonnull instancetype)initWithAdUnit:(NSString * _Nonnull)adUnit appDomain:(NSString * _Nonnull)appDomain adSize:(VisxAdSize * _Nonnull)adSize container:(UIView * _Nonnull)container delegate:(id <VisxAdViewDelegate> _Nonnull)delegate anchorView:(UIScrollView * _Nullable)anchorView SWIFT_DEPRECATED_MSG("Please use -> \"Adaptive banner initializer with dynamic size\"");
/// Returns current VisxSDK version
- (NSString * _Nonnull)getSdkVersion SWIFT_WARN_UNUSED_RESULT;
/// Sets absolute position of the visible view where creative can be shown.
/// Note: Ad container is the UIView which is adding creative as a subview.
/// \param anchorX Absolute x position of ad container in which creative is added.
///
/// \param anchorY Absolute top y position of UIScrollView/UITableView.
///
/// \param anchorWidth Max width of the ad container.
///
/// \param anchorHeight Max height of the UIScrollView/UITableView.
///
- (void)setAnchorFrameWith:(double)anchorX :(double)anchorY :(double)anchorWidth :(double)anchorHeight;
/// Loads request
- (void)load;
/// Loads request with custom targeting parameters
- (void)loadWithCustomTargetingParametersWithParams:(NSDictionary<NSString *, NSString *> * _Nonnull)params;
/// Sets advertising label above the creative
- (void)advertisingLabelTextWithLabel:(NSString * _Nonnull)label;
/// Deallocates current VisxAdView
- (void)deallocAdView;
/// Returns visxAdView
- (UIView * _Nonnull)getCreativeInScrollviewWithScroll:(UIScrollView * _Nonnull)scroll SWIFT_WARN_UNUSED_RESULT;
/// Returns reactive visxAdView
- (UIView * _Nullable)getReactiveCreative SWIFT_WARN_UNUSED_RESULT;
/// Presents interstitial ad from current UIViewController
- (void)showInterstitial;
/// Presents interstitial ad from specifed UIViewController
- (void)showInterstitialFromViewControllerWithController:(UIViewController * _Nonnull)controller;
/// AdView scrollDidScroll method enables understitial effect
- (void)scrollViewDidScroll:(UIScrollView * _Nonnull)scrollView;
/// Check if placement type is interstitial
- (BOOL)isInterstitial SWIFT_WARN_UNUSED_RESULT;
/// Set interstitial background color, clear is default
- (void)setInterstitialBackgroundColorWithColor:(UIColor * _Nonnull)color;
/// Used only when header bidding is enabled, renderAdIfHeaderBiddingEnabled() needs to be called to show creative
- (void)renderAdIfHeaderBiddingEnabled;
- (void)adViewDidReceiveAdWithBannerView:(UIView * _Nonnull)bannerView;
- (void)didFailToReceiveAdWithErrorWithBannerView:(UIView * _Nonnull)bannerView error:(NSError * _Nonnull)error;
@end



enum VisxPlacementEffect : NSInteger;

SWIFT_PROTOCOL("_TtP7VisxSDK18VisxAdViewDelegate_")
@protocol VisxAdViewDelegate
- (UIViewController * _Nonnull)viewControllerForPresentingVisxAdView SWIFT_WARN_UNUSED_RESULT;
- (void)visxAdViewDidInitializeWithVisxAdView:(VisxAdView * _Nonnull)visxAdView effect:(enum VisxPlacementEffect)effect;
@optional
- (void)visxAdRequestStartedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)visxAdResponseReceivedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView price:(double)price currency:(NSString * _Nonnull)currency;
- (void)visxAdFailedWithErrorWithVisxAdView:(VisxAdView * _Nonnull)visxAdView message:(NSString * _Nonnull)message code:(NSInteger)code;
- (void)visxAdViewSizeChangeWithVisxAdView:(VisxAdView * _Nonnull)visxAdView width:(CGFloat)width height:(CGFloat)height;
- (void)visxAdViewEffectChangeWithVisxAdView:(VisxAdView * _Nonnull)visxAdView effect:(enum VisxPlacementEffect)effect;
- (void)visxAdViewClosedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)visxAdViewClickedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)visxLandingPageOpened;
- (void)appShouldSuspendForAdWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)appShouldResumeFromAdWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)visxAdVideoFinishedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)visxAdInterstitialWillBeClosedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
- (void)visxAdInterstitialClosedWithVisxAdView:(VisxAdView * _Nonnull)visxAdView;
@end


SWIFT_CLASS_NAMED("VisxCollectionViewCell")
@interface VisxCollectionViewCell : UICollectionViewCell
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull visxCellIdentifier;)
+ (NSString * _Nonnull)visxCellIdentifier SWIFT_WARN_UNUSED_RESULT;
- (void)showAdWithAdView:(VisxAdView * _Nonnull)adView;
- (nonnull instancetype)initWithFrame:(CGRect)frame OBJC_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC7VisxSDK18VisxMediationUtils")
@interface VisxMediationUtils : NSObject
/// Returns the top most view controller
+ (UIViewController * _Nullable)topMostController SWIFT_WARN_UNUSED_RESULT;
/// Returns visxAdSize from mediation response
+ (VisxAdSize * _Nonnull)visxGetAdSizeFromStringWithServerParameter:(NSString * _Nonnull)serverParameter SWIFT_WARN_UNUSED_RESULT;
/// Returns visxAdSize from Xandr size
+ (VisxAdSize * _Nonnull)visxGetXandrAdSizeWithCgSize:(CGSize)cgSize SWIFT_WARN_UNUSED_RESULT;
/// Returns NSString const for notification center
+ (NSString * _Nonnull)visxGoogleAdUpdatedViewString SWIFT_WARN_UNUSED_RESULT;
/// Returns creative Id from mediation response
+ (NSString * _Nonnull)visxGetAUIDFromStringWithServerParameter:(NSString * _Nonnull)serverParameter SWIFT_WARN_UNUSED_RESULT;
/// Returns publisher app domian from mediation response
+ (NSString * _Nonnull)visxGetAppDomainFromStringWithServerParameter:(NSString * _Nonnull)serverParameter SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

typedef SWIFT_ENUM(NSInteger, VisxPlacementEffect, open) {
  VisxPlacementEffectBanner = 0,
  VisxPlacementEffectUnderstitial = 1,
  VisxPlacementEffectUnderstitialMini = 2,
  VisxPlacementEffectSticky = 3,
  VisxPlacementEffectInterstitial = 4,
};

typedef SWIFT_ENUM(NSInteger, VisxPlacementType, open) {
  VisxPlacementTypeInline = 0,
  VisxPlacementTypeInterstitial = 1,
};


SWIFT_CLASS_NAMED("VisxSDKManager")
@interface VisxSDKManager : NSObject
+ (VisxSDKManager * _Nonnull)sharedInstance SWIFT_WARN_UNUSED_RESULT;
- (void)initializeSDK;
- (NSString * _Nonnull)SDKVersion SWIFT_WARN_UNUSED_RESULT;
- (void)setRemoteConfigSiteIdWith:(NSString * _Nonnull)siteId;
- (void)setAppStoreUrlWithUrl:(NSString * _Nonnull)url;
- (void)setSharedNamespaceWithUuid:(NSString * _Nonnull)namespace_;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS_NAMED("VisxTableViewCell")
@interface VisxTableViewCell : UITableViewCell
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull visxCellIdentifier;)
+ (NSString * _Nonnull)visxCellIdentifier SWIFT_WARN_UNUSED_RESULT;
- (void)showAdWithAdView:(VisxAdView * _Nonnull)adView tableView:(UITableView * _Nonnull)tableView;
- (nonnull instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString * _Nullable)reuseIdentifier SWIFT_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)aDecoder SWIFT_UNAVAILABLE;
@end

#endif
#if defined(__cplusplus)
#endif
#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop
#endif

#else
#error unsupported Swift architecture
#endif

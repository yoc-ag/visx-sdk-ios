//
//  VisxAdSize.h
//  VisxSDK
//
//  Created by Balint Gyemant & Rob Siwek on 13.08.12.
//
//  Copyright 2012 YOC AG. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VisxSDK/VisxPlacementTypes.h>
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    CGSize adSize;
    VisxPlacementType type;
} VisxAdSize;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///Horizontal
/// IAB Smartphone Banner size 300x50 || type: "inline"
extern VisxAdSize const kSmartphoneBanner300x50;
/// IAB Smartphone Banner size 300x75 || type: "inline"
extern VisxAdSize const kSmartphoneBanner300x75;
/// IAB Smartphone Banner size 300x150 || type: "inline"
extern VisxAdSize const kSmartphoneBanner300x150;
/// IAB Smartphone Banner size 320x50 || type: "inline"
extern VisxAdSize const kSmartphoneBanner320x50;
/// IAB Billboard size 970x250 || type: "inline"
extern VisxAdSize const kBillboard970x250;
/// IAB Leaderboard size 728x90 || type: "inline"
extern VisxAdSize const kLeaderboard728x90;
/// IAB Pushdown size 970x90 || type: "inline"
extern VisxAdSize const kPushdown970x90;

///Vertical
/// IAB Halfpage size 300x600 || type: "inline"
extern VisxAdSize const kHalfpage300x600;
/// IAB Portrait size 300x1050 || type: "inline"
extern VisxAdSize const kPortrait300x1050;
/// IAB Skyscraper size 160x600 || type: "inline"
extern VisxAdSize const kSkyscraper160x600;
/// YOC Understitial 320x480 || type: "inline"
extern VisxAdSize const kUnderstitial320x480;
/// YOC Understitial 300x600 || type: "inline"
extern VisxAdSize const kUnderstitial300x600;

///Tiles
/// IAB Medium Rectangle size 300x150 || type: "inline"
extern VisxAdSize const kMediumRectangle300x150;
/// IAB Medium Rectangle size 300x250 || type: "inline"
extern VisxAdSize const kMediumRectangle300x250;
/// YOC Understitial (Mini) 300x250 || type: "inline"
extern VisxAdSize const kUnderstitial300x250;

///Interstitials (Fullscreen Overlays) & Sticky
///YOC Fullscreen Interstitial 1x1 || type: "interstitial"
extern VisxAdSize const kInterstitial1x1;
/// YOC Fullscreen Interstitial 320x480 || type: "interstitial"
extern VisxAdSize const kInterstitial320x480;
/// YOC Fullscreen Interstitial 300x600 || type: "interstitial"
extern VisxAdSize const kInterstitial300x600;
/// YOC Sticky Banner size 300x50 || type: "inline"
extern VisxAdSize const kStickyBanner300x50;
/// YOC Sticky Banner size 320x50 || type: "inline"
extern VisxAdSize const kStickyBanner320x50;





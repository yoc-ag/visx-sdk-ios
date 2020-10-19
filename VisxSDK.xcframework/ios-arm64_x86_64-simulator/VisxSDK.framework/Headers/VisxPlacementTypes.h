//
//  VisxPlacementTypes.h
//  VisxSDK
//
//  Created by Aleksandar Jovanov on 6/18/20.
//  Copyright © 2020 YOC AG. All rights reserved.
//

#ifndef VisxPlacementTypes_h
#define VisxPlacementTypes_h


#endif /* VisxPlacementTypes_h */
//VisxPlacementTypes solely mraid.getPlacementType()
typedef NS_ENUM (NSInteger, VisxPlacementType){
    VisxPlacementTypeInline = 0,
    VisxPlacementTypeInterstitial = 1
};

typedef NS_ENUM (NSInteger, VisxPlacementEffect) {
    VisxPlacementEffectBanner = 0,
    VisxPlacementEffectUnderstitial = 1,
    VisxPlacementEffectUnderstitialMini = 2,
    VisxPlacementEffectSticky = 3,
    VisxPlacementEffectInterstitial = 4
};

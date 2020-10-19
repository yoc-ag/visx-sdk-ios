//
//  VisxSDKManager.h
//  VisxSDK
//
//  Created by Aleksandar Jovanov on 4/30/20.
//  Copyright © 2020 YOC AG. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

enum {
    VisxSDKAppWillResignActive = 0,
    VisxSDKAppDidBecomeActive = 1,
};
typedef NSUInteger VisxSDKAppState;

@protocol VisxSDKManagerDelegate <NSObject>

@required
-(void)didChangedAppState:(VisxSDKAppState)state;
@end

@interface VisxSDKManager : NSObject

+ (VisxSDKManager *)sharedInstance;
-(void)addObserversForApplicationState;
-(void)removeObserversForApplicationState;
-(VisxSDKAppState)getAppState;
-(void)initializeSDK;
-(void)setAppStoreUrl:(NSString *)url;

@property (nonatomic, strong) id<VisxSDKManagerDelegate> delegate;
@property (nonatomic, assign) VisxSDKAppState appState;
@end

NS_ASSUME_NONNULL_END

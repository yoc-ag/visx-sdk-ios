//
//  MediationModel.h
//  VisxSDK
//
//  Created by Stefan Markovic on 8/7/20.
//  Copyright © 2020 YOC AG. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VisxSDK/Parameter.h>

NS_ASSUME_NONNULL_BEGIN

@interface Mediation: NSObject

@property (nonatomic, copy) NSString *className;
@property (nonatomic, copy) NSString *adunit;
@property (nonatomic, copy) NSArray<NSNumber *> *sizes;

- (instancetype)initWithClassName:(NSString *)className
                           adunit:(NSString *)adunit
                            sizes:(NSArray<NSNumber *>*)sizes;
@end

NS_ASSUME_NONNULL_END

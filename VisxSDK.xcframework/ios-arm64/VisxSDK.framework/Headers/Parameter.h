//
//  Parameter.h
//  VisxSDK
//
//  Created by Stefan Markovic on 8/7/20.
//  Copyright © 2020 YOC AG. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Parameter: NSObject

@property (nonatomic, copy) NSString *adunit;
@property (nonatomic, copy) NSArray<NSNumber *> *sizes;

- (instancetype)initWithAdUnit:(NSString *)adUnit sizes:(NSArray<NSNumber *> *)sizes;

@end

NS_ASSUME_NONNULL_END

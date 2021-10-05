//
//  MediationLoader.h
//  VisxSDK
//
//  Created by Stefan Markovic on 31.8.21.
//  Copyright © 2021 YOC AG. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MediationLoader : NSObject

@property (nonatomic, strong) NSString *adapterName;

- (instancetype)initWithName:(NSString *)name;
- (id)getClassByName;

@end

NS_ASSUME_NONNULL_END

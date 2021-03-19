//
//  VisxTableViewCell.h
//  VisxSDK
//
//  Created by Stefan Markovic on 3.3.21.
//  Copyright © 2021 YOC AG. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VisxAdView.h"

NS_ASSUME_NONNULL_BEGIN

@interface VisxTableViewCell: UITableViewCell

/// Method which will return visxTableViewCell
/// @param adView VisxAdView
/// @param tableView in which creative is added
/// @param row number of the row where creative is displayed
+ (VisxTableViewCell *)cellForAdView:(VisxAdView *)adView
                         inTableView:(UITableView *)tableView
                             withRow:(NSInteger)row;

@end

NS_ASSUME_NONNULL_END

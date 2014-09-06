//
//  CBPTodayDataSource.h
//  CBPWordPressExample
//
//  Created by Karl Monaghan on 06/09/2014.
//  Copyright (c) 2014 Crayons and Brown Paper. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CBPWordPressTodayPost;

@interface CBPTodayDataSource : NSObject <UITableViewDataSource>
- (void)loadPosts:(NSInteger)count completion:(void (^)(NSError* error)) handler;
- (CBPWordPressTodayPost *)postAtIndex:(NSInteger)index;
@end


/*******************************************************
 * Copyright (C) 2011-2012 Converser contact@converser.io
 *
 * This file is part of the Converser iOS SDK.
 *
 * This code may not be copied and/or distributed without the express
 * permission of Converser. Please email contact@converser.io for
 * all redistribution and reuse enquiries.
 *******************************************************/

#import <UIKit/UIKit.h>
#import "VGBaseViewController.h"

@class VGConversationEngine;
@class VGConversationPane;
@class VGConversationItemViewController;
@class VGFeedbackViewController;

typedef enum {
    VGConversationResultCancelled,
    VGConversationResultSent,
    VGConversationResultFailed,
} VGConversationResultType;

typedef enum {
    VGCallNumberActionType,
    VGVisitURLActionType
} VGActionType;

@protocol VGConversationItemViewControllerDelegate <NSObject>

@optional
-(void) conversationController:(VGConversationItemViewController *)controller
         didFinishWithResult:(VGConversationResultType)result
                       error:(NSError *)error;

-(BOOL) conversationController:(VGConversationItemViewController *)controller
                willTakeAction:(VGActionType)action
                     withParam:(NSString*)param;
@end


@interface VGConversationItemViewController : VGBaseViewController <UITableViewDelegate, UITableViewDataSource> {
    VGConversationPane *_conversationPane;
    VGConversationEngine *_engine;
}

@property (strong, nonatomic) IBOutlet UIImageView *fullScreenBackgroundImageView;
@property (strong, nonatomic) IBOutlet UIImageView *backgroundImageView;
@property (strong, nonatomic) IBOutlet UIImageView *buttonsBackgroundImageView;
@property (strong, nonatomic) IBOutlet UITableView *contentTableView;
@property (unsafe_unretained, nonatomic) IBOutlet UIView *buttonsView;
@property (nonatomic, assign) id<VGConversationItemViewControllerDelegate> delegate;
@property (readonly) NSString *conversationTrackerId;
@property (nonatomic, strong) VGConversationEngine *engine;


-(IBAction)cancelButtonTapped:(id)sender;
-(id)initWithConversationTrackerId:(NSString *)conversationTrackerId;
-(void)updateUI;

+(void)setSingleButtonImageName:(NSString*)name;
+(void)setFirstButtonImageName:(NSString*)name;
+(void)setLastButtonImageName:(NSString*)name;
+(void)setOtherButtonImageName:(NSString*)name;

@end

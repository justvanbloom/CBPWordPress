//
//  VGSSRatingPickerViewController.h
//  SSToolkit
//
//  Created by Sam Soffes on 2/3/11.
//  Copyright 2011 Sam Soffes. All rights reserved.
//
//  Modified by Barry Scott

#import "VGBaseViewController.h"

@class VGSSRatingPickerScrollView;
@class VGSSRatingPicker;
@class VGSSTextField;
@class VGSSTextView;
@class VGConversationEngine;
@class VGRatingFeedbackViewController;

typedef enum {
    VGFeedbackTypeRating,
    VGFeedbackTypeQuestion
} VGFeedbackType;

typedef enum {
    VGFeedbackResultCancelled,
    VGFeedbackResultSent,
    VGFeedbackResultFailed,
} VGFeedbackResultType;

@protocol VGRatingFeedbackViewControllerDelegate <NSObject>

@optional

-(void) ratingFeedbackController:(VGRatingFeedbackViewController *)controller
             didFinishWithResult:(VGFeedbackResultType)result
                           error:(NSError *)error;

@end


@interface VGRatingFeedbackViewController : VGBaseViewController <UITextViewDelegate, UITextFieldDelegate> {
    VGConversationEngine *_engine;
}

@property (nonatomic, assign) id<VGRatingFeedbackViewControllerDelegate> delegate;
@property (nonatomic, strong) VGConversationEngine *engine;

@property (nonatomic, strong, readonly) VGSSRatingPicker *ratingPicker;
@property (nonatomic, strong, readonly) VGSSTextField *titleTextField;
@property (nonatomic, strong, readonly) VGSSTextView *reviewTextView;
@property (strong, nonatomic) UIToolbar *fieldAccessoryView;

@end

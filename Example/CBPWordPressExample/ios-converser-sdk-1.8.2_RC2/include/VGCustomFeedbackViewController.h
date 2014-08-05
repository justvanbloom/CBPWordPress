//
//  VGCustomFeedbackViewController.h
//  VGConversationKit
//
//  Created by Barry Scott on 22/05/2013.
//  Copyright (c) 2013 Converser. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VGKeyboardAvoidingScrollView.h"
#import "VGBaseViewController.h"

@class VGConversationEngine;
@class VGCustomFeedbackViewController;

typedef enum {
    VGCustomFeedbackResultCancelled,
    VGCustomFeedbackResultSent,
    VGCustomFeedbackResultFailed,
} VGCustomFeedbackResultType;

@protocol VGCustomFeedbackViewControllerDelegate <NSObject>

@optional

-(void) customFeedbackController:(VGCustomFeedbackViewController *)controller
             didFinishWithResult:(VGCustomFeedbackResultType)result
                           error:(NSError *)error;

@end

@interface VGCustomFeedbackViewController : VGBaseViewController <UITextViewDelegate, UITextFieldDelegate> {
    VGConversationEngine *_engine;
    NSArray *fieldsArray;
    NSDictionary *context;
}

@property (nonatomic, assign) id<VGCustomFeedbackViewControllerDelegate> delegate;
@property (nonatomic, strong) VGConversationEngine *engine;

@property (strong, nonatomic) IBOutlet VGKeyboardAvoidingScrollView *containerScrollView;
@property (strong, nonatomic) UIToolbar *fieldAccessoryView;

@property (strong, nonatomic) IBOutlet UIView *headerView;
@property (strong, nonatomic) IBOutlet UILabel *headerLabel;

@property (strong, nonatomic) IBOutlet UIView *detailTextView;
@property (strong, nonatomic) IBOutlet UILabel *detailLabel;

@property (strong, nonatomic) IBOutlet UIView *textAreaView;
@property (strong, nonatomic) IBOutlet UILabel *textAreaLabel;
@property (strong, nonatomic) IBOutlet UITextView *textAreaTextView;

@property (strong, nonatomic) IBOutlet UIView *nameView;
@property (strong, nonatomic) IBOutlet UILabel *nameLabel;
@property (strong, nonatomic) IBOutlet UITextField *nameTextField;

@property (strong, nonatomic) IBOutlet UIView *emailView;
@property (strong, nonatomic) IBOutlet UILabel *emailLabel;
@property (strong, nonatomic) IBOutlet UITextField *emailTextField;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil fields:(NSArray *)fields context:(NSDictionary *)context;

@end

//
//  UIScrollView+VGKeyboardAvoidingAdditions.h
//  VGKeyboardAvoidingSample
//
//  Created by Michael Tyson on 30/09/2013.
//  Copyright 2013 A Tasty Pixel. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UIScrollView (VGKeyboardAvoidingAdditions)
- (BOOL)VGKeyboardAvoiding_focusNextTextField;
- (void)VGKeyboardAvoiding_scrollToActiveTextField;

- (void)VGKeyboardAvoiding_keyboardWillShow:(NSNotification*)notification;
- (void)VGKeyboardAvoiding_keyboardWillHide:(NSNotification*)notification;
- (void)VGKeyboardAvoiding_updateContentInset;
- (void)VGKeyboardAvoiding_updateFromContentSizeChange;
- (void)VGKeyboardAvoiding_assignTextDelegateForViewsBeneathView:(UIView*)view;
- (UIView*)VGKeyboardAvoiding_findFirstResponderBeneathView:(UIView*)view;
-(CGSize)VGKeyboardAvoiding_calculatedContentSizeFromSubviewFrames;
@end

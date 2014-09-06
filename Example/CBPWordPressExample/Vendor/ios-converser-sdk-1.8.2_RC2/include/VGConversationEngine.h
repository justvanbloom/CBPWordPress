
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
#import "ConverserNavigationController.h"
#import "VGCustomFeedbackViewController.h"

#define kErrorDomainVGConversationKit @"ErrorDomainVGConversationKit"

@class VGConversationPane;
@class VGConversationResponse;
@protocol VGConversationItemViewControllerDelegate;
@protocol VGRatingFeedbackViewControllerDelegate;
@protocol VGCustomFeedbackViewControllerDelegate;
@class VGInboxItem;

typedef void    (^VGArrayCompletionBlock)(NSArray *);
typedef void    (^VGConversationRetrieveCompletionBlock)(VGConversationPane *);
typedef void    (^VGErrorBlock)(NSError *);
typedef void    (^VGCompletionBlock)(NSData *);

extern NSString *const kConverserSDKVersion;
extern NSString *const kConverserDefaultApiUrl;

extern NSString *const kConverserViewsHideStatusBar;
extern NSString *const kConverserPollInterval;

#define kVGLoggingNone   0x00
#define kVGLoggingError  0x01
#define kVGLoggingInfo   0x02
#define kVGLoggingDebug  0x04

@protocol VGConverserDelegate <NSObject>
-(void) converserHasMessages:(NSNumber *)countMessages
                       error:(NSError *)error;
@optional
-(void) showUnreadConversationsHasEnded;
@end


@interface VGConversationEngine : NSObject <VGCustomFeedbackViewControllerDelegate>

/**
 Helper method for loading images from the bundle
 @param imageName the name of the image
 @return UIImage with correct scaling (e.g. @2x)
 */
+(UIImage *) imageFromBundleNamed:(NSString *)imageName;

/** 
 Converser settings are read from the Converser.plist file in the main bundle
 of the application
 */

+(NSDictionary*) settings;

/**
 Initialises the engine against a particular endpoind, with a supplied appkey
 @param hostname This is the host we should be connecting to, providing the VG Converation API
 @param appKey This is the app key supplied to you when you sign up to the Converser API
 @return An initialised conversation engine
 */
-(id) initWithHostName:(NSString *)hostname
                andKey:(NSString *)appKey;
/**
 Initialises the engine with the default endpoind and a supplied appkey
 @param appKey This is the app key supplied to you when you sign up to the Converser API
 @return An initialised conversation engine
 */
-(id) initWithAppKey:(NSString *)appKey;

/**
 @param identity The identity you wish to use for the user to be known as
 @param pushToken The push token for the user
 @param completion The completion block to call when the operation completes successfully
 @param errorHandler The error handler to call if the operation failes
 */
-(void) subscribeWithIdentity:(NSString *)identity
                    pushToken:(NSString *)pushToken
                   completion:(VGCompletionBlock)completionBlock
                 errorHandler:(VGErrorBlock)errorBlock;

/**
 Start the converser engine and subscibe the supplied user
 @param identity The identity you wish to use for the user to be known as
 @param pushToken The push token for the user
 @param withDelegate The delegate object that should receive callbacks
 */
-(void) startWithIdentity:(NSString *)identity
                pushToken:(NSString *)pushToken
                 delegate:(id<VGConverserDelegate>)delegate;
-(void) startWithIdentity:(NSString *)identity
                 delegate:(id<VGConverserDelegate>)delegate;

    
-(void) retrieveInboxWithCompletionBlock:(VGArrayCompletionBlock)completionBlock
                              errorHandler:(VGErrorBlock)errorBlock;

-(void) removeInboxItem:(NSString *)inboxRef
    withCompletionBlock:(VGCompletionBlock)completionBlock
           errorHandler:(VGErrorBlock) errorBlock;

-(void) sendFeedback:(NSUInteger)reaction
                area:(NSString *)area
                text:(NSString *)text
 withCompletionBlock:(VGCompletionBlock)completionBlock
        errorHandler:(VGErrorBlock) errorBlock;

-(void) sendFeedback:(NSUInteger)reaction
                area:(NSString *)area
                text:(NSString *)text
               email:(NSString *)email
                name:(NSString *)name
             context:(NSDictionary *)context
 withCompletionBlock:(VGCompletionBlock)completionBlock
        errorHandler:(VGErrorBlock) errorBlock;

/**
 Retrieve a given conversation from the server
 @param conversationRef a reference to the conversation to rertieve
 @param conversationCompletionBlock a block to be called once the remote call has completed
 @param errorHandler a block to be called if the remote operation fails
 */
-(void) retrieveConversation:(NSString *)conversationRef
         withCompletionBlock:(VGConversationRetrieveCompletionBlock)conversationCompletionBlock
                errorHandler:(VGErrorBlock) errorBlock;

/**
 @param converationTrackerId The conversation tracker to launch with
 @param delegate delegate to be called when for view controller events
 @return A UINavigationController for the conversation
 */
-(UINavigationController *)viewControllerForConversation:(NSString *)conversationTrackerId
                                             withDelegate:(id<VGConversationItemViewControllerDelegate>) delegate;
-(UINavigationController *)viewControllerForInboxItem:(VGInboxItem *)item
                                         withDelegate:(id<VGConversationItemViewControllerDelegate>) delegate;
-(ConverserNavigationController *)controllerForInboxItem:(VGInboxItem *)item
                                                delegate:(id<VGConversationItemViewControllerDelegate>)delegate;

/**
 Displays a popover/modal view with all unread conversations
 */
-(void) showUnreadConversations;
-(void) showUnreadConversationsInboxHasClosed;

/**
 Shows the inbox notification popup
 */
-(void) displayInboxNotificationMessage;
/**
 Shows the inbox notification popup at a specified position on screen
 @param desiredPosition The CGPoint for the origin of the popup message
 */
-(void) displayInboxNotificationMessageAtPosition:(CGPoint)desiredPosition;
/**
 Shows the inbox notification popup at a specified position on screen, with specific size
 @param desiredDimensions The CGRect for the origin and size of the popup message
 */
-(void) displayInboxNotificationMessageWithDimensions:(CGRect)desiredDimensions;

/**
 Hides the inbox notification popup
 */
-(void) hideInboxNotificationMessage;




/**
 Displays a controller to allow the user provide feedback on this app
 */
-(UINavigationController *)ratingFeedbackControllerWithDelegate:(id<VGRatingFeedbackViewControllerDelegate>) delegate; // Deprecated
-(ConverserNavigationController *)ratingFeedbackController:(id<VGRatingFeedbackViewControllerDelegate>)delegate;

/**
 Displays a customisable controller to allow the user provide feedback on this app
 @param fields An array of fields to be shown
 @param context A dictionary of user defined key-value fields
 @param delegate delegate to be called when for view controller events
 */
-(ConverserNavigationController *)feedbackControllerWithFields:(NSArray *)fields
                                                       context:(NSDictionary *)context
                                                      delegate:(id<VGCustomFeedbackViewControllerDelegate>)delegate;
/**
 Displays a customisable modal/popover controller to allow the user provide feedback on this app
 @param fields An array of fields to be shown
 @param context A dictionary of user defined key-value fields
 */
-(void)showFeedbackControllerWithFields:(NSArray *)fields
                                context:(NSDictionary *)context;

/**
 @param conversationTrackerId The id of the conversation we're working with
 @param message The message the user supplied
 @param completionBlock The conversation completion block to call when the operation completes: 
 @param errorBlock The block to call if an error occurs
 */
 -(void) postUserTalkbackForConversationTracker:(NSString *)conversationTrackerId
                                   withMessage:(NSString*)message
                          withCompletionBlock:(VGConversationRetrieveCompletionBlock)completionBlock
                                  errorHandler:(VGErrorBlock) errorBlock;
/**
 @param wantsToOptOut - Set to YES if the user wants to opt out, NO if they want to stay opted in
 */
-(void) sendOptoutPreference:(BOOL)wantsToOptOut
        withCompletionBlock:(VGCompletionBlock) completionBlock
                errorHandler:(VGErrorBlock) errorBlock;


/**
 Qualifications API
 */

-(void)qualify:(NSArray*)subjects
        status:(BOOL)include
withCompletionBlock:(VGCompletionBlock)completionBlock
       errorHandler:(VGErrorBlock)errorBlock;

-(void)qualifications:(VGArrayCompletionBlock)completionBlock
             errorHandler:(VGErrorBlock)errorBlock;
/**
 @return the app key for the engine - Supplied by Converser
 */
@property (readonly) NSString *appKey;

/**
 @eturn the host name the API endpoint is on
 */
@property (readonly) NSString *hostName;
@property (readonly) NSString *originalHostName;
@property (readonly) NSString *backupHostName;
@property (nonatomic, assign) BOOL logging;
@property (nonatomic, assign) id<VGConverserDelegate> delegate;

@end


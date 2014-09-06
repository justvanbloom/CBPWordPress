
/*******************************************************
 * Copyright (C) 2011-2012 Converser contact@converser.io
 *
 * This file is part of the Converser iOS SDK.
 *
 * This code may not be copied and/or distributed without the express
 * permission of Converser. Please email contact@converser.io for
 * all redistribution and reuse enquiries.
 *******************************************************/

#import <Foundation/Foundation.h>

extern NSString* const kVGStatusUnread;

@interface VGInboxItem : NSObject

@property (readonly) NSString *status;
@property (readonly) NSString *subject;
@property (readonly) NSString *subtitle;
@property (readonly) NSDate *createdDate;
@property (readonly) NSString *conversationId;
@property (readonly) NSString *reference;
@property (readonly) NSString *conversationTrackerId;
@property (readonly) NSString *mode;

@end

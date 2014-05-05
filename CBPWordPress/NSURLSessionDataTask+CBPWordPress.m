//
//  NSURLSessionDataTask+CBPWordPress.m
//  Pods
//
//  Created by Karl Monaghan on 31/03/2014.
//
//

#import "NSURLSessionDataTask+CBPWordPress.h"

#import "CBPWordPressAPIClient.h"

#import "CBPWordPressComment.h"
#import "CBPWordPressPost.h"
#import "CBPWordPressPostContainer.h"

@implementation NSURLSessionDataTask (CBPWordPress)
+ (NSURLSessionDataTask *)fetchPostsWithParams:(NSDictionary *)params withBlock:(void (^)(CBPWordPressPostContainer *data, NSError *error))block
{
    return [[CBPWordPressAPIClient sharedClient] GET:@"/?json=1" parameters:params success:^(NSURLSessionDataTask * __unused task, id JSON) {
        
        CBPWordPressPostContainer *container = [CBPWordPressPostContainer initFromDictionary:JSON];
        
        if (block) {
            block(container, nil);
        }
    } failure:^(NSURLSessionDataTask *__unused task, NSError *error) {
        if (block) {
            block(nil, error);
        }
    }];
}

+ (NSURLSessionDataTask *)fetchPostWithId:(NSInteger)postId withBlock:(void (^)(CBPWordPressPost *post, NSError *error))block
{
    return [[CBPWordPressAPIClient sharedClient] GET:@"/?json=get_post" parameters:@{@"post_id": [NSNumber numberWithInteger:postId]} success:^(NSURLSessionDataTask * __unused task, id JSON) {
        
        if ([JSON[@"status"] isEqualToString:@"ok"]) {
            CBPWordPressPost *post = [CBPWordPressPost initFromDictionary:JSON[@"post"]];
            
            if (block) {
                block(post, nil);
            }
        } else {
            block(nil, [NSError errorWithDomain:@"CBPWordPressError" code:0 userInfo:@{@"error": JSON[@"error"]}]);
        }
    } failure:^(NSURLSessionDataTask *__unused task, NSError *error) {
        if (block) {
            block(nil, error);
        }
    }];
}

+ (NSURLSessionDataTask *)postComment:(NSDictionary *)comment withBlock:(void (^)(CBPWordPressComment *comment, NSError *error))block
{
    return [[CBPWordPressAPIClient sharedClient] GET:@"/?json=respond.submit_comment" parameters:comment success:^(NSURLSessionDataTask * __unused task, id JSON) {
        
        if ([JSON[@"status"] isEqualToString:@"ok"]) {
            CBPWordPressComment *comment = [CBPWordPressComment initFromDictionary:JSON[@"comment"]];
            
            if (block) {
                block(comment, nil);
            }
        } else {
            block(nil, [NSError errorWithDomain:@"CBPWordPressError" code:0 userInfo:@{@"error": JSON[@"error"]}]);
        }
    } failure:^(NSURLSessionDataTask *__unused task, NSError *error) {
        if (block) {
            block(nil, error);
        }
    }];
}
@end

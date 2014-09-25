//
//  CBPAppDelegate.m
//  CBPWordPressExample
//
//  Created by Karl Monaghan on 29/03/2014.
//  Copyright (c) 2014 Crayons and Brown Paper. All rights reserved.
//

#import <Crashlytics/Crashlytics.h>
#import "GAI.h"
#import "GAIFields.h"
#import "GAIDictionaryBuilder.h"
#import <GooglePlus/GooglePlus.h>

#import "CBPAppDelegate.h"

#import "CBPHomeViewController.h"
#import "CBPNavigationController.h"
#import "CBPWordPressAPIClient.h"

@interface CBPAppDelegate()
@property (nonatomic) CBPHomeViewController *viewController;
@end

@implementation CBPAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    [CBPWordPressAPIClient rootURI:CBPApiURL];
                                                           
    self.viewController = [CBPHomeViewController new];
    
    self.navigationController = [[CBPNavigationController alloc] initWithRootViewController:self.viewController];
    self.navigationController.navigationBar.tintColor = [UIColor darkGrayColor];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor whiteColor];
    self.window.rootViewController = self.navigationController;
    [self.window makeKeyAndVisible];
    
    NSURLCache *URLCache = [[NSURLCache alloc] initWithMemoryCapacity:4 * 1024 * 1024
                                                         diskCapacity:20 * 1024 * 1024
                                                             diskPath:nil];
    [NSURLCache setSharedURLCache:URLCache];

    [self firstTime:application];
    
    [GPPSignIn sharedInstance].clientID = BSGooglePlusKey;
    
    [Crashlytics startWithAPIKey:BSCrashlyticsKey];
#if TARGET_IPHONE_SIMULATOR
    [[GAI sharedInstance] setDryRun:YES];
    [[[GAI sharedInstance] logger] setLogLevel:kGAILogLevelVerbose];
#endif
    [[GAI sharedInstance] trackerWithTrackingId:BSGoogleAnalyticsKey];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    [UIApplication sharedApplication].applicationIconBadgeNumber = 0;
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{        
    if ([[url host] hasSuffix:CBPSiteURL]) {
        [self.navigationController popToRootViewControllerAnimated:NO];
        
        [self.viewController openURL:url];
        
        [[[GAI sharedInstance] defaultTracker] send:[[GAIDictionaryBuilder createEventWithCategory:@"ui_action"
                                                                                            action:@"notification"
                                                                                             label:@"opened_from_url"
                                                                                             value:nil] build]];
        
        return YES;
    } else if ([[url scheme] isEqualToString:@"BroadsheetIe"]) {
        [self.navigationController popToRootViewControllerAnimated:NO];
        
        [self.viewController openPost:[[url host] integerValue]];
        
        [[[GAI sharedInstance] defaultTracker] send:[[GAIDictionaryBuilder createEventWithCategory:@"ui_action"
                                                                                            action:@"notification"
                                                                                             label:@"opened_from_today"
                                                                                             value:nil] build]];
        
        return YES;
    }
    
    // handle Google+ Sign In callback URL
    return [[GPPSignIn sharedInstance] handleURL:url sourceApplication:sourceApplication annotation:annotation];
}

- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    [self.viewController backgroundUpdateWithCompletionHandler:completionHandler];
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    [self.navigationController popToRootViewControllerAnimated:NO];
    
    [[[GAI sharedInstance] defaultTracker] send:[[GAIDictionaryBuilder createEventWithCategory:@"ui_action"
                                                                                        action:@"notification"
                                                                                         label:@"opened_from_local"
                                                                                         value:nil] build]];
}

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
    if ([[NSUserDefaults standardUserDefaults] boolForKey:CBPLockRotation]) {
        return UIInterfaceOrientationPortrait;
    }
    
    return UIInterfaceOrientationMaskAllButUpsideDown;
}

#pragma mark -
- (void)firstTime:(UIApplication *)application
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    if ([defaults boolForKey:CBPFirstTime]) {
        return;
    }

    [application setMinimumBackgroundFetchInterval:CBPBackgroundFetchInterval];
    [defaults setBool:YES forKey:CBPBackgroundUpdate];
    
    [self setupNotification];
    
    [defaults setBool:YES forKey:CBPFirstTime];
    
    [defaults synchronize];
}

- (void)setupNotification
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    if (![defaults boolForKey:@"removed_notification"]) {
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
        
        [defaults removeObjectForKey:CBPLocalNotifcation];
        
        [defaults setBool:YES forKey:@"removed_notification"];
        
        [defaults synchronize];
        
        return;
    }
    
    if ([defaults boolForKey:CBPLocalNotifcation]) {
        return;
    }
    
    NSDate *tomorrow = [NSDate dateWithTimeIntervalSinceNow:84600];
    
    NSCalendar *calendar = [NSCalendar autoupdatingCurrentCalendar];
    calendar.timeZone = [NSTimeZone defaultTimeZone];
    
    NSDateComponents *dateComps = [calendar components: NSCalendarUnitYear | NSCalendarUnitMonth |  NSCalendarUnitDay fromDate:tomorrow];
    [dateComps setHour:8];
    [dateComps setMinute:15];
    NSDate *itemDate = [calendar dateFromComponents:dateComps];
    
    UILocalNotification *localnotifcation = [UILocalNotification new];
    
    if (!localnotifcation) {
        return;
    }
    
    localnotifcation.fireDate = itemDate;
    localnotifcation.timeZone = [NSTimeZone defaultTimeZone];
    localnotifcation.repeatInterval = NSCalendarUnitWeekday;
    
    localnotifcation.alertBody = NSLocalizedString(@"Catch up on all the news that doesn't matter.", nil);
    localnotifcation.alertAction = NSLocalizedString(@"Read More", nil);
    
    localnotifcation.soundName = UILocalNotificationDefaultSoundName;
    localnotifcation.applicationIconBadgeNumber = 1;
    
    [[UIApplication sharedApplication] scheduleLocalNotification:localnotifcation];
    
    [dateComps setHour:17];
    [dateComps setMinute:45];
    itemDate = [calendar dateFromComponents:dateComps];
    localnotifcation.fireDate = itemDate;

    [[UIApplication sharedApplication] scheduleLocalNotification:localnotifcation];

    [defaults setBool:YES forKey:CBPLocalNotifcation];
    [defaults setBool:YES forKey:CBPDailyReminder];
    
    [defaults synchronize];
}

@end

//
//  StreamingView.h
//  iViewer
//
//  Created by davis.cho on 2015/1/6.
//  Copyright (c) 2015年 Vivotek. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSInteger
{
    eStreamingStatusConnecting = 0,
    eStreamingStatusConnected = 1,
    eStreamingStatusDisconnected = 2
} StreamingStatus;

typedef enum : NSInteger
{
    eFisheyeDewarpNone = 0,  // No dewarp
    eFisheyeDewarpPano = 1,  // panorama projection
    eFisheyeDewarpRect = 2,  // rectilinear projection
    eFisheyeDewarpFullHD = 3 // full hd panorama
} FisheyeDewarpType;

typedef enum : NSInteger
{
    eFisheyeInstallationWall = 0,
    eFisheyeInstallationCelling = 1,
    eFisheyeInstallationFloor = 2,
    eFisheyeInstallationLocaldewrap = 3
} FisheyeInstallation;

typedef enum : NSInteger
{
    ePTZActionZoomIn = 0,
    ePTZActionZoomOut = 1,
    ePTZActionRight = 2,
    ePTZActionLeft = 3,
    ePTZActionUp = 4,
    ePTZActionDown = 5
} PTZAction;

@class StreamingView;
@protocol StreamingViewDelegate<NSObject>
@optional
- (void)streamingView:(StreamingView *)streamingView gestureDidPinch:(UIPinchGestureRecognizer *)gestureRecognizer;
- (void)streamingView:(StreamingView *)streamingView gestureDidPan:(UIPanGestureRecognizer *)gestureRecognizer;
- (void)streamingView:(StreamingView *)streamingView gestureDidSwipe:(UISwipeGestureRecognizer *)gestureRecognizer;
- (void)streamingView:(StreamingView *)streamingView ptzDidOperate:(PTZAction)ptzAction;
- (void)streamingViewConnected:(StreamingView *)streamingView;
- (void)streamingViewDisconnected:(StreamingView *)streamingView;
- (void)streamingViewAuthFailed:(StreamingView *)streamingView;
@end

@interface StreamingView : UIView<UIGestureRecognizerDelegate>

// For General

@property (weak) id<StreamingViewDelegate> delegate;

@property (strong, nonatomic) NSString *IP;
@property (nonatomic) NSInteger port;
@property (strong, nonatomic) NSString *username;
@property (strong, nonatomic) NSString *password;

@property (nonatomic) NSInteger channel;
@property (nonatomic) NSInteger stream;
@property (strong, nonatomic) NSString *videoURL;

@property (nonatomic, readonly) StreamingStatus status;

- (void)setupCameraIP:(NSString *)IP port:(NSInteger)port username:(NSString *)username password:(NSString *)password channel:(NSInteger)channel stream:(NSInteger)stream;
- (void)setupServerIP:(NSString *)IP port:(NSInteger)port username:(NSString *)username password:(NSString *)password videoURL:(NSString *)videoURL;

- (void)preferProtocolHTTP; // Default
- (void)preferProtocolHTTPS;
- (void)preferProtocolTCP;
- (void)preferProtocolUDP;

- (void)startStreaming;
- (void)endStreaming;

- (void)enableAudio;
- (void)disableAudio;

// For iViewer & EZConnect App

@property (strong, nonatomic) NSString *deviceID;
@property (strong, nonatomic) NSString *MAC;

@property (nonatomic) BOOL allowGestures;
@property (nonatomic, readonly) double pinchScale;
@property (nonatomic, readonly) CGPoint panTranslation;

@property (nonatomic, readonly) BOOL isPIP;
@property (nonatomic, readonly) BOOL isPTZ;

@property (nonatomic, readonly) BOOL isFisheyeDewarping;
@property (nonatomic) FisheyeDewarpType fisheyeDewarpType;
@property (nonatomic, readonly) FisheyeInstallation fisheyeInstallation;

@property (nonatomic) BOOL autoReconnect;

- (void)setupDeviceID:(NSString *)deviceID MAC:(NSString *)MAC channel:(NSInteger)channel stream:(NSInteger)stream;
- (void)setupDeviceID:(NSString *)deviceID MAC:(NSString *)MAC channel:(NSInteger)channel; // Auto select stream with lowest resolution

- (void)enablePIP;
- (void)disablePIP;
- (void)resetPIP;

- (void)enablePTZ;
- (void)disablePTZ;

- (void)enableFisheyeDewraping;
- (void)disableFisheyeDewraping;

- (UIImage *)snapshot;

- (void)setConnectingAnimationImages:(NSArray *)images duration:(NSTimeInterval)animationDuration;
- (void)setDisconnectedImage:(UIImage *)image;
- (void)setUnsupportedCodecImage:(UIImage *)image;
- (void)setLostImage:(UIImage *)image;
- (void)setDisconnectedTransparentImage:(UIImage *)image;
- (void)setUnsupportedCodecTransparentImage:(UIImage *)image;
- (void)setLostTransparentImage:(UIImage *)image;

- (void)setBackgroundLabel:(NSString *)text;

- (void)setBitrateLimitModeForP2P:(BOOL)shouldLimit;
- (void)setBitrateLimitModeForRelay:(BOOL)shouldLimit;

@end

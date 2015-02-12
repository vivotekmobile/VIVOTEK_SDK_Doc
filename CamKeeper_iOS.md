CamKeeper for iOS
================

# How to use
## Streaming
In your ViewController header:

```objective-c
#import "CamKeeper/StreamingView.h"

@interface ViewController : UIViewController<StreamingViewDelegate>
@property (strong, nonatomic) StreamingView *streamingView;
```

In your ViewController implement:
###Connect to a IP camera:

```objective-c
self.streamingView = [[StreamingView alloc] initWithFrame:CGRectMake(0, 0, 320, 240)];
[self.view addSubview:self.streamingView];

self.streamingView.delegate = self;
[self.streamingView setupCameraIP:@"172.18.1.220" port:80 username:@"root" password:@"root" channel:1 stream:1];
[self.streamingView preferProtocolHTTP];
[self.streamingView enableAudio];
[self.streamingView startStreaming];
```

###Connect to a camera managed by VAST/ST7501 server or NVR:

```objective-c
self.streamingView = [[StreamingView alloc] initWithFrame:CGRectMake(0, 0, 320, 240)];
[self.view addSubview:self.streamingView];

self.streamingView.delegate = self;
NSString *videoURL = [NSString stringWithFormat:@"/Media/Live/Normal?camera=%@&streamindex=%u", @"C_1", 1];
[self.streamingView setupServerIP:@"172.18.120.11" port:3454 username:@"admin" password:@"admin" videoURL:videoURL];
[self.streamingView preferProtocolTCP];
[self.streamingView enableAudio];
[self.streamingView startStreaming];
```

StreamingView is a subclass of UIView. You can also load it from XIBs or Storyboards, then simply link a IBOutlet to your source code.

###StreamingViewDelegate:

When streaming connected

```objective-c
- (void)streamingViewConnected:(StreamingView *)streamingView;
```

When streaming disconnected

```objective-c
- (void)streamingViewDisconnected:(StreamingView *)streamingView;
```

When streaming authentication failed

```objective-c
- (void)streamingViewAuthFailed:(StreamingView *)streamingView;
```

##PTZ Control
In your ViewController header:
###Connect to a IP camera:
```objective-c
#import "CamKeeper/PTZController.h"

@interface ViewController : UIViewController<PTZControllerDelegate>
@property (strong, nonatomic) PTZController *ptzController;
```

In your ViewController implement:

```objective-c
self.ptzController = [[PTZController alloc] init];
self.ptzController.delegate = self;
[self.ptzController setupCameraIP:@"172.18.1.220" port:80 username:@"root" password:@"root"];
```

###Connect to a camera managed by VAST/ST7501 server or NVR:
*PTZController currently not support controlling cameras managed by VAST/ST7501 server or NVR.*

###PTZControllerDelegate:
When successfully connected to the PTZ camera

```objective-c
- (void)PTZControllerSetupSuccess;
```
When fail connecting to the PTZ camera. Check PTZControllerError for reason

```objective-c
- (void)PTZControllerSetupFailureWithError:(PTZControllerError)error;
```

After **- (void)PTZControllerSetupSuccess** get called, you are able to start operate PTZ actions. Such as **- (bool)zoomIn**, **- (bool)moveUp**, ...

# Installation
- Copy CamKeeper.framework to your project path
- Add CamKeeper.framework to your project Build Phases -> Link Binary With Libraries
- Also link the following libraries:
  - MobileCoreServices
  - Security
  - SystemConfiguration
  - libiconv
  - CoreGraphics
  - OpenGLES
  - QuartzCore
  - AudioToolbox
  - libz
- Select "libstdc++ (GNU C++ standard library)" in Build Settings -> C++ Standard Library
- Rename your objective-c files in your project from .m to .mm, including main, app delegate and view controllers
- Run your project

# Note
- CamKeeper.framework doesn't support x86 simulator, please build your project only on armv7 devices

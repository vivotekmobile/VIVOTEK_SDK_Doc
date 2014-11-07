### Audio Upload
AudioUploadController header:
```objective-c
@protocol AudioUploadControllerDelegate<NSObject>

- (void)audioUploadDidConnected;
- (void)audioUploadInitFail;
- (void)audioUploadAuthFail;
- (void)audioUploadConnectFail;
- (void)audioUploadServiceUnavailable;
- (void)audioUploadDidDisconnected;

@end

@interface AudioUploadController : NSObject <AVAudioSessionDelegate>

@property (weak, nonatomic) id<AudioUploadControllerDelegate> delegate;

@property (strong, nonatomic) NSString *IP;
@property (nonatomic) int port;
@property (strong, nonatomic) NSString *url;
@property (strong, nonatomic) NSString *username;
@property (strong, nonatomic) NSString *password;
@property (nonatomic) BOOL useHTTPS;

- (id)initWithDelegate:(id)delegate;

- (void)setupWithIP:(NSString *)IP
               port:(int)port
                url:(NSString *)url
           username:(NSString *)username
           password:(NSString *)password
           useHTTPS:(BOOL)useHTTPS;

- (void)setVoiceDetectLevelThreshold:(double)dbLevel;
- (void)start;
- (void)stop;

@end
```
#### How to use
In your main:
```objective-c
int main(int argc, char * argv[]) {
    @autoreleasepool {
        // Ignore SIGPIPE signal, othewise the app will force closed because of capturing the unhandled signals. It's OK to ignore this.
        // Note: If you are debugging the app using Xcode, all signals will still not be ignored due to Xcode debugger.
        signal(SIGPIPE, SIG_IGN); 
        
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
```

In your ViewController header:
```objective-c
#import <AudioUpload/AudioUploadController.h>

@interface ViewController : UIViewController<AudioUploadControllerDelegate>
@property (strong, nonatomic) AudioUploadController *audioUploadController;
```

In your ViewController implement:

```objective-c
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.audioUploadController = [[AudioUploadController alloc] initWithDelegate:self];
    
    [self.audioUploadController setupWithIP:YOUR_DEVICE_IP
                                       port:YOUR_DEVICE_PORT
                                        url:YOUR_DEVICE_AUDIO_UPLOAD_URL // Eg:"/vivint/g711.cgi?cameraID=0002D100AABB"
                                   username:YOUR_DEVICE_USERNAME
                                   password:YOUR_DEVICE_PASSWORD
                                   useHTTPS:NO];
                                   
    [self.audioUploadController setVoiceDetectLevelThreshold:-25.0f]; // Default value will be -25.0f if you don't set it
}

// Control your two way audio by UI
- (IBAction)buttonDidTouch:(UIButton *)sender
{
    sender.selected = !sender.selected;
    
    if (sender.selected)
    {
        [self.audioUploadController start];
    }
    else
    {
        [self.audioUploadController stop];
    }
}

// Implement AudioUploadControllerDelegate
- (void)audioUploadDidConnected
{
    // Connected. You could start talking now.
}

- (void)audioUploadInitFail
{
    // Fail to init system-side audio recording resource (AVAudioSession)
    // The issue should be caused by the operation system.
}

- (void)audioUploadAuthFail
{
    // 401 Authentication fail.
    // Can't access the target device using the provided username and password.
}

- (void)audioUploadConnectFail
{
    // Connection fail.
    // Can't connect to the target device.
}

- (void)audioUploadServiceUnavailable
{
    // 503 Service Unavailable
    // The audio upload service of the target device is unavailable.
}

- (void)audioUploadDidDisconnected
{
    // Disconnected. 
    // Fail to upload audio during talking. Either the mobile device or the target device is disconnected.
}

```

The AudioUploadController instance can be reused to connect to another device:
```objective-c
// Stop it first
[self.audioUploadController stop];

// Setup to another device
[self.audioUploadController setupWithIP:YOUR_DEVICE_IP
                                       port:YOUR_DEVICE_PORT
                                        url:YOUR_DEVICE_AUDIO_UPLOAD_URL
                                   username:YOUR_DEVICE_USERNAME
                                   password:YOUR_DEVICE_PASSWORD
                                   useHTTPS:USE_HTTPS];
// Start it again
[self.audioUploadController start];
```

### Installation
- Copy AudioUpload.framework to your project path
- Add AudioUpload.framework, AVFoundation, AudioToolbox to your project Build Phases -> Link Binary With Libraries
- Select "libstdc++ (GNU C++ standard library)" in Build Settings -> C++ Standard Library
- Rename your objective-c files in your project from .m to .mm, including main, app delegate and view controllers
- Run your project

### Support architecture
- x86, armv7, armv7s, arm64

### Reqiured iOS SDK version
- iOS 6.0 or above

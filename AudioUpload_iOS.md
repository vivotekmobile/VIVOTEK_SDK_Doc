### Audio Upload
AudioUploadController header:
```objective-c
@protocol AudioUploadControllerDelegate<NSObject>

- (void)audioUploadInitAudioSessionFail;
- (void)audioUploadAuthFail;
- (void)audioUploadConnectFail;
- (void)audioUploadDidConnected;
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

- (void)audioUploadInitAudioSessionFail
{
    // Fail to set & active iOS shared AVAudioSession
    // This should never happen.
}

- (void)audioUploadAuthFail
{
    // Authentication fail.
}

- (void)audioUploadConnectFail
{
    // Connection fail.
}

- (void)audioUploadDidConnected
{
    // Connected. You could start talking now.
    // After calling [start], you will receive this if everything is OK. 
}

- (void)audioUploadDidDisconnected
{
    // Disconnected.
    // After calling [stop] or something wrong during talking, you will receive this.
}

```

The AudioUploadController instance can be reused to connect to another device:
```objective-c
// Stop it first
[self.audioUploadController stop];

// Setup to another device
[self.audioUploadController setupWithIP:YOUR_DEVICE_IP
                                       port:YOUR_DEVICE_PORT
                                        url:YOUR_DEVICE_AUDIO_UPLOAD_URL // Eg:"/vivint/g711.cgi?cameraID=0002D100AABB"
                                   username:YOUR_DEVICE_USERNAME
                                   password:YOUR_DEVICE_PASSWORD
                                   useHTTPS:NO];
// Start it again
[self.audioUploadController start];
```

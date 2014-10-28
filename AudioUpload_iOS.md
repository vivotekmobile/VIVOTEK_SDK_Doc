### Audio Upload
AudioUploadController header:
```objective-c
@protocol AudioUploadControllerDelegate<NSObject>

- (void)audioUploadDidFail;
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
@property (nonatomic) double voiceDetectLevelThreshold;

- (id)initWithDelegate:(id)delegate useHTTPS:(BOOL)useHTTPS;
- (void)setupWithIP:(NSString *)IP Port:(int)port URL:(NSString *)url Username:(NSString *)username Password:(NSString *)password;
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
    
    self.audioUploadController = [[AudioUploadController alloc] initWithDelegate:self useHTTPS:NO];
    
    [self.audioUploadController setupWithIP:YOUR_DEVICE_IP
                                       Port:YOUR_DEVICE_PORT
                                        URL:YOUR_DEVICE_AUDIO_UPLOAD_URL // Ex: @"/vivint/g711.cgi?cameraID=0002D100AABB"
                                   Username:YOUR_DEVICE_USERNAME
                                   Password:YOUR_DEVICE_PASSWORD];
                                   
    [self.audioUploadController setVoiceDetectLevelThreshold:-25.0f]; // Default value will be -25.0f if you don't set one
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

- (void)audioUploadDidFail
{
    // Fail to connect
}

- (void)audioUploadDidDisconnected
{
    // Lost connection
}

```

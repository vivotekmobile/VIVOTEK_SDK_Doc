DeviceRollingLib for iOS
================

### How to use
In your ViewController header:

```objective-c
#import <DeviceRolling/DeviceRollingController.h>

@interface ViewController : UIViewController<DeviceRollingControllerDelegate>
@property (strong, nonatomic) DeviceRollingController *deviceRollingController;
```

In your ViewController implement:

```objective-c
- (void)viewDidLoad
{
    [super viewDidLoad];

    // Init the DeviceRollingController with P2P server and delegate. 
    // A DeviceRollingController instance can be reuse for connecting to different devices, you don't need to create another new instance for each device.
    
    self.deviceRollingController = [[DeviceRollingController alloc] initWithP2PServerIP:YOUR_VIVOTEK_P2P_SERVER_IP port:YOUR_VIVOTEK_P2P_SERVER_PORT delegate:self];

    // As long as the DeviceRollingController has init, you can always call this function to establish P2P connection and get the latest P2P ports for your device
    [self.deviceRollingController getDeviceInfoOfID:YOUR_VIVOTEK_DEVICE_ID
                                                  username:YOUR_VIVOTEK_USERNAME
                                                  password:YOUR_VIVOTEK_PASSWORD];
}

// The delegate will be called when P2P connection has done
- (void)getDeviceInfoDidCompleted:(DeviceInfo *)deviceInfo status:(DeviceStatusType)statusType
{
    // You will get a DeviceInfo object containing device ID, firmware version, username, password & P2P ports
    // If P2P connection has fail, you could check the DeviceStatusType for more information
}
```

### Installation
- Copy DeviceRolling.framework to your project path
- Add DeviceRolling.framework to your project Build Phases -> Link Binary With Libraries
- Select "libstdc++ (GNU C++ standard library)" in Build Settings -> C++ Standard Library
- Rename your objective-c files in your project from .m to .mm, including main, app delegate and view controllers
- Remove "armv7s" "arm64" from Build Settings -> Valid Architectures
- Run your project

### Note
- DeviceRolling.framework doesn't support x86 simulator, please build your project only on armv7 devices

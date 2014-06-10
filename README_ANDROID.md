DeviceRollingLib for Android
================

### How to use
In your Activity:

```java
import com.vivotek.devicerolling.DeviceInfo;
import com.vivotek.devicerolling.DeviceStatusType;
import com.vivotek.devicerolling.DeviceRollingController;
import com.vivotek.devicerolling.DeviceRollingController.DeviceRollingControllerDelegate;

public class MainActivity extends Activity implements DeviceRollingControllerDelegate
{
    private DeviceRollingController deviceRollingController = null;
    
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        deviceRollingController = new DeviceRollingController();
        
        // Init the DeviceRollingController with P2P server, delegate and context.
        // A DeviceRollingController instance can be reuse for connecting to different devices, you don't need to create another new instance for each device.
        deviceRollingController.initial(MainActivity.this, MainActivity.this.getApplicationContext(), YOUR_VIVOTEK_P2P_SERVER_IP, YOUR_VIVOTEK_P2P_SERVER_PORT);
        
        // As long as the DeviceRollingController has init, you can always call this function to establish P2P connection and get the latest P2P ports for your device
        deviceRollingController.getDeviceInfo(YOUR_VIVOTEK_DEVICE_ID, YOUR_VIVOTEK_USERNAME, YOUR_VIVOTEK_PASSWORD);
    }
}

// The delegate will be called when P2P connection has done
@Override
public void getDeviceInfoDidCompleted(DeviceInfo deviceInfo, DeviceStatusType status)
{
    // You will get a DeviceInfo object containing device ID, firmware version, username, password & P2P ports
    // If P2P connection has fail, you could check the DeviceStatusType for more information
}
```

### Installation
- Copy libVivotekP2PSDK-JNI.so to your project libs\armeabi folder
- Copy DeviceRolling.jar to your project path
- Add DeviceRolling.jar in your project Properties->Java Build Path->Libraties
- Select DeviceRolling.jar in your project Properties->Java Build Path->Order and Export
- Run your project



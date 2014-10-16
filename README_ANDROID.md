DeviceRollingLib for Android
================

### How to use
In your Activity:

```java
import com.vivotek.devicerolling.DeviceInfo;
import com.vivotek.devicerolling.DetailedDeviceInfo;
import com.vivotek.devicerolling.DeviceRollingStatus;
import com.vivotek.devicerolling.DeviceRollingType;
import com.vivotek.devicerolling.P2PStatusType;
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

// Implement the DeviceRollingControllerDelegate
@Override
public void getDeviceInfoDidCompleted(final DeviceInfo deviceInfo, final DeviceRollingStatus rollingStatus, final P2PStatusType p2pStatusType)
{
    // You will get a DeviceInfo object containing device ID, firmware version, username, password, 
    // IP, http/https/rtsp ports for the current best connection type
}

// Or another delegate providing more details
@Override
public void getDeviceInfoDidCompleted(final DetailedDeviceInfo deviceInfo, final DeviceRollingStatus rollingStatus, final DeviceRollingType rollingType, final P2PStatusType p2pStatusType)
{
    // You will get a DetailDeviceInfo object containing device ID, firmware version, username, password, 
    // a set of IPs and http/https/rtsp ports for all kinds of available connection types and the current best connection type
}

```

### Installation
- Copy libVivotekP2PSDK-JNI.so to your project libs\armeabi folder
- Copy DeviceRolling.jar to your project path
- Add DeviceRolling.jar in your project Properties->Java Build Path->Libraties
- Select DeviceRolling.jar in your project Properties->Java Build Path->Order and Export
- Run your project



### Audio Upload
#### How to use
In your Activity:

```java
import com.vivotek.camkeeper.AudioCapturer;

public class MainActivity extends Activity implements AudioCapturer.AudioUploadCallback
{
    private AudioCapturer mAudioCapturer = null;
    private Button mButton = null;
    
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        mAudioCapturer = AudioCapturer.getInstance();  
        mAudioCapturer.setup(YOUR_DEVICE_IP, YOUR_DEVICE_PORT, YOUR_DEVICE_AUDIO_UPLOAD_URL, YOUR_DEVICE_USERNAME, YOUR_DEVICE_PASSWORD, USE_HTTPS); 
        mAudioCapturer.initWithCallback(MainActivity.this); 
    }
    
    @Override
        public void onClick(View v)
        {
            if (v.equals(mButton))
            {
                if (mAudioCapturer == null)
                {
                    mAudioCapturer.start();
                }
                else
                {
                    mAudioCapturer.stop();
                    mAudioCapturer = null;
                }
            }
        }
}

// Implement AudioUploadCallback

@Override
public void audioUploadDidConnected()
{
    // Connected. You could start talking now.
}

@Override
public void audioUploadInitAudioFail()
{
    // Fail to init system-side audio recording resource
    // The issue should be caused by the operation system.
}

@Override
public void audioUploadAuthFail()
{
    // 401 Authentication fail.
    // Can't access the target device using the provided username and password.
}

@Override
public void audioUploadConnectFail()
{
    // Connection fail.
    // Can't connect to the target device.
}

@Override
public void audioUploadServiceUnavailable()
{     
    // 503 Service Unavailable
    // The audio upload service of the target device is unavailable.
}

@Override
public void audioUploadDidDisconnected()
{     
    // Disconnected. 
    // Fail to upload audio during talking. Either the mobile device or the target device is disconnected.
}

```

### Installation
- Copy libs and JAR to your project
- Add AudioUpload.jar in your project Properties->Java Build Path->Libraties
- Select AudioUpload.jar in your project Properties->Java Build Path->Order and Export
- Run your project

### Reqiured permission
- android.permission.INTERNET
- android.permission.RECORD_AUDIO

### Reqiured Android SDK version
- Android Gingerbread 2.3.3 or above

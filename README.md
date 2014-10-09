VIVOTEK SDK for iOS
================

### P2P Rolling

1. Init the DeviceRollingController with P2P server IP, port and delegate.
2. Start rolling to device by asking DeviceRollingController with your device ID, username and password.
3. When the rolling completed, you will get everything you need to connect to the device within a delegate callback.
  * Current best connection type (Public / LAN / P2P / Relay) 
  * IP, HTTP/HTTPS/RTSP ports for different connection type

After the rolling completed, you will be able to access the device by IP, port, username and password containing in the DeviceRollingController delegate callback.

### Audio upload

1. Init and setup the AudioUploader with device IP, port, username, password, and delegate.
2. Start AudioUploader to start talking 
3. You will be notified of the connection status of AudioUploader by some delegate callbacks to handle network fails.
3. Stop AudioUploader to stop talking

### Video/Audio Streaming

1. Init and setup the StreamingController with device IP, port, username, password, and delegate.
2. Add a view included in the StreamingController to your UI, the streaming will be shown on the view.
3. Start StreamingController to start streaming.
3. You will be notified of the connection status of StreamingController by some delegate callbacks to handle network fails.
3. Stop StreamingController to stop streaming

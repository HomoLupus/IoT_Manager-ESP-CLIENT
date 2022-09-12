# espHttpClient
Software for esp8266 board, connect to the internet and sends data from the sensor into PHP script via HTTPS methods 


<h2> Quick render </h2>

Simple visualization of final device. It will be created on 3D printer. 
<br><br>
![image](https://user-images.githubusercontent.com/83671766/189667017-0a9df4b8-0856-4483-8cca-464590228511.png)



<h2> How it works </h2>

Eps8266 read data from BMP280 sensor and it to server, server puts it into database. 
<br><br>
![image](https://user-images.githubusercontent.com/83671766/189524251-0d62aa19-61bc-41f8-8ec5-cb44e10b368a.png)

<br><br>

Connect the device to the power, microcontroller will create an AcessPoint, connect to it with your phone or desktop device. Managing page will open automatically, choose the wifi and write down the ID of your sensor.


![image](https://user-images.githubusercontent.com/83671766/189494247-b9832d1d-6983-4cf7-82df-3e4a3cdbbc85.png)
<br><br>

The https://github.com/tzapu/WiFiManager library was used to manage the wifi network.



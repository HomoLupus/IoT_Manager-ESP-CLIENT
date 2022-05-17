#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

Adafruit_BME280 bme; // I2C


/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/
//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "http://tonyz7esp.ct8.pl/esp.php"

#ifndef STASSID
#define STASSID "Arduino"
#define STAPSK  "arduino420"
#endif

#define DHTTYPE DHT11
#define DHTPIN 5 


float humidty,temp,pressure;


String postMessage;

void setup() {
  digitalRead(1);
  
  bool status;

  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

   

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  printValues();

  humidty = bme.readHumidity();
  pressure = (bme.readPressure() / 100.0F);
  temp = bme.readTemperature();

    


  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, SERVER_IP); //HTTP
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");



    // Prepare your HTTP POST request data
    String httpRequestData2 = "api_key=999&sensor=BMP280&location=Akademik&value1=111&value2=222&value3=333";

    String myStringTemp = String(temp);
    String myStringHum = String(humidty);
    String myStringPres = String(pressure);
   
    String httpRequestData = "api_key=999&sensor=BMP280&location=Akademik&value1=" + myStringTemp +"&value2= "+ myStringHum + "&value3=" + myStringPres;



    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST(httpRequestData);





    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(5000);
}
void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");


  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

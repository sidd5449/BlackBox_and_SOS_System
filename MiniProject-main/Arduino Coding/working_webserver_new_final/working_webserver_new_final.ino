#include <WiFiNINA.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Arduino_LSM6DS3.h>
#include<ArduinoJson.h>
#include <ArduinoBLE.h>


// code :- 29th march 1.56am
// In the address bar of the web browser, enter the IP address of the device running this
// code followed by :80. For example, if the IP address of the device is 192.168.1.100,
// you would enter http://192.168.1.100:80 in the address bar.

unsigned long startTime;

// char ssid[] = "Realme 3 Pro";
// char pass[] = "Abhishek55";
// int status = WL_IDLE_STATUS;

const int vibrationPin = A0;
const int chipSelect = 4;
StaticJsonDocument<200> doc; 
char jsonBuffer[512]; 
// WiFiServer server(80);


void setup() {

  Serial.begin(9600);
    // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  // set advertised local name and service UUID
  BLE.setLocalName("Nano33IoT");
  BLE.setAdvertisedServiceUuid("19B10000-E8F2-537E-4F6C-D104768A1214");

  // start advertising
  BLE.advertise();


  // while (status != WL_CONNECTED){
  //   Serial.print("Attempting to connect to SSID: ");
  //   Serial.println(ssid);
  //   status = WiFi.begin(ssid, pass);
  //   delay(5000);
  // }

  // Serial.println("Connected to WiFi network");
  // while (!Serial);
  // if (!IMU.begin()) {
  //   Serial.println("Failed to initialize IMU!");
  //   while (1) {
  //     delay(10);
  //   }
  // }

  Serial.println("IMU sensor initialized");
  pinMode(vibrationPin, INPUT);
  Serial.println("Vibration sensor initialized");
  // server.begin();
   startTime = millis();
}

void loop() {
   if (millis() - startTime > (1000)) {
     // Exit loop function
     return;
   }

    // server.begin();
    // IPAddress ip = WiFi.localIP();
    // Serial.print("IP Address: ");
    // Serial.println(ip);

  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {

    sensors_event_t event;
   float accX, accY, accZ, gyroX, gyroY, gyroZ;
   int vibrationValue = analogRead(vibrationPin);
   if (IMU.accelerationAvailable()) {
     IMU.readAcceleration(accX, accY, accZ);
     delay(100);
   } else IMU.end();
  
   if (IMU.gyroscopeAvailable()) {
     IMU.readGyroscope(gyroX, gyroY, gyroZ);
     delay(100);
   }
   doc["x"] = event.orientation.x;
   doc["y"] = event.orientation.y;
   doc["z"] = event.orientation.z;
   doc["accX"] = accX;
   doc["accY"] = accY;
   doc["accZ"] = accZ;
   doc["vibration"] = vibrationValue;


    // serialize the JSON object as a string
      String data;
      serializeJson(doc, data);

      // send the data from the Arduino to the mobile app
      SerialNina.write(data.c_str());
      delay(1000);
    }
      // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
   


    //  WiFiClient client = server.available();
    // if (client) {
    //   String request = "";
      
    //   // Read the HTTP request
    //   while (client.connected()) {
    //     if (client.available()) {
    //       char c = client.read();
    //       request += c;
          
    //       if (c == '\n') {
    //         break;
    //       }
    //     }
    //   }

    // // Send an HTTP response
    // client.println("HTTP/1.1 200 OK");
    // client.println("Content-Type: text/html");
    // client.println();
    // client.println("<h1>Hello from Arduino Nano 33 IoT!</h1>");
    
    // // Close the connection
    // client.stop();
  }


    // Serial.println("Client connected");
    // client.println("HTTP/1.1 200 OK");
    // client.println("Content-type:text/html");
    // client.println();
  
    // client.print("<html><head><style>");
    // client.print("body { font-family: Arial; background-color: #f0f0f0; }"); // Change the background color of the body
    // client.print("h1 { color: #333; text-align: center; }"); // Center-align the h1 element
    // client.print("table { border-collapse: collapse; width: 80%; margin: auto; }"); // Set the width of the table to 80% and center it on the page
    // client.print("th, td { text-align: left; padding: 8px; border-bottom: 1px solid #ddd; }"); // Add a bottom border to table cells
    // client.print("tr:hover { background-color: #f5f5f5; }"); // Change the background color of table rows on hover
    // client.print("</style></head><body>");

    // client.print("<h1>Sensor Data</h1>");
    // client.print("<table>");
    // client.print("<tr><th>Acceleration X</th><td>");
    // client.print(accX);

    // client.print("</td></tr>");
    // client.print("<tr><th>Acceleration Y</th><td>");
    // client.print(accY);

    // client.print("</td></tr>");
    // client.print("<tr><th>Acceleration Z</th><td>");
    // client.print(accZ);

    // client.print("</td></tr>");
    // client.print("<tr><th>Vibration</th><td>");
    // client.print(vibrationValue);
    
    // client.print("</td></tr>");
    // client.print("</table>");
    // client.print("</body></html>");
    // client.println();
    // client.stop();
  // }
}

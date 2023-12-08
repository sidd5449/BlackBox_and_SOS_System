#include <WiFiNINA.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Arduino_LSM6DS3.h>
#include<ArduinoJson.h>
// #include "arduino_secrets.h"

unsigned long startTime;


char ssid[] = "Realme 3 Pro"; // put this sensitive info in secrets.h file
char pass[] = "Abhishek55";   // put this sensitive info in secrets.h file
int status = WL_IDLE_STATUS;
const int vibrationPin = A0;
const int chipSelect = 4;
StaticJsonDocument<200> doc; 
char jsonBuffer[512]; 
WiFiServer server(80);
// data send to mongoDB cluster 
// HttpClient http;

void setup() {
  Serial.begin(9600);
  while (status != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Connected to WiFi network");
  
  while (!Serial);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("IMU sensor initialized");
  
  pinMode(vibrationPin, INPUT);
  Serial.println("Vibration sensor initialized");

  // Start the server
  server.begin();

 // you're connected now, so print out the status:
  // printWifiStatus();  

  // Record start time
   startTime = millis();
}


void loop() {

 // Check if more than 5 minutes have passed
   if (millis() - startTime > (2 * 60 *1000)) {
     // Exit loop function
     return;
   }

    // Start the local server
    // server.begin();
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);


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

   // Check for incoming client connections
    WiFiClient client = server.available();
    
    if (client) {
      Serial.println("Client connected");
  
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) {
          char  c = client.read();
          Serial.write(c);

          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the HTTP request has ended,
          // so you can send a reply
          if (c == '\n' && currentLineIsBlank) {
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
          }  

           if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;         
        } else if (c != '\r') {
          // you're gotten a character on the current line
          currentLineIsBlank = false;          
        }        
        
       

        }
   }
   // give the web browser time to receive the data
      delay(1);
      
      // Send JSON object as string to client
      String json;
      serializeJson(doc,json); 
      client.println(json); 
      client.flush();

      Serial.println("Data sent");
    
    // close the connection
    client.stop();
    Serial.println("client disconnected");

  }
}
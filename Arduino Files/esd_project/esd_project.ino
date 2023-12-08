// Final code , don't try to change anyline in the code 

#include <SPI.h>
// #include <Arduino_LSM6DS3.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>
SoftwareSerial esp8266(8, 7); // RX, TX
// #include "arduino_secrets.h" 

MPU6050 mpu;

const int sensorPin = A7;
const int lm35Pin = A5;

char ssid[] = "vivo-19";        // your network SSID (name)
char pass[] = "Siddhesh@5449";        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)


bool imuInitialized = false;
bool accStatus = true, gyroStatus = true;

// flag for detecting danger
bool isDangerDetected = false;

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Wire.begin();
  pinMode(sensorPin, INPUT);
  esp8266.begin(9600);
  Serial.println("ESP8266 Communication Established!");
  
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // check for the WiFi module:
  // if (WiFi.status() == WL_NO_MODULE) {
  //   Serial.println("Communication with WiFi module failed!");
  //   // don't continue
  //   while (true);
  // }

  // String fv = WiFi.firmwareVersion();
  // if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
  //   Serial.println("Please upgrade the firmware");
  // }

  // attempt to connect to WiFi network:
  // Serial.print("Creating access point named: ");
  // Serial.println(ssid);
  // status = WiFi.beginAP(ssid, pass);
  // if (status != WL_AP_LISTENING) {
  //   Serial.println("Creating access point failed");
  //   // don't continue
  //   while (true);
  //   }

    // wait 10 seconds for connection:
    delay(10000);


// Begin the server  
  // server.begin();

// Initialize the IMU  
  // if (!IMU.begin()) {
  //   Serial.println("Failed to initialize IMU!");
  //   accStatus = false;
  //   gyroStatus = false;
  //   imuInitialized = false;

  //   // while (1);
    
  // } else {
  //   // accStatus = IMU.accelerationAvailable();
  //   // gyroStatus = IMU.gyroscopeAvailable();
  //   imuInitialized = true;

  // }
    
// Print the WiFi status
  // printWifiStatus();
}


void loop() {
// Read the acceleration and gyroscope data
      
  int16_t accX, accY, accZ, gyX, gyY, gyZ;
  mpu.getMotion6(&accX, &accY, &accZ, &gyX, &gyY, &gyZ);
  int vib = digitalRead(sensorPin);
  int sensorValue = analogRead(lm35Pin);

  // Convert the analog voltage to temperature in degrees Celsius
  float temperatureC = (sensorValue * 5.0 / 1024) * 100;
 

  // Check if the acceleration or gyroscope values exceed certain thresholds
  if (abs(accX) > 20 || abs(accY) > 20 || abs(accZ) > 20 || abs(gyX) > 100 || abs(gyY) > 100 || abs(gyZ) > 100 || temperatureC>80) {
    
    // Danger detected
    isDangerDetected = true;
    
  } else {
    // No danger detected
    isDangerDetected = false;
  }
  
  // Create a JSON object with the acceleration and gyroscope data, and the danger flag
  JSONVar data;  
  data["accX"]=accX;
  data["accY"]=accY; 
  data["accZ"]=accZ; 
  data["gyX"]=gyX; 
  data["gyY"]=gyY; 
  data["gyZ"]=gyZ;
  data["Temperature"] = temperatureC;  
  data["Vibration"] = vib;
  data["accStatus"] = accStatus;
  data["gyroStatus"] = gyroStatus;
  data["danger"] = isDangerDetected;

  

  // Convert the JSON object to a string
  String dataStr = JSON.stringify(data);
  
  // Listen for incoming clients

  sendData(dataStr);

  delay(1);
  
}

// void printWifiStatus() {
  
//   // print the SSID of the network you're attached to:
//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());

//   // print your board's IP address:
//   IPAddress ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);

//   // print the received signal strength:
//   long rssi = WiFi.RSSI();
//   Serial.print("signal strength (RSSI):");
//   Serial.print(rssi);
//   Serial.println(" dBm");
// }

void sendData(String data) {
  // Send data to ESP8266
  esp8266.println("AT+CWJAP='vivo-1906','Siddhesh@5449'");
  esp8266.println("AT+CIPSTART=\"TCP\",\"api-endpoint-url\",80");
  delay(1000);

  String postRequest = "POST /api/endpoint HTTP/1.1\r\n";
  postRequest += "Host: api-endpoint-url\r\n";
  postRequest += "Content-Type: application/json\r\n";
  postRequest += "Content-Length: " + String(data.length()) + "\r\n\r\n";
  postRequest += data;
  
  String sendCmd = "AT+CIPSEND=";
  sendCmd += String(postRequest.length());
  esp8266.println(sendCmd);
  delay(1000);

  esp8266.print(postRequest);
  delay(1000);

  esp8266.println("AT+CIPCLOSE");
}
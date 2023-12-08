// Final code , don't try to change anyline in the code 

#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <Adafruit_Sensor.h>
#include <ArduinoHttpClient.h>
// please enter your sensitive data in the Secret tab/arduino_secrets.h
#include "arduino_secrets.h" 

const int analogPinLM35 = A0;

Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
SoftwareSerial gsmSerial(7, 8);  // RX, TX for GSM

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)
const char serverName[] = "192.168.116.149";  // server name
int port = 6001;
int status = WL_IDLE_STATUS;

// WiFiServer server(80);
WiFiClient wifi;
HttpClient client = HttpClient( wifi, serverName, port );
// int status = WL_IDLE_STATUS;

bool imuInitialized = false;
bool accStatus = true, gyroStatus = true;

// flag for detecting danger
bool isDangerDetected = false;

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  gsmSerial.begin(9600);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

    // wait 10 seconds for connection:
    // delay(10000);


// Begin the server  
  // server.begin();

// Initialize the IMU  
  // if (!mpu.begin()) {
  //   Serial.println("Failed to initialize IMU!");
  //   accStatus = false;
  //   gyroStatus = false;
  //   imuInitialized = false;

  //   // while (1);
    
  // } else {
  //   accStatus = true;
  //   gyroStatus = true;
  //   imuInitialized = true;

  // }
    
// Print the WiFi status
  printWifiStatus();
}


void loop() {
// Read the acceleration and gyroscope data
  int sensorValue = analogRead(analogPinLM35);
  float temperature = (sensorValue * 0.48828125);  // LM35 output is in 10mV per degree Celsius
  float accX, accY, accZ, gyX, gyY, gyZ;
  sensors_event_t a, g, temp;
  
  if(imuInitialized) {
    
    
    mpu.getEvent(&a, &g, &temp);

    accX = a.acceleration.x;    
    accY = a.acceleration.y;    
    accZ = a.acceleration.z;    
    gyX = g.gyro.x;    
    gyY = g.gyro.y;    
    gyZ = g.gyro.z;    
  }
 

  // Check if the acceleration or gyroscope values exceed certain thresholds
if (abs(accX) > 20 || abs(accY) > 20 || abs(accZ) > 20 || abs(gyroX) > 100 || abs(gyroY) > 100 || abs(gyroZ) > 100) {
  isDangerDetected = true;
  
  // Send SMS
  sendSMS("Emergency Detected!", "Location: Latitude, Longitude");
} else {
  isDangerDetected = false;
}


while (gsmSerial.available()) {
  char c = gsmSerial.read();
  Serial.write(c);
}
  // Read GPS data
  float gpsLatitude, gpsLongitude;
  if (readGPSData(gpsLatitude, gpsLongitude)) {
    // GPS data is valid, use it as needed
  }

  // Create a JSON object with the acceleration and gyroscope data, and the danger flag
  JSONVar data;  
  data["accX"]=accX;
  data["accY"]=accY; 
  data["accZ"]=accZ; 
  data["gyX"]=gyX; 
  data["gyY"]=gyY; 
  data["gyZ"]=gyZ;
  data["temperature"] = temperature;
  data["accStatus"] = accStatus;
  data["gyroStatus"] = gyroStatus;
  data["danger"] = isDangerDetected;
  data["gpsLatitude"] = gpsLatitude;
  data["gpsLongitude"] = gpsLongitude;

  // Convert the JSON object to a string
  String dataStr = JSON.stringify(data);
  
  // Listen for incoming clients
  makePostRequest(dataStr);
}
void makePostRequest(String payload) {
  String contentType = "application/json";

  client.post( "/post", contentType, payload );

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  Serial.print( "Status code: " );
  Serial.println( statusCode );
  String response = client.responseBody();
  Serial.print( "Response: " );
  Serial.println( response );

  Serial.println( "Wait 30 seconds" );
  delay( 3000 );
}

void printWifiStatus() {
  
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

bool readGPSData(float &latitude, float &longitude) {
  while (gsmSerial.available()) {
    if (gps.encode(gsmSerial.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        return true; // GPS data is valid
      }
    }
  }
  return false; // GPS data is not valid or not available
}

void sendSMS(const char* phoneNumber, const char* message) {
  gsmSerial.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.print(message);
  delay(100);
  gsmSerial.write(26);  // Send CTRL+Z to indicate the end of the message
  delay(1000);
}

// Final code , don't try to change anyline in the code 

#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <MPU6050.h>
// #include "arduino_secrets.h" 

MPU6050 mpu;



char ssid[] = "vivo-1906";        // your network SSID (name)
char pass[] = "Siddhesh@5449";        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

bool imuInitialized = false;
bool accStatus = true, gyroStatus = true;

// flag for detecting danger
bool isDangerDetected = false;

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  
  // Verify connection
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

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
  Serial.print("Creating access point named: ");
  Serial.println(ssid);
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
    }

    // wait 10 seconds for connection:
    delay(10000);


// Begin the server  
  server.begin();

// Initialize the IMU  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    accStatus = false;
    gyroStatus = false;
    imuInitialized = false;

    // while (1);
    
  } else {
    accStatus = IMU.accelerationAvailable();
    gyroStatus = IMU.gyroscopeAvailable();
    imuInitialized = true;

  }
    
// Print the WiFi status
  printWifiStatus();
}


void loop() {
// Read the acceleration and gyroscope data
      
  int16_t accX, accY, accZ, gyX, gyY, gyZ;
  mpu.getMotion6(&accX, &accY, &accZ, &gyX, &gyY, &gyZ);
 

  // Check if the acceleration or gyroscope values exceed certain thresholds
  if (abs(accX) > 20 || abs(accY) > 20 || abs(accZ) > 20 || abs(gyX) > 100 || abs(gyY) > 100 || abs(gyZ) > 100) {
    
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
  data["accStatus"] = accStatus;
  data["gyroStatus"] = gyroStatus;
  data["danger"] = isDangerDetected;

  // Convert the JSON object to a string
  String dataStr = JSON.stringify(data);
  
  // Listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    
    // an HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply

        if (c == '\n' && currentLineIsBlank) {
          
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");        // the connection will be closed after completion of the response
          client.println("Refresh: 5");               // refresh the page automatically every 5 sec
          client.println();
          
          // client.println("<!DOCTYPE HTML>");
          // client.println("<html>");
          
          // output the value of each analog input pin
          client.print(dataStr);
          
          //   client.println("<br />");
          // client.println("</html>");
          break;
        }
        
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
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
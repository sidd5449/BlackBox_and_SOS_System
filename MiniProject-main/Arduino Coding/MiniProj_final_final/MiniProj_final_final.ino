#include <WiFiNINA.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Arduino_LSM6DS3.h>
#include <ArduinoJson.h>

unsigned long startTime;

char ssid[] = "Realme 3 Pro";
char pass[] = "Abhishek55";
int status = WL_IDLE_STATUS;
const int vibrationPin = A0;
const int chipSelect = 4;
StaticJsonDocument<200> doc;
char jsonBuffer[512];
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Connected to WiFi network");

  while (!Serial)
    ;
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("IMU sensor initialized");

  pinMode(vibrationPin, INPUT);
  Serial.println("Vibration sensor initialized");

  // Start the server
  server.begin();

  // Record start time
  startTime = millis();
}

void loop()
{

  // Check if more than 5 minutes have passed
  if (millis() - startTime > (5 * 60 * 1000))
  {
    // Exit loop function
    return;
  }

  sensors_event_t event;
  float accX, accY, accZ, gyroX, gyroY, gyroZ;
  int vibrationValue = analogRead(vibrationPin);

  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration(accX, accY, accZ);
    delay(100);
  }
  else
    IMU.end();

  if (IMU.gyroscopeAvailable())
  {
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

  if (client)
  {
    Serial.println("Client connected");

    // Send JSON object as string to client
    String json;
    serializeJson(doc, json);
    client.println(json);
    client.flush();

    Serial.println("Data sent");
  }
}
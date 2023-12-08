#include <WiFiNINA.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Arduino_LSM6DS3.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

unsigned long startTime;

char ssid[] = "Your WiFi SSID";
char pass[] = "Your WiFi Password";
int status = WL_IDLE_STATUS;
const int vibrationPin = A0;
StaticJsonDocument<200> doc;
char jsonBuffer[512];
WiFiClientSecure wifiClient;
PubSubClient mqttClient("your-mqtt-broker.com", 8883, wifiClient);

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

  // Load root CA certificate into WiFi client
  wifiClient.setCACert(cacert);

  // Connect to MQTT broker
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("arduino-client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }

  // Record start time
  startTime = millis();
}

void loop()
{

  // Check if 30 seconds have passed
  if (millis() - startTime < (30 * 1000))
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

  doc.clear();
  doc["x"] = event.orientation.x;
  doc["y"] = event.orientation.y;
  doc["z"] = event.orientation.z;
  doc["accX"] = accX;
  doc["accY"] = accY;
  doc["accZ"] = accZ;
  doc["vibration"] = vibrationValue;

  // Serialize JSON object to buffer
  serializeJson(doc, jsonBuffer);

  // Publish JSON object to MQTT broker
  if (mqttClient.connected()) {
    mqttClient.publish("sensor-data", jsonBuffer);
    Serial.println("Sent data:");
    Serial.println(jsonBuffer);
  } else {
    Serial.println("MQTT client disconnected");
  }

  // Record start time for next 30-second interval
  startTime = millis();

  delay(1000);
}

// Root CA certificate for your MQTT broker
const char* cacert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFzDCCAbQCCQDgepN

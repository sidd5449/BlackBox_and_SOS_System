#include <ArduinoBLE.h>

void setup() {
  // initialize serial communication
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
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // send data from the Arduino to the mobile app
      SerialNina.write("Hello from Arduino!");
      delay(1000);
    }
    // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
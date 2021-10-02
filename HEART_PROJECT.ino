// Health_IoT_Project created by Theocharis Theocharidis on 24.06.2021

#include <ArduinoBLE.h>

#define HEART_SERVICE_UUID  "180D"                      // This is the Services' UUID for Heart Rate Service
#define HEART_SERVICE_CHARACTERISTIC_UUID  "2A37"       //" This is the Service Characteristic's UUID for Heart Rate Measurement
#define AD8232_SENSOR_PIN A0 //Sensor attached to this Arduino's BLE 33 Sense Pin
#define LO_PLUS_PIN 10
#define LO_MIN_PIN 11
#define HEART_SENSOR_INTERVAL 200

BLEService HeartService(HEART_SERVICE_UUID );

BLEIntCharacteristic HeartCharact( HEART_SERVICE_CHARACTERISTIC_UUID, BLERead | BLENotify );

//int Value = analogRead(A0);
static unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);    // initialize serial communication
  pinMode(LO_PLUS_PIN, INPUT); // Setup for leads off detection LO +
  pinMode(LO_MIN_PIN, INPUT); // Setup for leads off detection LO -
  //while (!Serial);


  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
  */
  BLE.setLocalName("Heart Project");
  BLE.setAdvertisedService(HeartService); // add the service UUID
  HeartService.addCharacteristic(HeartCharact); // add the heart  characteristic
  BLE.addService(HeartService); // Add the heart service
  HeartCharact.writeValue( 0 ); // set initial value for this characteristic
  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:


    // while the central is connected:
    while (central.connected()) {
      long currentMillis = millis();
      if (currentMillis - previousMillis >= HEART_SENSOR_INTERVAL) {
        previousMillis = currentMillis;

        int heartSensorValue = analogRead( AD8232_SENSOR_PIN );
      HeartCharact.writeValue( heartSensorValue );
      Serial.println( heartSensorValue );

      }
    }
    // when the central disconnects, turn off the LED:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

// for the ESP32 with LionChief
// by Joseph P Rampolla, December 2022
// https://www.youtube.com/user/christmasgarden
// https://www.josephrampolla.com/

#include "BLEDevice.h"

// The remote service we wish to connect to.
static BLEUUID serviceUUID("e20a39f4-73f5-4bc4-a12f-17d1ad07a961");
// The characteristic of the remote service we are interested in.
static BLEUUID charUUID("08590f7e-db05-467e-8757-72f6faeb13d4");

static BLERemoteCharacteristic* pRemoteCharacteristic;

  
  void setup() {
    // start serial port at 1115200 bps:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  BLEDevice::init("");
  BLEClient*  pClient = BLEDevice::createClient();

  if (pClient->connect(BLEAddress("44:A6:E5:3E:79:45"))) {
    Serial.println("Connected!");
  } else Serial.println("Failed to connect");

  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.println("Failed to get service");
    return;
  } else Serial.println("Got service");

  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.println("Failed to get characteristic");
    return;
  } else Serial.println("Got characteristic");



} // End of setup.


void loop() {
   // add 0x before values sniffed by Dagan Martinez, https://github.com/Property404/lionchief-controller 
   // for his Python code.
   
  byte command[9][4] = {
    {0x00, 0x48, 0x01, 0x00 }, //   whistle on  
    {0x00, 0x48, 0x00, 0x00 }, //   whistle off
    {0x00, 0x46, 0x01, 0x00 }, // forward
    {0x00, 0x45, 0x08, 0x00 }, // speed 8 (experiment for various speed values)
    {0x00, 0x46, 0x02, 0x00 }, // reverse
    {0x00, 0x45, 0x05, 0x00 }, // speed 5
    {0x00, 0x47, 0x01, 0x00 }, //   bell on
    {0x00, 0x47, 0x00, 0x00 }, //   bell off
    {0x00, 0x45, 0x00, 0x00 } // speed 0 "stop"
  };

  Serial.println("whistle On");
  pRemoteCharacteristic->writeValue(command[0], sizeof(command[0]));

  delay(2000);

  Serial.println("Whistle Off");
  pRemoteCharacteristic->writeValue(command[1], sizeof(command[1]));
  delay(500);
  Serial.println("set to forward");
  pRemoteCharacteristic->writeValue(command[2], sizeof(command[2]));

  delay(500);

  Serial.println("speed 8");  //speed dependent on track voltage and loco, I use 15VDC
  pRemoteCharacteristic->writeValue(command[3], sizeof(command[3]));
  delay(10000);

 
  


} // End of loop

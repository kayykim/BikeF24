#include <HardwareSerial.h>
#include <TinyGPS++.h>

#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);
TinyGPSPlus gps; 

void setup() {
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial 2 starting");
}

void loop() {
  boolean newData = false;
  for (unsigned long start = millis(); millis()- start < 1000;){
    while (neogps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
      }
    }
  }

  if (newData == true){
    newData = false;
    Serial.println(gps.satellites.value());
    Serial.print("Latitude= ");
    Serial.print(gps.location.lat(), 6);
    Serial.print("Longitude= ");
    Serial.println(gps.location.lng(), 6);
  }
  else{
    Serial.println("No Data");
  }
  delay(1000);
  Serial.println("-----------------------");
}
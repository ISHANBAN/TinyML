#include <HardwareSerial.h>
#include <TinyGPSPlus.h>

// Use UART2 for GPS on GPIO16 (RX2)
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, -1);  // RX=16, TX not needed

  Serial.println("GPS Module Test - ESP32 WROVER");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());

    Serial.print("Satellites: ");
    Serial.println(gps.satellites.value());

    Serial.print("Speed (km/h): ");
    Serial.println(gps.speed.kmph());

    Serial.println("----------------------");
  }

  delay(1000);
}

#include <Arduino_HS300x.h>     // ✅ For Temperature & Humidity (HS3001)
#include <Arduino_LPS22HB.h>    // ✅ For Pressure

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initializing sensors...");

  if (!HS300x.begin()) {
    Serial.println("❌ HS300x (Temp+Humidity) sensor not found!");
    while (1);
  }

  if (!BARO.begin()) {
    Serial.println("❌ LPS22HB (Pressure) sensor not found!");
    while (1);
  }

  Serial.println("✅ All sensors initialized!\n");
}

void loop() {
  float temperature = HS300x.readTemperature();
  float humidity = HS300x.readHumidity();
  float pressure = BARO.readPressure();

  // Output in CSV format: millis,temp,humidity,pressure
  Serial.print(millis()); Serial.print(",");
  Serial.print(temperature); Serial.print(",");
  Serial.print(humidity); Serial.print(",");
  Serial.println(pressure);

  delay(5000);  // ⏲️ Wait for 5 seconds
}
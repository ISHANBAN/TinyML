#include <HardwareSerial.h>

// Use UART2 (GPIO16 = RX, GPIO17 = TX)
HardwareSerial gsmSerial(2);

void setup() {
  Serial.begin(115200);        // Debug monitor
  gsmSerial.begin(9600, SERIAL_8N1, 16, 17);  // SIM800L UART

  Serial.println("Initializing GSM module...");
  delay(1000);

  // Send basic AT command
  gsmSerial.println("AT");
  waitForResponse();

  // Check SIM presence
  gsmSerial.println("AT+CPIN?");
  waitForResponse();

  // Set SMS text mode
  gsmSerial.println("AT+CMGF=1");
  waitForResponse();

  // Set recipient number and send SMS
  gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\"");  // Replace with your number
  delay(500);
  gsmSerial.print("Hello from ESP32 via GSM!");
  delay(500);
  gsmSerial.write(26);  // CTRL+Z to send SMS
  waitForResponse();

  Serial.println("SMS Sent!");
}

void loop() {
  // Nothing in loop
}

void waitForResponse() {
  long timeout = millis() + 5000;
  while (millis() < timeout) {
    while (gsmSerial.available()) {
      char c = gsmSerial.read();
      Serial.write(c);  // Print GSM module response
    }
  }
}

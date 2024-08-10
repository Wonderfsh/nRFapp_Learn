#include <Arduino.h>
#include <Adafruit_TinyUSB.h> // for Serial
#include <Adafruit_MCP4725.h>

int adcin    = A5;
int adcvalue = 0;
float mv_per_lsb = 3600.0F/1024.0F; // 10-bit ADC with 3.6V input range
Adafruit_MCP4725 dac;  // 12-bit DAC chip

void setup() {
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb
  dac.begin(0x62);               // default I2C address? May subject to change
  Serial.println("DACbegin");
}

void loop() {
  // Get a fresh ADC value
  adcvalue = analogRead(adcin);

  // Display the results
  Serial.print(adcvalue);
  Serial.print(" [");
  Serial.print((float)adcvalue * mv_per_lsb);
  Serial.println(" mV]");

  dac.setVoltage(adcvalue, false);

  delay(100);
}


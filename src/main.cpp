#include <Arduino.h>
#include <Adafruit_VEML7700.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

void setup()
{
  // Start serial communication
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Wait for Serial Monitor to open

  // Initialize I2C communication with VEML7700
  if (!veml.begin())
  {
    Serial.println("Failed to initialize VEML7700 sensor!");
    while (1)
      ; // Stop if initialization fails
  }

  // Optional: Set gain and integration time (default is auto)
  veml.setGain(VEML7700_GAIN_1);              // 1x gain
  veml.setIntegrationTime(VEML7700_IT_800MS); // 800ms integration time

  Serial.println("VEML7700 initialized successfully!");
}

void loop()
{
  // Read lux value from VEML7700
  float lux = veml.readLux();
  Serial.print("Lux: ");
  Serial.println(lux);

  delay(1000); // Read every second
}
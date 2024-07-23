#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#define SEALEVELPRESSURE_HPA 1013.25
const float k = 1.333;

Adafruit_BME280 bme;  // BME280 sensor object using I2C interface

/**
 * @brief Initializes the BME280 sensor.
 * @details Initializes the Wire library with specified SDA and SCL pins,
 *          and begins communication with the BME280 sensor at address 0x76.
 */
void initBME() {
  Wire.begin(SDA, SCL); // Initialize I2C communication with SDA and SCL pins
  bme.begin(0x76);      // Begin communication with BME280 sensor at address 0x76
}

/**
 * @brief Reads temperature, humidity, and pressure from the BME280 sensor.
 * @details Reads temperature in Celsius, humidity in percentage, and pressure
 *          in millimeters of mercury (mmHg), adjusted for altitude.
 */
void ReadBME() {
  bmetemp = bme.readTemperature();                              // Read temperature in Celsius
  bmehumidity = bme.readHumidity();                              // Read humidity in percentage
  bmepressure = (bme.readPressure() / 100.0F) / k;  // Read pressure in hPa and convert to mmHg
}

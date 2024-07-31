#include <sys/_stdint.h>     // Include standard integer types
#include <stdint.h>          // Additional standard integer types
#include <Arduino.h>         // Arduino core library
#include <HardwareSerial.h>  // HardwareSerial library
#include <USBCDC.h>          // USB CDC library
#include "EEPROM.h"          // EEPROM library

#define EEPROM_SIZE 512      // Size of EEPROM
#define RXD1 18              // Pin for RXD1 (NEX)
#define TXD1 17              // Pin for TXD1 (NEX)
#define RXD2 6               // Pin for RXD2 (RF)
#define TXD2 7               // Pin for TXD2 (RF)
#define SDA 8                // Pin for I2C SDA
#define SCL 9                // Pin for I2C SCL
uint16_t addr_e = 0;         // Address in EEPROM

bool fanFlag    = false;     // Flag for fan status
bool lightFlag  = false;     // Flag for light status
bool MMFlag     = false;     // Flag for MM (unknown purpose)
bool sent       = false;     // Flag for data sent

int bmetemp = 0;             // BME temperature
int bmehumidity = 0;         // BME humidity
int bmepressure = 0;         // BME pressure

uint8_t i = 0;               // Counter variable
uint8_t FFCount = 0;         // FFCount variable

uint8_t wifi = OFF;          // WiFi state (ON/OFF)
uint8_t bluetooth = OFF;     // Bluetooth state (ON/OFF)
uint8_t RF0 = ON;            // State of main RF module on ESP32-S3
uint8_t airplane_mode = OFF; // Airplane mode state (ON/OFF)

const uint8_t RF = 15;       // Pin for RF module switch (ON/OFF)
const uint8_t buzzer = 10;   // Pin for buzzer

const uint8_t Red_top = 1;   // Red LED on top
const uint8_t Gre_top = 2;   // Green LED on top
const uint8_t Blu_top = 4;   // Blue LED on top

const uint8_t Red_bot = 46;  // Red LED on bottom
const uint8_t Gre_bot = 5;   // Green LED on bottom
const uint8_t Blu_bot = 16;  // Blue LED on bottom

uint8_t pageID = 0;          // Page ID from NEX
uint8_t cmpID = 0;           // Component ID from NEX
uint8_t touch = 0;           // Component touch/release from NEX
uint8_t CMD = 0;             // Data type from NEX

const unsigned long interval = 60000;  // Interval for temperature request
unsigned long prev_tm = 0;             // Previous time for interval

const unsigned long interval2 = 200;   // Interval for buzzer delay
unsigned long prev_tm2 = 0;            // Previous time for buzzer interval

const unsigned long interval3 = 120000; // Interval for unknown purpose
unsigned long prev_tm3 = 0;             // Previous time for interval3

#ifdef BME_SUPPORT
const unsigned long interval4 = 10000;  // Interval for BME sensor
unsigned long prev_tm4 = 0;             // Previous time for BME interval
#endif

// Temperature variables for page 6
int tRF1 = 0;  // Temperature of fan_1 location
int tRF2 = 0;  // Temperature of fan_2 location

uint8_t fDR1 = 0;
uint8_t sDR2 = 100;
/**
 * @brief Reset global variables related to NEX components.
 */
void reset() {
  CMD = 0;
  pageID = 0;
  cmpID = 0;
  touch = 0;
  sent      = false;
  fanFlag   = false;
  MMFlag    = false;
  lightFlag = false;
}

/**
 * @brief Output signal to piezo buzzer.
 */
void piezoOutput() {
  unsigned long currentTime = millis();
  digitalWrite(buzzer, LOW);
  if (currentTime - prev_tm2 >= interval2) {
    digitalWrite(buzzer, HIGH);
    prev_tm2 = currentTime;
  }
}

/**
 * @brief Control RF0 main state based on touch input.
 */
void Ctrl_RF0main() {
  if (touch == 1 && RF0 == OFF) {
    RF0 = ON;
    digitalWrite(RF, LOW);
    reset();
  }
  if (touch == 1 && RF0 == ON) {
    RF0 = OFF;
    digitalWrite(RF, HIGH);
    reset();
  }
}

/**
 * @brief Handle WiFi related operations based on touch input.
 */
void nex_wifi() {
  // Example placeholder functions
  // if(touch == 1 && wifi == OFF) wifi = ON; homekit_setup(); reset();
  // if(touch == 1 && wifi == ON) wifi = OFF; WiFi.; reset(); 
}

/**
 * @brief Placeholder function for Bluetooth operations.
 */
void Bluetooth() {
  // Example placeholder function
}

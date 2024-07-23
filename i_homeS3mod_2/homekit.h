#include <sys/_types.h>
////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 8: HomeKit Bridges and Bridge Accessories      //
//                                                        //
////////////////////////////////////////////////////////////

#include "HomeSpan.h"   // Include HomeSpan library
#include "DEV_LED.h"    // Include LED device library
#include <WiFi.h>       // Include WiFi library

#define RGB_BUILTIN 48  // Define the built-in RGB LED pin

const char* ssid = "darkAngel";      // Your WiFi SSID
const char* password = "julian2001"; // Your WiFi password

/**
 * @brief Initialize WiFi connection.
 */
void initWiFi() {
  WiFi.mode(WIFI_STA);  // Set WiFi mode to station
  WiFi.begin(ssid, password);  // Connect to WiFi with provided credentials
  Serial.print("Connecting to WiFi ..");
  
  // Wait until connected to WiFi
  unsigned long currentTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0); // Set RGB LED to Red
    if(currentTime>=30000)break;
  }
  
  Serial.println(WiFi.localIP());  // Print local IP address when connected
}

/**
 * @brief Setup HomeKit accessories and initialize.
 */
void homekit_setup() {
  initWiFi();  // Initialize WiFi connection
  
#ifdef DEBUG
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());  // Print WiFi signal strength if DEBUG is defined
#endif

  wifi = ON;  // Assume this updates a status for WiFi
  neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); // Set RGB LED to Green
  wifi = 1;   // Update WiFi status for nextion WiFi icon
  
  // Initialize HomeSpan with a Bridge category and name
  homeSpan.begin(Category::Bridges, "HomeSpan Bridge");
  
  // Define and add HomeKit accessories and services
  
  // Example accessory 1: Light 3
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Light 3");
  new DEV_APP(3); // Assuming DEV_APP is a custom device type
  
  // Example accessory 2: Light 4
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Light 4");
  new DEV_APP(4); // Assuming DEV_APP is a custom device type
  
  // Example accessory 3: Light 5
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Light 5");
  new DEV_APP(5); // Assuming DEV_APP is a custom device type
  
  // Example accessory 4: Garage temperature sensor
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Garage temperature");
  new DEV_TempSensor(1); // Assuming DEV_TempSensor is a custom temperature sensor
  
  // Example accessory 5: Basement temperature sensor
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Basement temperature");
  new DEV_TempSensor(2); // Assuming DEV_TempSensor is a custom temperature sensor
  
  // Example accessory 6: Garage fan
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Garage fan");
  new DEV_FAN(1); // Assuming DEV_FAN is a custom fan controller
  
  // Example accessory 7: Basement fan
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Basement fan");
  new DEV_FAN(2); // Assuming DEV_FAN is a custom fan controller
}


////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 8: HomeKit Bridges and Bridge Accessories      //
//                                                        //
////////////////////////////////////////////////////////////
#include "HomeSpan.h" 
#include "DEV_LED.h" 
#include <WiFi.h>
#define RGB_BUILTIN 48
const char* ssid = "darkAngel";    // Your WiFi SSID
const char* password = "julian2001";  // Your WiFi password

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
    Serial.print(".");
    delay(1000);
  }
 Serial.println(WiFi.localIP());
}
void homekit_setup(){
  Serial.begin(115200);
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
  wifi = 1;  // for nextion wifi icon update
  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");
  
  new SpanAccessory();                            // This first Accessory is the new "Bridge" Accessory.  It contains no functional Services, just the Accessory Information Service
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
 
  new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Light 3");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_APP(3);

new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Light 4");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_APP(4);
    
new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Light 5");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_APP(5);

new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Garage temperature");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_TempSensor(1);

new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Basement temperature");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_TempSensor(2);

new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Garage fan");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_FAN(1);               

new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Basement fan");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_FAN(2);               

}
  

  // neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
  // neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
  // If the only Service defined in the FIRST Accessory of a multi-Accessory device is the required Accessory Information Service,
  // the device is said to be configured as a "Bridge".  Historically there may have been a number of functional differences between bridge
  // devices and non-bridge devices, but since iOS 15, it's not obvious there are any differences in functionality, with two exceptions:
  
  //  1. Recall from Example 7 that the use of Characteristic::Name() to change the default name of an Accessory Tile
  //     does not work for the first Accessory defined.  The Home App always displays the default name of the first Accessory Tile
  //     as the name of the device specified in homeSpan.begin().  However, this is not an issue when implementing a device
  //     as a Bridge, since the first Accessory is nothing but the Bridge itself - having the default name match the name
  //     of the device in this case makes much more sense.  More importantly, you can now use Characteristic::Name() to change the 
  //     default name of BOTH the LED Accessory Tiles.

  //  2. Devices configured as a Bridge appear in the Home App under the main settings page that displays all Hubs and Bridges.

  // The sketch below is functionally identical to Example 7, except that instead of defining two Accessories (one for the Simple On/Off
  // LED and one for the Dimmable LED), we define three Accessories, where the first acts as the Bridge.
  
  // As usual, all previous comments have been deleted and only new changes from the previous example are shown.

  // NOTE: To see how this works in practice, you'll need to unpair your device and re-pair it once the new code is loaded.
  

  // Below we replace Category::Lighting with Category::Bridges. This changes the icon of the device shown when pairing
  // with the Home App, but does NOT change the icons of the Accessory Tiles.  You can choose any Category you like.
  // For instance, we could have continued to use Category::Lighting, even though we are configuring the device as a Bridge.

 
// } // end of setup()



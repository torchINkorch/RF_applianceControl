/*
*****       ********          
*     *     *                
*     *     *                    
*****       *******                
*    *      *                    
**    ***  ***      

*/
// WEMOS D1 MINI 4MB>>ESP8266>>80MHZ>>JDY-41]
#include "RF_Universal.h"

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  delay(1000);

  pinMode(switch_1, INPUT);
  pinMode(appliance_1, OUTPUT);
  pinMode(indicator, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

 // tempC = tempRead();
  if (Serial.available() > 0) {

      if(Serial.parseInt() == 7725577){
        paramConfig();
        if ( Config == 255)ESP.reset();
        }
    
    payload = Serial.parseInt();
    decodePayload();
  }
}
////////////

 
     


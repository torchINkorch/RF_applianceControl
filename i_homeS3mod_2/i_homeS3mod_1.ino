#define HK_SUPPORT
#define BME_SUPPORT
// #define DEBUG
#include "RF.h"
#include "functions.h"
#include "nextion.h"
#include "RGB.h"

#ifdef HK_SUPPORT
#include "homekit.h"
#endif

#ifdef BME_SUPPORT
#include "BME280.h"
#endif

/**
 * @brief Setup function called once at the beginning of the program.
 * @details Initializes serial communication, HomeKit (if supported), BME280 sensor (if supported),
 *          EEPROM, Nextion display, RF module, and buzzer.
 */
void setup() {
#ifdef DEBUG
  Serial.begin(115200); // Initialize serial communication for debugging
#endif

#ifdef HK_SUPPORT
  homekit_setup(); // Initialize HomeKit setup
#endif

#ifdef BME_SUPPORT
  initBME(); // Initialize BME280 sensor
#endif

  EEPROM.begin(EEPROM_SIZE); // Initialize EEPROM

  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1); // Initialize Serial1 for Nextion communication
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);   // Initialize Serial2 for RF module communication

  pinMode(RF, OUTPUT);         // Set RF pin as output
  digitalWrite(RF, 0x0);       // Initialize RF pin state
  pinMode(buzzer, OUTPUT);     // Set buzzer pin as output
  digitalWrite(buzzer, 0x0);   // Initialize buzzer pin state
}

/**
 * @brief Main loop function that continuously runs after setup.
 * @details Polls HomeSpan (if supported), reads BME280 sensor (if supported), handles Nextion
 *          communication, updates device states and UI based on flags and intervals.
 */
void loop() {
#ifdef HK_SUPPORT
  homeSpan.poll(); // Poll HomeSpan for updates
#endif

#ifdef BME_SUPPORT
  ReadBME(); // Read data from BME280 sensor
#endif

  unsigned long currentTime = millis(); // Get current time in milliseconds

  // Nextion communication handling
  if (Serial1.available() > 0) {
    byte array[i];
    byte Byte = Serial1.read();
    if (Byte == 'e') CMD = 65; // Command
    if (Byte == 'p') CMD = 70; // Parameter
    if (Byte == 0xff) {
      FFCount++;
      if (FFCount >= 3) {
        i = 0;
        FFCount = 0;
        array[i] = 0;

        #ifdef DEBUG
        Serial.print(pageID);
        Serial.print(cmpID);
        Serial.print(touch);
        #endif

        execute_command(); // Execute received command
      }
    } else {
      array[i] = Byte;
      i++;
    }

    if (array[1] != 0) pageID = array[1];
    if (array[2] != 0) cmpID = array[2];
    if (array[3] != 0) touch = array[3];
  }

  // Fan state handling
  if (fanFlag) {
    if (updateN) nextion_updateFstate();
    updateN = false;
    if (currentTime - prev_tm >= interval) {
      tRF1 = rf1.getTemperature();
      tRF2 = rf2.getTemperature();
      nextion_updateFtmp(tRF1, tRF2);
      prev_tm = currentTime;
    }
  }

  // Light state handling
  if (lightFlag && updateN) nextion_updateL();updateN = false;
   

  // Periodic RF state update
  if (currentTime - prev_tm3 >= interval3) {
    rf1.getRFApplianceState();
    rf2.getRFApplianceState();
    rf3.getRFApplianceState();
    rf4.getRFApplianceState();
    rf5.getRFApplianceState();
    rf6.getRFApplianceState();
    prev_tm3 = currentTime;
  }
  if(MMFlag && sent == false){
    if(rf1.getmemApplianceState() || rf2.getmemApplianceState()){
      nexsys(1, 1, 1); sent = true;
    }else nexsys(1, 1, 1); sent = true;
  }
#ifdef BME_SUPPORT
  // Main menu update for BME280 data
  if (MMFlag) {
    if (currentTime - prev_tm4 >= interval4) {
      nextion_updateMainMenu();
      prev_tm4 = currentTime;
    }
  }
#endif
}




void execute_command() {
 switch (CMD) {
    case 65:  //--------------------->touch events
      switch (pageID) {
        case 1:  //------------> page 1 lights
          switch (cmpID) {
            case 1: if (touch == 1) reset(); break; //------>standard command when exiting to non updatable page
            case 2: if (touch == 1) reset(); MMFlag = true; break; //------> main menu flag
          }
        case 2:  //------------> page main menu
          switch (cmpID) {
            case 2: nextion_updateFstate();nextion_updateFtmp(rf1.getTemperature(),rf2.getTemperature());reset();fanFlag=true;break; // enter fan page-> shift out temp
            case 3: nextion_updateL(); reset();lightFlag = true; break;
            case 4: nextion_updateDD();reset();break;
            case 5: reset(); break;
          }
        case 3:  //------------> settings page 3
          switch (cmpID) {
            case 4: nextion_updateRF();reset(); break;
            case 9: if(touch == 9)ESP.restart();break;
          }
        case 4:  //------------> page 4 lights
          switch (cmpID) {
            case 1: rf3.toggleRFApplianceState(); reset(); break;  //------> lamp_1
            case 2: rf4.toggleRFApplianceState(); reset(); break;  //------> lamp_2
            case 3: rf5.toggleRFApplianceState(); reset(); break;  //------> lamp_3 
            case 4: rf6.toggleRFApplianceState(); reset(); break;  //------> lamp_4
          }
        case 6:  //------------> page 6 fans
          switch (cmpID) {
            case 1: rf1.toggleRFApplianceState(); reset(); break;   //------> fan_1
            case 2: rf2.toggleRFApplianceState(); reset(); break;   //------> fan_2   
            //case 3: rf3.toggleRFApplianceState(); break;   //------> fan_3
          }
        case 9:
          switch(cmpID){
            case 1: Ctrl_RF0main();reset(); break;  //------> airplane mode
            case 2: Ctrl_RF0main();reset(); break;  //------> rf mode on/off
            case 3: nex_wifi();    reset(); break;    //------> wifi mode
            case 4: Bluetooth();   reset(); break;        //------> bluetooth mode
          }
        case 12:  //------------> page settings ->rf modules
          switch (cmpID) { //------> wireless rf module enable/disable
            case 1:  rf1.changeSelfState(); reset(); break;     //------> wireless rf1 en/di
            case 2:  rf2.changeSelfState(); reset(); break;     //------> wireless rf2 en/di
            case 3:  rf3.changeSelfState(); reset(); break;     //------> wireless rf3 en/di
            case 4:  rf4.changeSelfState(); reset(); break;     //------> wireless rf4 en/di
            case 5:  rf5.changeSelfState(); reset(); break;     //------> wireless rf5 en/di
            case 6:  rf6.changeSelfState(); reset(); break;     //------> wireless rf6 en/di
            // case 7:  tggRF7();   break;     //------> wireless rf7 en/di
            // case 8:  tggRF8();   break;     //------> wireless rf8 en/di
            // case 9:  tggRF9();   break;     //------> wireless rf9 en/di
            // case 10: tggRF10();  break;     //------> wireless rf10 en/di
            // case 11: tggRF11();  break;     //------> wireless rf11 en/di
            // case 12: tggRF12();  break;     //------> wireless rf12 en/di
            // case 13: tggRF13();  break;     //------> wireless rf13 en/di
            // case 14: tggRF14();  break;     //------> wireless rf14 en/di
            // case 100: rebootALL();   break; //------> reboot all at once 
          }
        case 15:  //------------> timer page ----->piezo buzzer
          switch(cmpID){
            case 1: piezoOutput(); break;
          }
      }
    break;//commands
  case 70: break;
 }
}
      

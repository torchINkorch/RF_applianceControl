#include <stdint.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <USBCDC.h>
#include "EEPROM.h"
#define EEPROM_SIZE 512
#define RXD1 18              //nex
#define TXD1 17              //nex
#define RXD2 6               //rf
#define TXD2 7               //rf
uint16_t addr_e = 0;// eeprom
//--------------------------------<
bool fanFlag = false;
uint8_t i = 0;
uint8_t FFCount = 0;
uint8_t wifi = OFF;
uint8_t bluetooth = OFF;
uint8_t RF0 = ON;               // state of main rf module on esp32s3
uint8_t airplane_mode = OFF;
//--------------------------------<
const uint8_t RF = 15;         // pin switch on/off rf module
const uint8_t buzzer = 10;     // pin buzzer pin
const uint8_t Red_top = 1;    //--->R
const uint8_t Gre_top = 2;    //--->G
const uint8_t Blu_top = 4;    //--->B
//--------------------------------<
const uint8_t Red_bot = 46;    
const uint8_t Gre_bot = 5;    
const uint8_t Blu_bot = 16;   
//***************************
 uint8_t pageID = 0;  // page ID from NEX
 uint8_t cmpID = 0;   // component ID from NEX
 uint8_t touch = 0;   // component touch release from NEX
 uint8_t CMD = 0;     // data type from NEX
//***************************
const unsigned long interval = 60000;  // temperature request interval
unsigned long prev_tm = 0;
const unsigned long interval2 = 200;  // for buzzer interval delay
unsigned long prev_tm2 = 0;
const unsigned long interval3 = 120000;  // for buzzer interval delay
unsigned long prev_tm3 = 0;
//***************************
//***************************
bool sent = false;
//*****page 6****************
 int tRF1 = 0;  // temperature of fan_1 loc
 int tRF2 = 0;  // temperature of fan_2 loc
//><---------------><--><----------------><
void reset() {
  CMD = 0;
  pageID = 0;
  cmpID = 0;
  touch = 0;
  sent = false;
  fanFlag = false;
}
//><---------------><--><----------------><

void jtag_debug(){
  Serial.print(pageID);
  Serial.print(cmpID);
  Serial.print(touch);
}
void piezoOutput(){
unsigned long currentTime = millis();
  digitalWrite(buzzer, 0x0);
  if (currentTime - prev_tm2 >= interval2){ 
    digitalWrite(buzzer, 0x1);
    prev_tm2 = currentTime;
  }
}
void Ctrl_RF0main(){
    if (touch == 1 && RF0 == OFF) {RF0 = ON;digitalWrite(RF, 0x0);reset();}
    if (touch == 1 && RF0 == ON)  {RF0  = OFF;digitalWrite(RF, 0x1);reset();}
}
void nex_wifi(){
  // if(touch == 1 && wifi == OFF)wifi = ON;homekit_setup();reset();
  // if(touch == 1 && wifi == ON)wifi = OFF;WiFi.;reset(); 
}
void Bluetooth(){};


#include <Arduino.h>
#include <EEPROM.h>
#define analog_in A0
//config
byte RFID;
byte APP_Q;
byte TMP;
byte SWS_Q;

byte Config;
const uint8_t appliance_1 = 12;  //D6
const uint8_t switch_1 = 13; //D7
const uint8_t indicator = 4; //D2
byte incom_cmd =0;
byte switch1 = 0;
int payload = 0;
int tempC;
static float steinhart;

// void read_sw_input(){
//   if(digitalRead(switch_1) == HIGH )switch1 = 0; // not pressed
//   if(digitalRead(switch_1) == LOW)switch1 = 1;  // pressed
//   if(switch1 == 0 && incom_cmd == 1)digitalWrite(appliance_1, HIGH);
//   else if(switch1 == 0 && incom_cmd == 0 )digitalWrite(appliance_1, LOW);
//   else if(switch1 == 1 && incom_cmd == 0 )digitalWrite(appliance_1, HIGH);
//   else if(switch1 == 1 && incom_cmd == 1 )digitalWrite(appliance_1, LOW);
// }


void paramConfig(){
  // [RFID]--[APP_Q]--[TMP]--[SWS_Q]

byte sampleRFID = Serial.parseInt();
if (sampleRFID >= 0 && sampleRFID <= 254) RFID = sampleRFID; EEPROM.write(0, RFID);
byte sampleAPP_Q = Serial.parseInt();
if (sampleAPP_Q >= 0 && sampleAPP_Q <= 8)APP_Q = sampleAPP_Q; EEPROM.write(1, APP_Q);
byte sampleTMP = Serial.parseInt();
if (sampleTMP >= 0 && sampleTMP <= 255){
if (sampleTMP == 0) TMP = 0;
if (sampleTMP == 255) TMP = 1;
EEPROM.write(2, TMP);
}
byte sampleSWS_Q = Serial.parseInt();
if (sampleSWS_Q >= 0 && sampleSWS_Q <= 8)SWS_Q = sampleSWS_Q; EEPROM.write(3, SWS_Q);
EEPROM.commit(); 
Config = 255;
}

























int tempRead() {
  int adc0 = analogRead(analog_in);
  float volts0 = (adc0 * 3.3) / 1023;
  float val = 3.3 / volts0 - 1;
  float resistance = 10000 / val;
  steinhart = resistance / 10000;
  steinhart = log(steinhart);
  steinhart /= 3080;  //prev = 3380
  steinhart += 1.0 / (25 + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;
  int C = round(steinhart);
  return C;
}

void switch1State_R_Frame() {
  Serial.print("SSS");
  delay(1);
  Serial.print(switch1);
  delay(1);
  Serial.print("EEE");
  Serial.println("");
}
void temp_R_Frame() {
  Serial.print("SSS");
  delay(1);
  Serial.print(steinhart);
  delay(1);
  Serial.print("EEE");
  Serial.println("");
}


void decodePayload() {
  switch (payload) {
    case 29000:
      digitalWrite(appliance_1, LOW);
      incom_cmd=0;
      analogWrite(indicator, 0);
      break;
    case 29255:
      digitalWrite(appliance_1, HIGH);
      incom_cmd=1;
      analogWrite(indicator, 127);
      break;
    case 29888:
      temp_R_Frame();
      break;
    case 29999:
      switch1State_R_Frame();
      break;
   }
}


//    (addr*100^2)+255

//if (steinhart <= -9.99) {
   // Serial.print(steinhart, 0);
    //Serial.print("       ");
    //Serial.flush();
  //} else {
    //Serial.print(steinhart, 1);
    //Serial.print("       ");
    //Serial.flush();
  //}
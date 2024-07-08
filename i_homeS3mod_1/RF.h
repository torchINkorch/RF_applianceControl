#include <sys/_stdint.h>
#include "Appliance.h"

const uint8_t ON = 1;
const uint8_t OFF = 0;

class RF{
public:
  RF(uint8_t addr, Appliance appliance, uint8_t RFstate): address(addr), assignedAppliance(appliance), RFstate(RFstate) {}

  void changeSelfState() {
    RFstate = !RFstate;
  }
  uint8_t rState() {
    return RFstate;
  }
  void assignAppliance(Appliance appliance) {
    assignedAppliance = appliance;
  }

  uint8_t getmemApplianceState() {
    return assignedAppliance.getState();
  }
  void setRFApplianceState(uint8_t state) {     // for homekit access
    if(RFstate)assignedAppliance.setState(state);
    if (assignedAppliance.getState() == OFF) sendCommand(0);
    if (assignedAppliance.getState() == ON)  sendCommand(5);
  }
  void getRFApplianceState() {
    if(RFstate)assignedAppliance.setState(sendCommand(9));
  }

  void toggleRFApplianceState() {
    assignedAppliance.toggleState();
    if(RFstate){
    if (assignedAppliance.getState() == OFF) sendCommand(0);
    if (assignedAppliance.getState() == ON) sendCommand(5);
    }
  }

  int getTemperature() {
    if(RFstate)return sendCommand(8);
    else return -1;
  }
  static RF createNewRF(Appliance appliance, uint8_t RFstate) {
    static uint16_t nextAddress = 110;
    RF newRF(nextAddress, appliance, RFstate);
    nextAddress += 10;
    return newRF;
  }

  
  private:
  uint8_t address;
  Appliance assignedAppliance;  // Added member variable of type Appliance
  uint8_t RFstate;


int sendCommand(uint8_t command) {
      Serial2.print(address + command);
      Serial2.print("\n");
      Serial2.flush();
      if( (command == 8) || (command == 9) ){
        unsigned long currentTime = millis();
        while (!Serial2.available()) {
          if (currentTime >= 1000) break;
        }
      }
      return Serial2.parseInt();
}
  
};

Appliance fan1 = Appliance::createNewAppliance(1, OFF);    // Assuming type 1 for fan
Appliance fan2 = Appliance::createNewAppliance(1, OFF);    // Assuming type 1 for fan
Appliance light1 = Appliance::createNewAppliance(2, OFF);  // Assuming type 2 for light
Appliance light2 = Appliance::createNewAppliance(2, OFF);  // Assuming type 2 for light
Appliance light3 = Appliance::createNewAppliance(2, OFF);  // Assuming type 2 for light
Appliance light4 = Appliance::createNewAppliance(2, OFF);  // Assuming type 2 for light

RF rf1 = RF::createNewRF(fan1, OFF);
RF rf2 = RF::createNewRF(fan2, OFF);
RF rf3 = RF::createNewRF(light1, OFF);
RF rf4 = RF::createNewRF(light2, OFF);
RF rf5 = RF::createNewRF(light3, OFF);
RF rf6 = RF::createNewRF(light4, OFF);



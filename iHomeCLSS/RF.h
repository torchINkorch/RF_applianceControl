#include "Appliance.h"
class RF {
  private:
    uint16_t address;
    Appliance assignedAppliance; // Added member variable of type Appliance
    uint8_t RFstate;

    int sendCommand(uint_fast8_t command) {
       Serial2.print(address + command);
       Serial2.print("\n");
       Serial2.flush();
       while (!Serial2.available()) {
         // Wait for response
       }
       return Serial2.parseInt();
    }

    void changeSelfState() {
      RFstate = !RFstate;
    }

  public:
    RF(uint16_t addr, Appliance appliance, uint8_t RFstate) : address(addr), assignedAppliance(appliance), RFstate(RFstate) {}

    // Method to assign an appliance to the RF
    void assignAppliance(Appliance appliance) {
      assignedAppliance = appliance;
    }

    // Method to get the state of the assigned appliance
    bool getApplianceState() {
      return assignedAppliance.getState();
    }

    // Method to set the state of the assigned appliance
    void setApplianceState(bool state) {
      assignedAppliance.setState(state);
    }

    // Static method to create new RF instances with incremented addresses
    static RF createNewRF(Appliance appliance, uint8_t RFstate) {
      static uint16_t nextAddress = 110;
      RF newRF(nextAddress, appliance, RFstate);
      nextAddress += 10;
      return newRF;
    }
};

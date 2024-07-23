////////////////////////////////////////////////////////////
//                                                        //
//    Class RF                                            //
//    ------------------------------------------------    //
//                                                        //
// This class represents an RF device that interacts with  //
// an Appliance, controlling its state and receiving       //
// temperature readings.                                   //
//                                                        //
////////////////////////////////////////////////////////////

#include <sys/_stdint.h>  // Standard integer types
#include "Appliance.h"    // Include Appliance class header

const uint8_t ON = 1;     // Constant representing ON state
const uint8_t OFF = 0;    // Constant representing OFF state
bool updateH = false;     // Flag for update to home
bool updateN = false;     // Flag for update to nextion

class RF {
public:
    /**
     * @brief Constructor to initialize an RF device.
     * @param addr Address of the RF device.
     * @param appliance Appliance assigned to this RF device.
     * @param RFstate Initial state of the RF device.
     */
    RF(uint8_t addr, Appliance appliance, uint8_t RFstate) : address(addr), assignedAppliance(appliance), RFstate(RFstate) {}

    /**
     * @brief Change the state of the RF device itself.
     */
    void changeSelfState() {
        RFstate = !RFstate;
    }

    /**
     * @brief Get the current state of the RF device.
     * @return Current state of the RF device (1 for ON, 0 for OFF).
     */
    uint8_t rState() {
        return RFstate;
    }

    /**
     * @brief Assign a new Appliance to the RF device.
     * @param appliance New Appliance to assign.
     */
    void assignAppliance(Appliance appliance) {
        assignedAppliance = appliance;
    }

    /**
     * @brief Get the state of the assigned Appliance.
     * @return State of the assigned Appliance (1 for ON, 0 for OFF).
     */
    uint8_t getmemApplianceState() {
        return assignedAppliance.getState();
    }

    /**
     * @brief Set the state of the assigned Appliance via RF device.
     * @param state State to set for the Appliance (1 for ON, 0 for OFF).
     *              Also sends corresponding command based on state.
     */
    void setRFApplianceState(uint8_t state) {     // for homekit access
        if (RFstate) assignedAppliance.setState(state);
        if (assignedAppliance.getState() == OFF) sendCommand(0);
        if (assignedAppliance.getState() == ON) sendCommand(5);
    }

    /**
     * @brief Get the state of the assigned Appliance via RF device.
     *        Updates the state of the Appliance based on received command.
     */
    void getRFApplianceState() {
        if (RFstate) assignedAppliance.setState(sendCommand(9));
        updateH = true;
    }

    /**
     * @brief Toggle the state of the assigned Appliance via RF device.
     *        Also updates the flag for home update.
     */
    void toggleRFApplianceState() {
        assignedAppliance.toggleState();
        updateH = true;
        if (RFstate) {
            if (assignedAppliance.getState() == OFF) sendCommand(0);
            if (assignedAppliance.getState() == ON) sendCommand(5);
        }
    }

    /**
     * @brief Get the temperature from the assigned Appliance via RF device.
     * @return Temperature read from the Appliance (if RFstate is ON), otherwise -1.
     */
    int getTemperature() {
        if (RFstate) return sendCommand(8);
        else return -1;
    }

    /**
     * @brief Static method to create a new RF device.
     * @param appliance Appliance to assign to the new RF device.
     * @param RFstate Initial state of the new RF device.
     * @return Newly created RF object.
     */
    static RF createNewRF(Appliance appliance, uint8_t RFstate) {
        static uint16_t nextAddress = 110;
        RF newRF(nextAddress, appliance, RFstate);
        nextAddress += 10;
        return newRF;
    }

private:
    uint8_t address;                ///< Address of the RF device.
    Appliance assignedAppliance;    ///< Appliance assigned to this RF device.
    uint8_t RFstate;                ///< Current state of the RF device (1 for ON, 0 for OFF).

    /**
     * @brief Send a command to the RF device and retrieve response.
     * @param command Command to send to the RF device.
     * @return Response received from the RF device.
     */
    int sendCommand(uint8_t command) {
        Serial2.print(address + command);
        Serial2.print("\n");
        Serial2.flush();
        
        // Wait for response for commands 8 and 9
        if ((command == 8) || (command == 9)) {
            unsigned long currentTime = millis();
            while (!Serial2.available()) {
                if (currentTime >= 1000) break;
            }
        }
        
        return Serial2.parseInt();
    }
};

//  instances of Appliances and RF devices
Appliance fan1 = Appliance::createNewAppliance(1, OFF);    // Type 1 for fan
Appliance fan2 = Appliance::createNewAppliance(1, OFF);    // Type 1 for fan
Appliance light1 = Appliance::createNewAppliance(2, OFF);  // Type 2 for light
Appliance light2 = Appliance::createNewAppliance(2, OFF);  // Type 2 for light
Appliance light3 = Appliance::createNewAppliance(2, OFF);  // Type 2 for light
Appliance light4 = Appliance::createNewAppliance(2, OFF);  // Type 2 for light

RF rf1 = RF::createNewRF(fan1, OFF);
RF rf2 = RF::createNewRF(fan2, OFF);
RF rf3 = RF::createNewRF(light1, OFF);
RF rf4 = RF::createNewRF(light2, OFF);
RF rf5 = RF::createNewRF(light3, OFF);
RF rf6 = RF::createNewRF(light4, OFF);

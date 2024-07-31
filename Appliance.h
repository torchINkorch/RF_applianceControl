////////////////////////////////////////////////////////////
//                                                        //
//    Class Appliance                                     //
//    ------------------------------------------------    //
//                                                        //
// This class represents an Appliance with address, type,  //
// state, and optionally temperature for type 1 (fan).     //
//                                                        //
////////////////////////////////////////////////////////////

class Appliance {
public:
    /**
     * @brief Constructor to initialize an Appliance object.
     * @param addr Address of the appliance.
     * @param type Type of the appliance.
     * @param state Initial state of the appliance.
     */
    Appliance(uint8_t addr, uint8_t type, uint8_t state) : address(addr), type(type), state(state), temperature(0) {}

    /**
     * @brief Get the current state of the appliance.
     * @return Current state (1 for ON, 0 for OFF).
     */
    uint8_t getState() {
        return state;
    }

    /**
     * @brief Set the state of the appliance.
     * @param newState New state to set (1 for ON, 0 for OFF).
     */
    void setState(uint8_t newState) {
        state = newState;
    }

    /**
     * @brief Toggle the state of the appliance.
     */
    void toggleState() {
        state = !state;
    }

    /**
     * @brief Set the temperature for type 1 appliances (fans).
     * @param newTemperature New temperature value to set.
     */
    void setTemperature(int newTemperature) {
        if (type == 1) {
            temperature = newTemperature;
        }
    }

    /**
     * @brief Static method to create a new Appliance object.
     * @param type Type of the appliance.
     * @param state Initial state of the appliance.
     * @return Newly created Appliance object.
     */
    static Appliance createNewAppliance(uint8_t type, uint8_t state) {
        static uint8_t nextAddress = 1;
        Appliance newAppliance(nextAddress, type, state);
        nextAddress++;
        return newAppliance;
    }

private:
    uint8_t address;    ///< Address of the appliance.
    uint8_t type;       ///< Type of the appliance.
    uint8_t state;      ///< Current state of the appliance (1 for ON, 0 for OFF).
    int temperature;    ///< Temperature (for type 1 appliances, such as fans).
};

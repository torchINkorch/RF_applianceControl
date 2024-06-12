class Appliance {
  private:
    uint8_t address;
    uint8_t type;
    bool state;
    int temperature; // Only applicable for type 1 (fan)

  public:
    // Constructor with address, type, and initial state
    Appliance(uint8_t addr, uint8_t type, bool state) : address(addr), type(type), state(state), temperature(0) {}

    // Method to get the state of the appliance
    bool getState() {
      return state;
    }

    // Method to set the state of the appliance
    void setState(bool newState) {
      state = newState;
    }

    // Method to get the temperature of the appliance (only applicable for type 1)
    int getTemperature() {
      if (type == 1)
        return temperature;
      else
        return -1; // Return -1 for appliances of type 2 (light)
    }

    // Method to set the temperature of the appliance (only applicable for type 1)
    void setTemperature(int newTemperature) {
      if (type == 1)
        temperature = newTemperature;
    }

    // Static method to create new Appliance instances with incremented addresses starting from 1
    static Appliance createNewAppliance(uint8_t type, bool state) {
      static uint8_t nextAddress = 1;
      Appliance newAppliance(nextAddress, type, state);
      nextAddress++;
      return newAppliance;
    }
};

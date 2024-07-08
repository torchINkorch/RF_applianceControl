
class Appliance  {
  public:
    Appliance(uint8_t addr, uint8_t type, uint8_t state) : address(addr), type(type), state(state), temperature(0) {}

    uint8_t getState() {
      return state;
    }

    void setState(uint8_t newState) {
      state = newState;
    }

    void toggleState() {
      state = !state;
      }

    void setTemperature(int newTemperature) {
      if (type == 1)
        temperature = newTemperature;
    }

    static Appliance createNewAppliance(uint8_t type, uint8_t state) {
      static uint8_t nextAddress = 1;
      Appliance newAppliance(nextAddress, type, state);
      nextAddress++;
      return newAppliance;
    }
  private:
    uint8_t address;
    uint8_t type;
    uint8_t state;
    int temperature; // Only applicable for type 1 (fan)
};

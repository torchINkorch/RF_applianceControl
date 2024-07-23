#include <sys/_stdint.h>

////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

////////////////////////////////////////////////////////////
//                                                        //
//    Lightbulb structure for HomeKit                      //
//    ------------------------------------------------    //
//                                                        //
// This structure defines a HomeKit Lightbulb service      //
// that interacts with RF appliances.                      //
//                                                        //
////////////////////////////////////////////////////////////

struct DEV_APP : Service::LightBulb {
                                    
  uint8_t applianceFlag;                ///< Flag indicating the specific appliance
  SpanCharacteristic *power;            ///< Pointer to the Power characteristic

  /**
   * @brief Constructor for DEV_APP structure.
   * @param applianceFlag Flag indicating the specific appliance.
   */
  DEV_APP(uint8_t applianceFlag) : Service::LightBulb() {
    power = new Characteristic::On();   // Initialize Power characteristic
    this->applianceFlag = applianceFlag;
  }

  /**
   * @brief Update method to set RF appliance state based on Power characteristic.
   * @return True if update was successful.
   */
  boolean update() {
    switch(applianceFlag) {
      case 3: rf3.setRFApplianceState(power->getNewVal()); updateN = true; break;
      case 4: rf4.setRFApplianceState(power->getNewVal()); updateN = true; break;
      case 5: rf5.setRFApplianceState(power->getNewVal()); updateN = true; break;
    }
    return true;
  }

  /**
   * @brief Loop method to update Power characteristic based on RF appliance state.
   */
  void loop() {
    if (updateH) {
      switch(applianceFlag) {
        case 3: power->setVal(bool(rf3.getmemApplianceState())); updateH = false; break;
        case 4: power->setVal(bool(rf4.getmemApplianceState())); updateH = false; break;
        case 5: power->setVal(bool(rf5.getmemApplianceState())); updateH = false; break;
      }
    }
  }
};

////////////////////////////////////////////////////////////
//                                                        //
//    Fan structure for HomeKit                           //
//    ------------------------------------------------    //
//                                                        //
// This structure defines a HomeKit Fan service            //
// that interacts with RF appliances.                      //
//                                                        //
////////////////////////////////////////////////////////////

struct DEV_FAN : Service::Fan {
                                    
  uint8_t applianceFlag;                ///< Flag indicating the specific appliance
  SpanCharacteristic *power;            ///< Pointer to the Active characteristic

  /**
   * @brief Constructor for DEV_FAN structure.
   * @param applianceFlag Flag indicating the specific appliance.
   */
  DEV_FAN(uint8_t applianceFlag) : Service::Fan() {
    power = new Characteristic::Active();   // Initialize Active characteristic
    this->applianceFlag = applianceFlag;
  }

  /**
   * @brief Update method to set RF appliance state based on Active characteristic.
   * @return True if update was successful.
   */
  boolean update() {
    switch(applianceFlag) {
      case 1: rf1.setRFApplianceState(power->getNewVal()); updateN = true; break;
      case 2: rf2.setRFApplianceState(power->getNewVal()); updateN = true; break;
    }
    return true;
  }

  /**
   * @brief Loop method to update Active characteristic based on RF appliance state.
   */
  void loop() {
    if (updateH) {
      switch(applianceFlag) {
        case 1: power->setVal(bool(rf1.getmemApplianceState())); updateH = false; break;
        case 2: power->setVal(bool(rf2.getmemApplianceState())); updateH = false; break;
      }
    }
  }
};

////////////////////////////////////////////////////////////
//                                                        //
//    Temperature sensor structure for HomeKit            //
//    ------------------------------------------------    //
//                                                        //
// This structure defines a HomeKit TemperatureSensor      //
// service that interacts with temperature readings.       //
//                                                        //
////////////////////////////////////////////////////////////

struct DEV_TempSensor : Service::TemperatureSensor {    

  uint8_t applianceFlag;                ///< Flag indicating the specific appliance
  SpanCharacteristic *temp;             ///< Pointer to the CurrentTemperature characteristic

  /**
   * @brief Constructor for DEV_TempSensor structure.
   * @param applianceFlag Flag indicating the specific appliance.
   */
  DEV_TempSensor(uint8_t applianceFlag) : Service::TemperatureSensor() {
    temp = new Characteristic::CurrentTemperature(-10.0);   // Initialize CurrentTemperature characteristic with a default value and expanded range
    temp->setRange(-50, 100);    // Expand the range from the default 0-100 to -50 to 100 to allow for negative temperatures
    this->applianceFlag = applianceFlag;
  }

  /**
   * @brief Loop method to update temperature based on RF appliance state.
   */
  void loop() {
    if (temp->timeVal() > 20000) {
      switch(applianceFlag) {
        case 1: temp->setVal(tRF1); break;
        case 2: temp->setVal(tRF2); break;
      }
    }
  }
};


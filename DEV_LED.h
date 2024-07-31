#include <sys/_stdint.h>
#include <sys/types.h>

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



//-----------------------------------------

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
    return(true);
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
    return (true);
  }

  /**
   * @brief Loop method to update Active characteristic based on RF appliance state.
   */
  void loop() {
    if (updateH) {
      switch(applianceFlag) {
        case 1: power->setVal(rf1.getmemApplianceState());updateH = false;  break;
        case 2: power->setVal(rf2.getmemApplianceState());updateH = false;  break;
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


struct DEV_DoorLock : Service::Door {

  
  uint8_t doornum;                ///< Flag indicating the specific appliance
  SpanCharacteristic *current;           // reference to the Current Door State Characteristic 
  SpanCharacteristic *target;             // reference to the Target Door State Characteristic
  SpanCharacteristic *obstruction;
 /**
   * @brief Constructor for DEV_DoorLock structure.
   * @param doornum  indicating the specific appliance.
   */
  DEV_DoorLock(uint8_t doornum) : Service::Door() {

    current=new Characteristic::CurrentPosition(0);      
    target=new Characteristic::TargetPosition(0);                                  
    obstruction=new Characteristic::ObstructionDetected(false);   
    this->doornum = doornum;
    obstruction->setVal(false); 
  }

  // boolean update(){
  //    if(target->getNewVal()==target->OPEN){          // HomeKit is requesting the door to be in OPEN position
  //     current->setVal(current->OPEN);            // set the current-state value to OPENING
  //     obstruction->setVal(false);                   // clear any prior obstruction detection - note we do not bother using an enumerated constant here
  //   } else {
  //    current->setVal(current->CLOSED);            // set the current-state value to CLOSING
  //    bstruction->setVal(false);                   // clear any prior obstruction detection
  //   }
  //   return(true);
  // }
  /**
   * @brief Loop method to update Active characteristic based on RF appliance state.
   */
  void loop() {
    if(updateH){
      switch(doornum){
        case 1: current->setVal(fDR1);target->getVal();updateH = false; break;
        case 2: current->setVal(sDR2);target->getVal();updateH = false; break;
      }
    }
  }

};

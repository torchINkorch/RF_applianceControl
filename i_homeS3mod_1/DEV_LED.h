
#include <sys/_stdint.h>

////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////


struct DEV_APP : Service::LightBulb {               // First we create a derived class from the HomeSpan LightBulb Service
                                    
  uint8_t applianceFlag;
  SpanCharacteristic *power;                        // here we create a generic pointer to a SpanCharacteristic named "power" that we will use below
  
  DEV_APP(uint8_t applianceFlag) : Service::LightBulb(){

    power=new Characteristic::On();                 // this is where we create the On Characterstic we had previously defined in setup().  Save this in the pointer created above, for use below
    this->applianceFlag=applianceFlag;                            
    
  } // end constructor

  boolean update(){            
   switch(applianceFlag) 
   {
    case 3: rf3.setRFApplianceState(power->getNewVal()); break;
    case 4: rf4.setRFApplianceState(power->getNewVal()); break;
    case 5: rf5.setRFApplianceState(power->getNewVal()); break;
   }
    return(true);          
  }                         
};
struct DEV_FAN : Service::Fan {               // First we create a derived class from the HomeSpan LightBulb Service
                                    
  uint8_t applianceFlag;
  SpanCharacteristic *power;                        // here we create a generic pointer to a SpanCharacteristic named "power" that we will use below
  
  DEV_FAN(uint8_t applianceFlag) : Service::Fan(){

    power=new Characteristic::Active();                 // this is where we create the On Characterstic we had previously defined in setup().  Save this in the pointer created above, for use below
    this->applianceFlag=applianceFlag;                            
    
  } // end constructor

  boolean update(){            
   switch(applianceFlag) 
   {
    case 1: rf1.setRFApplianceState(power->getNewVal()); break;
    case 2: rf2.setRFApplianceState(power->getNewVal()); break;
   }
    return(true);          
  }                         
};
struct DEV_TempSensor : Service::TemperatureSensor {    

   uint8_t applianceFlag;
   SpanCharacteristic *temp;                                      

   DEV_TempSensor(uint8_t applianceFlag) : Service::TemperatureSensor() {      

     temp = new Characteristic::CurrentTemperature(-10.0);    
     temp->setRange(-50, 100);// expand the range from the HAP default of 0-100 to -50 to 100 to allow for negative temperatures
     this->applianceFlag=applianceFlag;                            

  } // end constructor

   void loop() {

  if (temp->timeVal() > 20000) {
    switch(applianceFlag) 
    {
      case 1:  temp->setVal(tRF1); break;
      case 2:  temp->setVal(tRF2); break;
    }       // set the new temperature; this generates an Event Notification and also resets the elapsed time                          
   }
  } // loop
 };














// struct DEV_DimmableLED : Service::LightBulb {       // Dimmable LED

//   LedPin *ledPin;                                   // reference to Led Pin
//   SpanCharacteristic *power;                        // reference to the On Characteristic
//   SpanCharacteristic *level;                        // reference to the Brightness Characteristic
  
//   DEV_DimmableLED(int pin) : Service::LightBulb(){       // constructor() method

//     power=new Characteristic::On();     
                
//     level=new Characteristic::Brightness(50);       // Brightness Characteristic with an initial value of 50%
//     level->setRange(5,100,1);                       // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%

//     this->ledPin=new LedPin(pin);                   // configures a PWM LED for output to the specified pin
    
//   } // end constructor

//   boolean update(){                              // update() method
    
//     ledPin->set(power->getNewVal()*level->getNewVal());    
   
//     return(true);                               // return true
  
//   } // update
// };
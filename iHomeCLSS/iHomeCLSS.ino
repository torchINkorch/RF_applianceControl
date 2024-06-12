
#include "RF.h"

// Create instances of Appliance
Appliance fan = Appliance::createNewAppliance(1, false); // Assuming type 1 for fan
Appliance light = Appliance::createNewAppliance(2, false); // Assuming type 2 for light

// Create instances of RF and assign appliances
RF rf1 = RF::createNewRF(fan, 0); // Assign fan to RF
RF rf2 = RF::createNewRF(light, 0); // Assign light to RF

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

// Example usage of controlling the assigned appliance through RF
rf1.setApplianceState(true); // Turn on the fan assigned to rf1
rf2.setApplianceState(true); // Turn on the light assigned to rf2

// Check the state of appliances
bool fanState = rf1.getApplianceState(); // Get state of fan assigned to rf1
bool lightState = rf2.getApplianceState(); // Get state of light assigned to rf2
}

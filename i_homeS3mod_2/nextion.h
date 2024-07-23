////////////////////////////////////////////////////////////
//                                                        //
//    Nextion: Serial communication functions             //
//    ------------------------------------------------    //
//    Write to txt, number, component                     //
//                                                        //
////////////////////////////////////////////////////////////

#include <string>

const uint8_t usec = 80;  // Microsecond delay for baud rate 115200
// const uint32_t usec = 22;   // Microsecond delay for baud rate 460800
// const uint32_t usec = 11;   // Microsecond delay for baud rate 926100

/*
--------------------------------------------------------------->> NEXTION SERIAL 1 COMMUNICATION <<---------------------------------------------------------------
*/

/**
 * @brief Write text to a Nextion component.
 * @param txtnum Text component number.
 * @param txt Text to display.
 * @param delayM Whether to include an 80us delay after sending the command.
 */
void nextxt(uint8_t txtnum, String txt, uint8_t delayM) {
  Serial1.print("t");
  Serial1.print(txtnum);
  Serial1.print(".txt=\"");
  Serial1.print(txt);
  Serial1.print("\"");
  Serial1.print("\xFF\xFF\xFF");
  if (delayM == 1) delayMicroseconds(usec);
}

/**
 * @brief Write a number to a Nextion component.
 * @param numnum Number component number.
 * @param value Value to display.
 * @param delayM Whether to include an 80us delay after sending the command.
 */
void nexnum(uint8_t numnum, int value, uint8_t delayM) {
  Serial1.print("n");
  Serial1.print(numnum);
  Serial1.print(".val=");
  Serial1.print(value);
  Serial1.print("\xFF\xFF\xFF");
  if (delayM == 1) delayMicroseconds(usec);
}

/**
 * @brief Write a boolean value to a universal component on Nextion.
 * @param component Component name.
 * @param value Boolean value to set.
 * @param delayM Whether to include an 80us delay after sending the command.
 */
void nexcmp(String component, bool value, uint8_t delayM) {
  Serial1.print(component);
  Serial1.print(".val=");
  Serial1.print(value);
  Serial1.print("\xFF\xFF\xFF");
  if (delayM == 1) delayMicroseconds(usec);
}

void nexsys(uint8_t sysnum, uint8_t value, uint8_t delayM){
  Serial1.print("sys");
  Serial1.print(sysnum);
  Serial1.print("=");
  Serial1.print(value);
  Serial1.print("\xFF\xFF\xFF");
  if (delayM == 1) delayMicroseconds(usec);
}
/**
 * @brief Set the baud rate of the Nextion display.
 * @param Baudrate Baud rate value to set.
 */
void nextionSetBaud(uint32_t Baudrate) {
  Serial1.print("bauds=");
  Serial1.print(Baudrate);
  Serial1.print("\xFF\xFF\xFF");
}

#ifdef BME_SUPPORT
/**
 * @brief Update the main menu of the Nextion display with BME sensor data.
 */
void nextion_updateMainMenu() {
  nexnum(0, bmetemp, 1);
  nexnum(1, bmehumidity, 1);
  nexnum(2, bmepressure, 1);
}
#endif

/**
 * @brief Update the fan temperature display on the Nextion display.
 * @param t1 Temperature value for fan 1.
 * @param t2 Temperature value for fan 2.
 */
void nextion_updateFtmp(int t1, int t2) {
  nexnum(0, t1, 1);
  nexnum(1, t2, 1);
}

/**
 * @brief Update the state of fan menu switches on the Nextion display.
 */
void nextion_updateFstate() {
  if (!sent) {
    rf1.getRFApplianceState();
    rf2.getRFApplianceState();
    sent = true;
  }
  nexcmp("sw0", rf1.getmemApplianceState(), 1);
  nexcmp("sw1", rf2.getmemApplianceState(), 1);
}

/**
 * @brief Update the state of lamp menu switches on the Nextion display.
 */
void nextion_updateL() {
  nexcmp("sw0", rf3.getmemApplianceState(), 1);
  nexcmp("sw1", rf4.getmemApplianceState(), 1);
  nexcmp("sw2", rf5.getmemApplianceState(), 1);
  nexcmp("sw3", rf6.getmemApplianceState(), 1);
}

/**
 * @brief Update the state of RF settings switches on the Nextion display.
 */
void nextion_updateRF() {
  nexcmp("sw0", rf1.rState(), 1);
  nexcmp("sw1", rf2.rState(), 1);
  nexcmp("sw2", rf3.rState(), 1);
  nexcmp("sw3", rf4.rState(), 1);
  nexcmp("sw4", rf5.rState(), 1);
  nexcmp("sw5", rf6.rState(), 1);
  // Uncomment below lines as needed for more RF switches
  // nexcmp("sw6", RF7, 1);
  // nexcmp("sw7", RF8, 1);
  // nexcmp("sw8", RF9, 1);
  // nexcmp("sw9", RF10, 1);
  // nexcmp("sw10", RF11, 1);
  // nexcmp("sw11", RF12, 1);
  // nexcmp("sw12", RF13, 1);
  // nexcmp("sw13", RF14, 1);
}

/**
 * @brief Update the state of various digital display buttons on the Nextion display.
 */
void nextion_updateDD() {
  nexcmp("bt0", airplane_mode, 1);
  nexcmp("bt1", RF0, 1);
  nexcmp("bt2", bluetooth, 1);
  nexcmp("bt3", wifi, 1);
}


#include <string>
const uint32_t usec = 80;//baud 115200
//const uint32_t usec = 22;//baud 460800
//const uint32_t usec = 11;//baud 926100
/*
--------------------------------------------------------------->> NEXTION SERIAL 1 COMMUNICATION <<---------------------------------------------------------------
*/


/*------------->>> text ASCII out <<<*/
void nextxt(uint8_t txtnum, String txt, uint8_t delayM)   // 1- 80us delay included , 0- excluded
{
Serial1.print("t");
Serial1.print(txtnum);
Serial1.print(".txt=\"");
Serial1.print(txt);
Serial1.print("\"");
Serial1.print("\xFF\xFF\xFF");
if(delayM == 1)delayMicroseconds(usec);
}
//><---------------><--><----------------><
/*------------->>> number ASCII out <<<*/
void nexnum(uint8_t numnum, int value, uint8_t delayM)   // 1- 80us delay included , 0- excluded
{
Serial1.print("n");
Serial1.print(numnum);
Serial1.print(".val=");
Serial1.print(value);
Serial1.print("\xFF\xFF\xFF");
if(delayM == 1)delayMicroseconds(usec);else{};
}//><---------------><--><----------------><

/*------------->>> universal component value ASCII out <<<*/
void nexcmp(String component, bool value, uint8_t delayM)   // 1- 80us delay included , 0- excluded
{
Serial1.print(component);
Serial1.print(".val=");
Serial1.print(value);
Serial1.print("\xFF\xFF\xFF");
if(delayM == 1)delayMicroseconds(usec);
}//><---------------><--><----------------><

void nextionSetBaud(uint32_t Baudrate){
  Serial1.print("bauds=");
  Serial1.print(Baudrate);
  Serial1.print("\xFF\xFF\xFF");
}


//><---------------><--><----------------><

void nextion_updateFtmp(int t1, int t2) {
  nexnum(0,t1,1);
  nexnum(1,t2,1);
}
//><---------------><--><----------------><
/*------------->>> fan menu state update <<<*/

void nextion_updateFstate()
{
  if(sent == !true){
    rf1.getRFApplianceState();
    rf2.getRFApplianceState();
    sent = true;
  }
  nexcmp("sw0", rf1.getmemApplianceState(), 1);
  nexcmp("sw1", rf2.getmemApplianceState(), 1);
}
//><---------------><--><----------------><
/*------------->>> lamp menu state update <<<*/

void nextion_updateL()
{
nexcmp("sw0", rf3.getmemApplianceState(), 1);
nexcmp("sw1", rf4.getmemApplianceState(), 1);
nexcmp("sw2", rf5.getmemApplianceState(), 1);
nexcmp("sw3", rf6.getmemApplianceState(), 1);
}
//><---------------><--><----------------><
/*------------->>> RF SETTINGS state update <<<*/
void nextion_updateRF(){
nexcmp("sw0", rf1.rState(), 1);
nexcmp("sw1", rf2.rState(), 1);
nexcmp("sw2", rf3.rState(), 1);
nexcmp("sw3", rf4.rState(), 1);
nexcmp("sw4", rf5.rState(), 1);
nexcmp("sw5", rf6.rState(), 1);
// nexcmp("sw6", RF7, 1);
// nexcmp("sw7", RF8, 1);
// nexcmp("sw8", RF9, 1);
// nexcmp("sw9", RF10, 1);
// nexcmp("sw10", RF11, 1);
// nexcmp("sw11", RF12, 1);
// nexcmp("sw12", RF13, 1);
// nexcmp("sw13", RF14, 1);
}
void nextion_updateDD(){
nexcmp("bt0", airplane_mode, 1);
nexcmp("bt1", RF0, 1);
nexcmp("bt2", bluetooth, 1);
nexcmp("bt3", wifi, 1);
}

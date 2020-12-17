/*
****************************
Convertisseur SUMD vers USB
****************************

Quick and durty basé sur les examples des 2 projets suivants :

RC NAVY => http://p.loussouarn.free.fr (déjà inclu)
Joystick Master => https://github.com/MHeironimus/ArduinoJoystickLibrary/archive/master.zip (in the Arduino IDE, select `Sketch` > `Include Library` > `Add .ZIP Library...`.)

Cablage:
 .---------------.              .----------------------.           .------------------.  
 |  RC Receiver  |              |    Leonardo/MEGA     |           |       PC         |
 |               |              |                      |           |                  | 
 |           Alim+------------->+ Raw                  |           |                  | 
 |               |              |                      |           |                  | 
 |    SUMD Signal+------------->+ Serial1 Rx           |           | (Joystick HID)   |
 |               |              |                   USB+-----------+USB               |
 |            Gnd+--------------+ Gnd                  | USB cable |                  |
 |               |              |                      |           |                  |
 '---------------'              '----------------------'           '------------------'

*/
#include "RcBusRx.h"
#include "Joystick.h"

// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 0, 0,
  true, true, true, true, true, true,
  false, false, false, false, false);


void setup()
{
  // Set Range Values
  Joystick.setXAxisRange(8800, 15200);
  Joystick.setYAxisRange(8800, 15200);
  Joystick.setZAxisRange(8800, 15200);
  Joystick.setRxAxisRange(8800, 15200);
  Joystick.setRyAxisRange(8800, 15200);
  Joystick.setRzAxisRange(8800, 15200);
  
  Joystick.begin();
  
  while(!Serial);
  Serial.begin(115200); /* For serial console output */
  Serial.println(F("RcBusRx configured in SUMD receiver\n"));
  
  Serial1.begin(SUMD_RX_SERIAL_CFG); /* Choose your serial and select xxxx__RX_SERIAL_CFG (list in RcBusRx.h) where xxxx is the protocol */

  RcBusRx.serialAttach(&Serial1);    /* Then, attach the SUMD receiver to this Serial1 */
  RcBusRx.setProto(RC_BUS_RX_SUMD);  /* Select here the serial protocol */
}

void loop()
{
  RcBusRx.process(); /* Don't forget to call the RcBusRx.process()! */
  Joystick.setXAxis(RcBusRx.rawData(1));
  Joystick.setYAxis(RcBusRx.rawData(2));
  Joystick.setZAxis(RcBusRx.rawData(3));
  Joystick.setRxAxis(RcBusRx.rawData(4));
  Joystick.setRyAxis(RcBusRx.rawData(5));
  Joystick.setRzAxis(RcBusRx.rawData(6));
}

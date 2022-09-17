//-------------------------------------------------------------------------------------
// HX711_ADC.h
// Arduino master library for HX711 24-Bit Analog-to-Digital Converter for Weigh Scales
// Olav Kallhovd sept2017
// Tested with      : HX711 asian module on channel A and YZC-133 3kg load cell
// Tested with MCU  : Arduino Nano
//-------------------------------------------------------------------------------------
// This is an example sketch on how to use this library for two ore more HX711 modules
// Settling time (number of samples) and data filtering can be adjusted in the config.h file

#include "HX711_ADC.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string> 

//pins:
const int HX711_dout            = 19; //mcu > HX711 no 1 dout pin 24
const int HX711_sck             = 20; //mcu > HX711 no 1 sck pin  26
unsigned long t                 = 0;

//HX711 constructor (dout pin, sck pin)
HX711_ADC LoadCell(HX711_dout, HX711_sck); //HX711 4

int main() {

  usleep(10E3);

  printf("Starting...\n");

  float calibrationValue        = 34.00; // uncomment this if you want to set this value in the sketch
  unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  bool _tare                    = true; //set this to false if you don't want tare to be performed in the next step
  uint8_t loadcell_rdy          = 0;
  
  LoadCell.begin();
  while (!loadcell_rdy) { //run startup, stabilization and tare, both modules simultaniously
    if (!loadcell_rdy) loadcell_rdy = LoadCell.startMultiple(stabilizingtime, _tare);
  }

  LoadCell.setCalFactor(calibrationValue); // user set calibration value (float)
 printf("Startup is complete\n");


while(1) {

  static bool newDataReady   = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) { newDataReady = true; }

  //get smoothed value from data set
  if ((newDataReady)) {
    if (LoadCell.millis() > t + serialPrintInterval) {
      float a = LoadCell.getData();
      a = a / 10;
      printf("Weight:%.2f\n",a);
      newDataReady = 0;
      t = LoadCell.millis();
    }
  }
  //check if last tare operation is complete
  if (LoadCell.getTareStatus() == true) {
    printf("Tare load cell complete.\n");
  }
}
return 0;
}


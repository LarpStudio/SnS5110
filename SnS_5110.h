#ifndef _SNS_5110_H
#define _SNS_5110_H

#define RST 5
#define CE 4
#define DC 12
#define DIN 13
#define CLK 15

#include<Arduino.h>
#include "ASCIIfont.h"

class SnS5110 {
  public:
    //--------------------------------- public functions ---------------------------------
    void Init(byte rst, byte ce, byte dc, byte din = MOSI, byte clk = SCK);
    void Hello(); //demo function
    void XY(byte x, byte y); //set cursor to position X,Y ,0 <= x <= 83 ,0 <= y <= 5
    void WriteCharacter(char character); //print single character to cursor position
    void WriteCString(char *cString); //print character array to cursor position
    void Clear();

  private:
    //--------------------------------- private variables ---------------------------------
    uint8_t reset = NULL;
    uint8_t chipEnable = NULL;
    uint8_t dataCommand = NULL;
    uint8_t dataIn = NULL;
    uint8_t clock = NULL;

    //--------------------------------- private functions ---------------------------------
    void writeCmd(byte cmd);
    void writeData(byte dat);

};

#endif //_SNS_5110_H

#include "SnS_5110.h"

//--------------------------------- PUBLIC ---------------------------------
void SnS5110::Hello() {
  this->Clear();
  XY(8, 2);
  WriteCString("Hello world!");
}

void SnS5110::Clear() {
  for (int i = 0; i < 504; i++)writeData(0x00); //clear LCD
}

void SnS5110::Init() {
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);

  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);

  //writeCmd(0x00); //NOP, debug purposes

  writeCmd(0x21); // LCD extended commands
  writeCmd(0xB8); // set LCD Vop (contrast) default B8
  writeCmd(0x04); // set temp coefficent
  writeCmd(0x14); // LCD bias mode 1:40
  writeCmd(0x20); // LCD basic commands
  writeCmd(0x0C); // LCD normal video
  //writeCmd(0x09); // LCD all segments on, for debug purposes

  this->Clear();
  //for (int i = 0; i < 504; i++)WriteData(0x00); //clear LCD
}

// set cursor to X,Y position
void SnS5110::XY(byte x, byte y) { //0 <= x <= 83 ,0 <= y <= 5
  writeCmd(0x80 | x); //column
  writeCmd(0x40 | y); //row
}

void SnS5110::WriteCharacter(char character) { //print out single character
  for (byte i = 0; i < 5; i++) writeData(ASCII[character - 0x20][i]);
  writeData(0x00);
}

void SnS5110::WriteCString(char *cString) { //print out character array
  while (*cString) WriteCharacter(*cString++);
}

//--------------------------------- PRIVATE ---------------------------------
void SnS5110::init(byte a) {

}

void SnS5110::writeData(byte dat) {
  digitalWrite(DC, HIGH); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
  digitalWrite(CE, HIGH);
}

void SnS5110::writeCmd(byte cmd) {
  digitalWrite(DC, LOW); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}








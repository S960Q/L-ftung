// Display samples of fonts.
//
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

const char* fontName[] = {
  "Arial14",
  "Arial_bold_14",
  "Callibri11",
  "Callibri11_bold",
  "Callibri11_italic",
  "Callibri15",
  "Corsiva_12",
  "fixed_bold10x15",
  "font5x7",
  "font8x8",
  "Iain5x7",
  "lcd5x7",
  "Stang5x7",
  "System5x7",
  "TimesNewRoman16",
  "TimesNewRoman16_bold",
  "TimesNewRoman16_italic",
  "utf8font10x16",
  "Verdana12",
  "Verdana12_bold",
  "Verdana12_italic",
  "X11fixed7x14",
  "X11fixed7x14B",
  "ZevvPeep8x16"
};
const uint8_t* fontList[] = {
  /*
    Arial14,
  Arial_bold_14,
  Callibri11,
  Callibri11_bold,
  Callibri11_italic,
  Callibri15,
  Corsiva_12,
  fixed_bold10x15,
  font5x7,
  font8x8,
  */
  //Iain5x7,
  //lcd5x7,
  //Stang5x7,
  //System5x7,
  //TimesNewRoman16,
  //TimesNewRoman16_bold,
  
  //utf8font10x16,
  //Verdana12,
  //Verdana12_bold,
  //Verdana12_italic,
  //X11fixed7x14,
  //X11fixed7x14B,
  //ZevvPeep8x16
  
};
uint8_t nFont = sizeof(fontList) / sizeof(uint8_t*);

SSD1306AsciiWire oled;
//Arial_bold_14
//------------------------------------------------------------------------------
void setup() {
    Wire.begin();
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
    oled.set400kHz();

    oled.setFont(TimesNewRoman16);
    oled.write("TEst");
   delay(5000);
    

}
void loop() {}
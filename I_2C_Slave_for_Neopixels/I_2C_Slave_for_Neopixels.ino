/*
   rosserial Servo Control Example

   This sketch demonstrates the control of hobby R/C servos
   using ROS and the arduiono

   For the full tutorial write up, visit
   www.ros.org/wiki/rosserial_arduino_demos

   For more information on the Arduino Servo Library
   Checkout :
   http://www.arduino.cc/en/Reference/Servo
*/
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#include <Adafruit_NeoPixel.h>
#include <Wire.h>


#define PIN        6
#define NUMPIXELS 20

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 2, 2, PIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE +
                            NEO_TILE_TOP + NEO_TILE_RIGHT + NEO_TILE_COLUMNS + NEO_TILE_PROGRESSIVE,
                            NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

int inp;
int x    = matrix.width();
int pass = 0;
bool task = false;
String string = "";


void scroll(String text) {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(text);
  if (--x < -80) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
    task =  false;
  }
  matrix.show();
  delay(100);
}

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  //Wire.onRequest(requestEvent);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
  matrix.setTextSize(2);
  Serial.begin(9600);
}

void loop() {
  delay(1);
  //delay(1);
  
  

}

void receiveEvent(int howMany) {
  task = true;
  while (0 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    string.concat(c);
  }
  Serial.println(string);
  while(task){
  scroll(string);
  }
  string = "";
  //inp = Wire.read();
  //Serial.println(inp);
  // Send the updated pixel colors to the hardware.
}

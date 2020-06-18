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


#define PIN        6 //data output pin
#define NUMPIXELS 20

//the block of code below is to set up such that the running text display will be displayed correctly according to our own configuration of LED matrices
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

//code block below takes in the a string and displays the running text on the neopixel matrices

void scroll(String text) {
  matrix.fillScreen(0); //fills screen with a single colour
  matrix.setCursor(x, 0); // set cursor set cursor location which is where the top left lixel will go
  matrix.print(text);
  if (--x < -80) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
    task =  false; // set task to false when sine it is finished
  }
  matrix.show();
  delay(100);
}

void setup() {
  Wire.begin(8);                // join i2c bus with address #8 this number should be the same in the wire.begintTransmission() code for the Master
  Wire.onReceive(receiveEvent); // activates callback function recieveEvent() when data is recieved
  //Wire.onRequest(requestEvent);
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
  matrix.setTextSize(2); //ext characters are set to 8 pixels high by default. Setting this to 2 means the text will now be 16 pixels high
  Serial.begin(9600); // set Serial baud rate to 9600.. important for serial monitor usage
}

void loop() {
  delay(1);
  //delay(1);
  

}

void receiveEvent(int howMany) { //callback function 
  task = true; // set task to true
  while (0 < Wire.available()) { // loop through all the bytes available for retrival
    char c = Wire.read(); // receive byte as a character
    string.concat(c); // concatinate the characters
  }
  Serial.println(string); // serial print the message recieved
  while(task){
  scroll(string); //run the scroll function while the task is true
  }
  string = ""; // set the variable to an empty string to clear the message
  //inp = Wire.read();
  //Serial.println(inp);
  // Send the updated pixel colors to the hardware.
}

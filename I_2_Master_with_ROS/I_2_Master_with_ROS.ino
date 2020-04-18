#include <Wire.h>
#include <ros.h>
#include<Arduino.h>
#include <std_msgs/String.h>
#include<std_msgs/UInt16.h>

ros::NodeHandle  nh;



void led_cb(const std_msgs::String& cmd_msg) {
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(cmd_msg.data);        // sends five bytes
    //Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    //x++;
    delay(1000);
    //Wire.requestFrom(8, 8);    // request 8 bytes from slave device #8
    //while (Wire.available()) { // slave may send less than requested
    //int c = Wire.read(); // receive a byte as character
    //Serial.print(c);         // print the character
    //}
    //Serial.println();
    delay(5000);
    
  }


ros::Subscriber<std_msgs::String>sub("led", led_cb);

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  Wire.begin();

}

void loop() {
  nh.spinOnce();

}

#include <Wire.h> //wire is a library that allows you to communicate I2C devices
#include <ros.h> //ROS library
#include<Arduino.h>
#include <std_msgs/String.h>
#include<std_msgs/UInt16.h>

ros::NodeHandle  nh; // initialising a ROS nodehandler class called nh which allows our program to create publishers and subscribers. The node handle also takes care of serial port communications.



void led_cb(const std_msgs::String& cmd_msg) { // callback function that is to be activated every a message is recieved about the topic
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(cmd_msg.data);        //sends cmd_msg.data which is a string
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


ros::Subscriber<std_msgs::String>sub("led", led_cb); // subscribe to the topic "led" and execute the call back led_cb upon recieving a message

void setup() {
  nh.initNode(); // initialises ROS node
  nh.subscribe(sub); // setup he subscriber. argument must be the same as the one written in line 30
  Wire.begin(); //

}

void loop() {
  nh.spinOnce(); //will call all the callbacks waiting to be called at that point in time.

}

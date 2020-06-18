# NEOPIXEL MATRIX - ROS

This project involves the integration of ROS and Arduino so as to recieve a message from ROS and display animation/text on the matrix display attached to the MOMO robot.
The display will flash green arrow keys when the robot is moving and red colour when it is stopping. It also allows for a scrolling text message to be displayed on it, of which the text will be sent from a webpage using ROS Server.

## Overview
![Overview](images/ros_diagram.jpg "Overview")

**Figure 1.1: The Big Picture**

## Hardware

2 set of Arduino Unos and a total of 12 8x8 Neopixel matrices would be used, with 6 on the side panels of the MOMObot. The matrices are configured in a 3x2 position. The Serial Interface is connected to ROS and the Webpage, via ROS Server, where the message to displayed is recieved. The Arduino used as the serial interface is connected to the other arduino used as a display interface (via I2C), communicating via pins A4 and A5. Pin 6 is the data pin that is routed to the Neopixel matrices.

![Breadboard layout](images/breadboard.jpg "Breadboard layout")

**Figure 1.2: Breadboard layout**

![Schematics](images/schematics.jpg "Schematics")

**Figure 1.3 Schematics**


## Software
The repository would be split into 2 sections: Arduino & Web section.
### Arduino
In the repository, there are 2 set of Arduino code:
- **I_2C_Master:** This set of code is for the Arduino Uno that runs as a _I2C Master_ (Serial Interface) as well as a Rosserial-Arduino Node subscribed to the "led" ROS Topic. It relays the messages from the ROS topic to the Slave via I2C.
- **I_2C_Slave:** This Arduino Uno runs as an _I2C Slave_ (Display Interface) which recieves the message from the master in bytes and the executes the scrolling text function which displays the string sent over on the Neopixel Matrix display.

### Web
There is also a set of HTML, CSS & JS code for a webpage which is connected to the ROS Mastere via ROS Server. This webpage allows a person to send messages to be displayed onto the Neopixel Matrix.








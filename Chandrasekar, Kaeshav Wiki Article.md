# Using the Ultrasonic Sensor and Bluetooth Module on an Arduino to Measure Acceleration

## Introduction
	In this article, we will discuss how to use an Arduino, Bluetooth module, and ultrasonic sensor, and how they can be integrated to measure the acceleration of the apparatus.  Arduino is an electronics platform that provides user-friendly hardware and software for development. The platform consists of a simple microcontroller board and a development environment that enables users to write, upload and run code written in the Arduino Programming Language on the board. Arduino boards are compatible with a slew of sensors, actuators and other components, making them ideal for a variety of projects, from simple hobby projects such as this ultrasound sensor project, to more complex and demanding applications. Bluetooth is a wireless technology that enables communication between devices over short distances. It has become a popular technology for connecting devices due to its low power consumption and ease of use. Bluetooth communication is prevalent in many of today’s devices, such as headphones, smart home devices, and wearables. To enable Bluetooth communication on the Arduino platform, a Bluetooth communication module is used. The Arduino Bluetooth module is a compact module that enables the Arduino board to communicate with other Bluetooth devices. In this article, we will explore the basics of Bluetooth technology and how it is used with the Arduino platform. We will also look at how the Arduino Bluetooth module can be used to enable Bluetooth communication in Arduino projects, and some of the popular applications and use cases for this module. Ultrasonic sensors are a type of distance measurement device that operate the same way a bat’s echolocation does. It outputs high frequency sound waves and detects when they are bounced. The time of flight that it takes for the sound wave to return to the sensor is used with the speed of sound to back-calculate the distance of the sensor to the object. The simplicity of ultrasonic sensors makes them easy to integrate into many applications, such as this one. Integrating the Arduino, Bluetooth module, and this ultrasonic sensor, we can easily build a project that can have many uses. 		

## Materials
1.	Arduino Uno R3
a.	Arduino programming cable
2.	HC-06 Bluetooth Module
3.	HC-SR04 Ultrasonic Sensor
4.	Jumper wires
5.	Arduino Prototyping Shield with Tiny Breadboard
6.	Computer with Bluetooth capability
	
 
## Getting Started
Our first goal is to get started with the Bluetooth module and communicate between the Arduino and the computer. Let us begin by physically connecting the Arduino to the computer through this port with the cable that comes with the kit:
 

Next, we want to install the Arduino IDE so we can program the Arduino Uno. Follow this link to install the IDE: Software | Arduino

Once installed, open the development environment and select the Arduino Uno as the primary board. 
 

If the Arduino is properly connected to the computer, the option to select it as the COM port of choice will be available. For example, it should look like this:
 
Select the COM port that has the Arduino/Genuino Uno listed next to it. Now, the computer knows to send and receive data from the Arduino through this physical port. 


We will now test if the Arduino is properly functioning with the example code available in the IDE. One of the benefits of using the Arduino development environment is the built-in example codes that are provided to test some basic and advanced functionality of the Arduino. Navigate to the top bar and select the “Blink” code file under “Basics”:
 
Select this code example and the following should appear:
 
To upload this code to the Arduino that is currently plugged in, click on the forward arrow in the top bar:
 
The progress on the compilation and upload should appear towards the bottom of the page:
 
After this, the LED on the Arduino should start blinking repeatedly on for one second, then off for one second. If this works properly, then the Arduino is perfectly ready to be used for the rest of our project. 



Bluetooth Module 
The next step in our journey to measuring acceleration is setting up the Bluetooth module. Prepare the prototyping shield with tiny breadboard, jumper wires, and Arduino. 
Place the shield on top of the Arduino, snapping it into place such that the orientation is like so:
 




Use the jumper wires to connect the Bluetooth module as follows:
 

Once this is properly connected, the red LED on the Bluetooth module should begin blinking. This means that the module is ready to be paired with the computer. Open your computer’s Bluetooth pairing setting and the default name of the device “HC-06” should appear. The password for pairing to this device is “1234”. After it is paired, the red LED should become a solid red light. 
At this point, we can upload the following Bluetooth test code to make sure that the module is working as expected. 
 


The output of this test should be the following:

*Insert Output*

The initial setup of the Bluetooth module will be tricky; however it is crucial to this project, so ensure that this step is fully complete before moving onto the subsequent steps. 

## Ultrasonic Sensor
*insert ultrasonic sensor testing plan*

## Sending Ultrasonic Sensor Data via Bluetooth
*insert integration and test of the previous two sections*

## Final Experiment Setup
*insert test plan about the final experiment using the setup from the previous section + data collection*

## Data Analysis
*insert data analysis steps*

## Conclusion
*insert conclusion* 


Sources:
-	Arduino and Bluetooth module HC-06 • AranaCorp
-	Arduino Tutorial - Lesson 3 - Breadboards and LEDs (ladyada.net)
-	Ultrasonic Sensor HC-SR04 and Arduino - Complete Guide (howtomechatronics.com)




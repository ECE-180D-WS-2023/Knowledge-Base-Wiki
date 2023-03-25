# Using the Ultrasonic Sensor and Bluetooth Module on an Arduino to Measure Acceleration

## Introduction

In this article, we will discuss how to integrate an Arduino, Bluetooth module, and ultrasonic sensor, to measure acceleration.  Arduino is an electronics platform that provides user-friendly hardware and software for development. The platform consists of a simple microcontroller board and a development environment that enables users to write, upload and run code written in the Arduino Programming Language on the board. Arduino boards are compatible with a slew of sensors, actuators and other components, making them ideal for a variety of projects, from simple hobby projects such as this ultrasound sensor project, to more complex and demanding applications. Bluetooth is a wireless technology that enables communication between devices over short distances. It has become a popular technology for connecting devices due to its low power consumption and ease of use. Bluetooth communication is prevalent in many of today’s devices, such as headphones, smart home devices, and wearables. The Arduino Bluetooth module is a compact module that enables the Arduino board to communicate with other Bluetooth devices. Ultrasonic sensors are distance measurement devices that operate the same way a bat’s echolocation does. It outputs high frequency sound waves and detects when they are bounced, as seen in Figure 1. The time of flight that it takes for the sound wave to return to the sensor is used with the speed of sound to back-calculate the distance of the sensor to the object. The simplicity of ultrasonic sensors makes them easy to integrate into many applications. Integrating the Arduino, Bluetooth module, and this ultrasonic sensor, we can build a project with many uses. 		

![image](https://user-images.githubusercontent.com/63273284/227699038-84e1fdbe-6b9a-4ced-94e2-23c6f8a144a9.png)

*Figure 1*

## Materials
1.	Arduino Uno R3
a.	Arduino programming cable
2.	HC-06 Bluetooth Module
3.	HC-SR04 Ultrasonic Sensor
4.	Jumper wires
5.	Arduino Prototyping Shield with Tiny Breadboard
6.	Computer with Bluetooth capability
7.	4x AA Battery Pack
8.	Spool of thin string

	
 
## Getting Started
Our first goal is to get started with the Bluetooth module and communicate between the Arduino and the computer. Let us begin by physically connecting the Arduino to the computer through this port with the cable that comes with the kit in Figure 2:
 
![image](https://user-images.githubusercontent.com/63273284/227655103-8c6e75ab-e506-43a9-88cd-3eb2cb7b476a.png)

*Figure 2*

Next, we want to install the Arduino IDE so we can program the Arduino Uno. Follow this link to install the IDE: https://www.arduino.cc/en/software/

Once installed, open the development environment and select the Arduino Uno as the primary board. 
 
![image](https://user-images.githubusercontent.com/63273284/227655216-3b23f6aa-0e00-4b30-83d7-46d4ef940d6b.png)

*Figure 3*

If the Arduino is properly connected to the computer, the option to select it as the COM port of choice will be available. For example, it should look like Figure 4. 
 
![image](https://user-images.githubusercontent.com/63273284/227655237-0a3db7e6-e0a8-4c21-8fff-a3af0a71e132.png)

*Figure 4*
 
Select the COM port that has the Arduino/Genuino Uno listed next to it. Now, the computer knows to send and receive data from the Arduino through this physical port. 


We will now test if the Arduino is properly functioning with the example code available in the IDE. One of the benefits of using the Arduino development environment is the built-in example codes that are provided to test some basic and advanced functionality of the Arduino. Navigate to the top bar and select the “Blink” code file under “Basics”, seen in Figure 5. 
 
![image](https://user-images.githubusercontent.com/63273284/227655257-917494c4-a171-4bd7-af25-2f0319952bd5.png)

*Figure 5*
 
Select this code example and the file in Figure 6 should appear. 
 
![image](https://user-images.githubusercontent.com/63273284/227655272-f58fdea9-2001-4ce7-85b6-2fd46587c96e.png)

*Figure 6*
 
To upload this code to the Arduino that is currently plugged in, click on the forward arrow in the top bar, seen in Figure 7. 
 
![image](https://user-images.githubusercontent.com/63273284/227655282-b6e4ab69-4956-4d47-84b7-5ff29dd84d1d.png)

*Figure 7*
 
The progress on the compilation and upload should appear towards the bottom of the page, seen in Figure 8. 
 
![image](https://user-images.githubusercontent.com/63273284/227655296-7aca8d0f-0eab-424d-985b-d30ca59ebd11.png)

*Figure 8*

After this, the LED on the Arduino should start blinking repeatedly on for one second, then off for one second. If this works, then the Arduino will be ready for the rest of the project. 


## Bluetooth Module 
The next step in our journey to measuring acceleration is setting up the Bluetooth module. Locate the prototyping shield with tiny breadboard, jumper wires, battery pack, and Arduino. 
Place the shield on top of the Arduino, snapping it into place such that the orientation is as seen in Figure 9. 
 
![image](https://user-images.githubusercontent.com/63273284/227655321-51f6ed62-be37-4618-af84-0181397d90a0.png)

*Figure 9*

Use the jumper wires to connect the Bluetooth module as seen in Figure 10:
 
![image](https://user-images.githubusercontent.com/63273284/227655349-02898207-fd43-493a-afd2-c67f94c668f9.png)

*Figure 10*

Once this is properly connected, the red LED on the Bluetooth module should begin blinking. This means that the module is ready to be paired with the computer. Open your computer’s Bluetooth pairing setting and the default name of the device “HC-06” should appear. The password for pairing to this device is “1234”. After it is paired, the red LED should become a solid red light. 
A successful Bluetooth connection will show the Bluetooth LED as a solid red. At this point, we can upload the following Bluetooth test code to make sure that the module is working as expected. 
 
``` C
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(10,11); //RX, TX

```

Once this code is uploaded to the Arduino, disconnect the Arduino from the computer and connect the battery pack to the Arduino as follows:

![image](https://user-images.githubusercontent.com/63273284/227689401-bcab07a8-db35-46ab-bf43-1d0a3acd0104.png)

After connecting, the Bluetooth LED should begin blinking again. Follow the aforementioned steps to connect the Bluetooth module to the computer. Once the Bluetooth LED is solid red, open the serial monitor for the appropriate COM port for the Bluetooth connection. This can be found through trial and error of the various COM ports available in the "Port" dropdown menu under "Tools". This step is similar to selecting the appropriate COM port for the Arduino in an earlier step. 

The serial monitor can be opened after selecting the COM port under the "Tools" tab. The output on the serial monitor after connecting to the Bluetooth module should contain the following string: "Hello, SoftwareSerial ready". 

The initial setup of the Bluetooth module will be tricky; however it is crucial to this project, so ensure that this step is fully complete before moving onto the subsequent steps. EXPLAIN WHY TRICKY

## Ultrasonic Sensor
The ultrasonic sensor is how we will be measuring the acceleration of the Arduino apparatus. The output of the ultrasonic sensor is the distance away from a target in front of it after including a calibration factor. The ultrasonic sensor should be electrically connected to the Arduino as follows:

![image](https://user-images.githubusercontent.com/63273284/227689758-e9118a27-a5d0-4c22-9e03-f54b6f622cc2.png)

After connecting the sensor's echo and trig pins to ports 3 and 2 respectively, we must implement the data reading and output to the serial monitor through the Bluetooth module. The following code should be uploaded to the Arduino to implement the ultrasonic sensor readings to the serial monitor:

Pre-setup:

![image](https://user-images.githubusercontent.com/63273284/227689825-b2973a4e-b794-46b3-bdf7-4eedb824e385.png)

Setup:

![image](https://user-images.githubusercontent.com/63273284/227689837-585c5c86-1806-404c-a0d7-d0e93e060d6c.png)

Loop:

![image](https://user-images.githubusercontent.com/63273284/227689869-e5864968-e3b6-455a-ab12-753775dfcb31.png)

Note: In this loop, the aforementioned calibration from the raw ultrasonic sensor output to centimeter output is included. 

Connect the Arduino to the computer and upload the code above. 

## Sending Ultrasonic Sensor Data via Bluetooth
Now that the ultrasonic sensor and Bluetooth code has been uploaded, disconnect the Arduino from the computer and connect the battery pack to the Arduino. Once again pair the Bluetooth module to the computer as mentioned in earlier steps. Open the serial monitor after choosing the correct COM port. The serial monitor should read the distance values from the ultrasonic sensor in the following format:

![image](https://user-images.githubusercontent.com/63273284/227690637-88e927bf-2786-41ea-b346-aac7a5685660.png)

The first number in each row is the time in milliseconds since the program began running, and the second number is the calibrated sensor output in centimeters. By moving the ultrasonic sensor back and forth, the second reading should change, and the first reading should increment by 1 each millisecond. If this output has been obtained, then the hardware setup is successful!

## Final Experiment
In order to measure the acceleration of the setup, we will carefully drop the Arduino apparatus to measure the acceleration of Earth's gravity. Tie a rope around the Arduino apparatus such that it can be suspended with the ultrasonic sensor facing downard 

## Data Analysis
*insert data analysis steps*

## Conclusion
*insert conclusion* 


Sources:
-	Arduino and Bluetooth module HC-06 • AranaCorp
-	Arduino Tutorial - Lesson 3 - Breadboards and LEDs (ladyada.net)
-	Ultrasonic Sensor HC-SR04 and Arduino - Complete Guide (howtomechatronics.com)
-	How to run an Arduino (clone) on (AA) batteries for over a year - Part 2 | Hardware Setup (https://hwstartup.wordpress.com/2013/04/15/how-to-run-an-arduino-clone-on-aa-batteries-for-over-a-year-part-2/)
-	fritzing.org (https://fritzing.org/projects/)
-	UCLA Physics 4AL




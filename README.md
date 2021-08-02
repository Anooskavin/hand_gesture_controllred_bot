# hand_gesture_controllred_bot

CIRCUIT CONFIGURATIONS

1 RECEIVER CIRCUIT OF HAND GESTURE BOT

![image](https://user-images.githubusercontent.com/53963293/127822078-a2b3985b-efb2-40de-ac6c-357618e5241a.png)


Fig. 1 Receiver circuit of Hand Gesture Bot


2. TRANSMITTER CIRCUIT OF HAND GESTURE BOT

![image](https://user-images.githubusercontent.com/53963293/127822119-48f3a04a-c9ac-450b-a003-720e1be48444.png)


Fig. 2 Transmitter circuit of Hand Gesture Bot

ASSEMBLY 
1. COMPONENTS USED IN TRANSMITTER PART
S.No.
Component Name
Specification
Quantity
(Nos.)
1.
Gyroscope sensor 
 MPU6050
1
2.
Arduino 
 UNO
1
3.
Battery
 9V
1
4.
Bluetooth module
 HC-05
1
5.
Jumper wires
Male-Female 
10
6.
Hand glove
Gym glove
1

(* nano\ lilypad-can also be used)

MPU 6050: 
.
MPU-6050
Pin 
Arduino Pin 
(Connected in)
VCC
5V
GND
GND
SCL
A5
SDA
A4
XDA
  -
XCL
    •  
ADD
    • 
INT
  2


Bluetooth(HC-05):

HC-05
Pin 
Arduino Pin
(Connected in)
VIN
5V
GND
GND
TXD
10
RXD
11
STATE
  -
EN
    •  
Arduino UNO:
              Arduino is used for connecting the above Bluetooth module , 9V battery and MPU-6050 by using jumper cables.
Hand glove:
     These overall components or fixed over hand glove for controlling the bot.

![image](https://user-images.githubusercontent.com/53963293/127822194-7e08c6a0-9e57-4040-809c-bfb4e263a380.png)


Fig . 3 transmitter part with wirings


2 COMPONENTS USED IN RECEIVER PART

S.No.
Component Name
Specification
Quantity
(Nos.)
1.
Motor driver.
 L298N
1
2.
Bluetooth module  
HC-05
1
3.
Two wheel with DC motor.
 RC WHEELS
1
4.
Arduino 
Uno 
1
5.
Jumper wires
Male-Female 
10
6.
Chasis
Made of cardboard
1
7.
Battery
9V
2



Bluetooth(HC-05):

HC-05
Pin 
Arduino Pin
(Connected in)
VIN
5V
GND
GND
TXD
10
RXD
11
STATE
  -
EN
    •  

Motor drive (L298N):
L298N Pin 
     Connected in
2 OUTPUTS
RC wheels with DC motor
GND
GND
+9V / +5V 
VIN
Arduino : 
              Arduino is used for connecting the above Bluetooth module , 9V battery , motor drive by using jumper cables.

![image](https://user-images.githubusercontent.com/53963293/127822241-1313483e-2457-4b32-9daf-9a47205df392.png)

        Fig. 4 receiver part with wirings


TESTING  




MOVING ACCELERATION:
![image](https://user-images.githubusercontent.com/53963293/127822324-58da3428-25bd-437a-8aa9-8b3d7ce389c1.png)

X - x axis ; Y - y axis
1.Stop (S)       : (x>=45 && x<=55); 
                          (y>=145&&y<=155)   
2.Right (R)      : (x>60); 
3.Left (L)         :  (x<40);                
4.Forward (F)    : (y>160);
5.Backward (B) :(y<140).


DISTANCE SPECIFICATION

![image](https://user-images.githubusercontent.com/53963293/127822369-5ac82036-e825-44a8-9352-2f616953d9f7.png)

                                          It  covers  the  distance about 6 to 8 metres.

APPENDIX  -  1
PAIRING OF BLUETOOTH
For Slave

    1. Connect Bluetooth module HC-05 with the Arduino Rx, Tx, Vcc, GND
    2. Upload an empty program in the Arduino
    3. Push and hold the reset button to the Bluetooth module and power the Bluetooth module and thus the Bluetooth module enters AT mode (blinking of LED once per 2 seconds denotes this) 
    4. Now, open the serial monitor of the Arduino IDE.
    5. Send some command like
    • AT( displays OK)
    • AT+ROLE=0(to slave the Bluetooth, which displays OK)
    • AT+UART (displays the baud rate) 
    • AT+UART=3800,0,0(to set the baud rate at 38400).
    • Type AT+ADDR(displays the address of slave            Bluetooth module) and copy the address of the slave module.

For Master 

    1. Connect Bluetooth module HC-05 with the Arduino Rx, Tx, Vcc, GND
    2. upload an empty program in the Arduino
    3. Push and hold the reset button to the Bluetooth module and power the Bluetooth module.
    4. Now, open the serial monitor of the Arduino IDE.
    5. Send some command like 
    • AT( displays OK)
    • AT+ROLE=1(to master the Bluetooth, which displays OK)
    • AT+UART (displays the baud rate) 
    • AT+UART=3800,0,0(to set the baud rate at 38400).
    • AT+BIND= paste the copied address of the slave module(use commas instead of colons) 

On powering the modules they start dual blinking per two seconds, which denotes that the modules have paired.



APPENDIX  -  2
TROUBLE SHOOTING
       After completion if there is no output,
    • Check the jumpers.
    • Confirm the pairing of Bluetooth and check whether there is output from the master.
    • Confirm the working of gyroscope by opening the serial monitor.
    • Working of arduino.

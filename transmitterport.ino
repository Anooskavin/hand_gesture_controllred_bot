//libraried to be included:
//1)helper_3dmath.h
//2)I2Cdev.h
//3)I@Cdev.cpp
//4)MPU6050.cpp
//5)MPU6050.h
//6)MPU6050_6Axis_MotionApps20.h
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementationis used in I2Cdev.h
#include "Wire.h"

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN

#define OUTPUT_READABLE_YAWPITCHROLL
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13
MPU6050 mpu;
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  
uint8_t mpuIntStatus;   
uint8_t devStatus;      
uint16_t packetSize;    
uint16_t fifoCount;    
uint8_t fifoBuffer[64];

// orientation/motion vars
Quaternion q;          
VectorFloat gravity;    
float ypr[3];          
float pitch = 0;
float roll = 0;
float yaw = 0;
int x;
int y;


volatile bool mpuInterrupt = false;     
void dmpDataReady() {
  mpuInterrupt = true;
}


void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

 
  Serial.begin(115200);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  
  while (!Serial);
  
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(126);
  mpu.setYGyroOffset(57);
  mpu.setZGyroOffset(-69);
  mpu.setZAccelOffset(1869);
  //almost all MPU6050's have the same output

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
}


void loop() {
  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  
  while (!mpuInterrupt && fifoCount < packetSize) {
   
  }

 
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  
  fifoCount = mpu.getFIFOCount();

  
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
 } else if (mpuIntStatus & 0x02) {
while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount(); mpu.getFIFOBytes(fifoBuffer, packetSize);
 fifoCount -= packetSize;
#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    yaw = ypr[0] * 180 / M_PI;
    pitch = ypr[1] * 180 / M_PI;
    roll = ypr[2] * 180 / M_PI;

    if (roll > -100 && roll < 100)
      x = map (roll, -100, 100, 0, 100);

    if (pitch > -100 && pitch < 100)
      y = map (pitch, -100, 100, 100, 200);

    Serial.print(x);
    Serial.print("\t");
    Serial.println(y);

    if((x>=45 && x<=55) && (y>=145 && y <=155)){
      BTSerial.write('S');
    }else if(x>60){
      BTSerial.write('R');
    }else if(x<40){
      BTSerial.write('L');
    }else if(y>160){
      BTSerial.write('B');
    }else if(y<140){
      BTSerial.write('F');
    }
#endif
 blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
  }
}

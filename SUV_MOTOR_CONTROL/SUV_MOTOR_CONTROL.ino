
/*--------------------------------------------------------------
  Program:      SUV MOTOR CONTROL
  
  Description:  Read wii nunchuck buttons and joystick and control 
                2 sabertooth 2x60 motor controllers
  
  Hardware:     Arduino Pro mini with wii Nunchuck
                
  Date:         September, 2015
 
  Author:       Chris Low

 */
 
//included libraries
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double aggKp=.1, aggKi=.0002, aggKd=.005;
double consKp=.085, consKi=.0025, consKd=.02;
double gap;

//Set upsoftware seirial tx only on pin 11
SoftwareSerial SWSerial(NOT_A_PIN, 11);
Sabertooth ST(128, SWSerial);
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

//need to change data types
//pin assignments
const int button1 = 4;
const int button2 = 5;
const int joy1 = A6;
const int joy2 = A7;
const int steeringpot = A0;
const int rcin1 = 8;
const int rcin2 = 12;
const int rcon = 9;
const int open1 = 3;
const int open2 = 6;
const int open3 = 7;

//variable
const int samplenumber = 4;
const int hornvolume =128;
const int leftmax = 340;
const int rightmax = 785;
int joyx;
int joyy;
int horn;
int hornout;
int steering;
int samples;
int joyxtotal;
int joyytotal;
int steeringtotal;
int drivemode;
int joyturn;
int joypower;
int sampledone;
int errorx;
int errory;



void setup() {
// set pinmodes so they are not floating
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(rcin1, INPUT_PULLUP);
pinMode(rcin2, INPUT_PULLUP);
pinMode(rcon, INPUT_PULLUP);
pinMode(open1, INPUT_PULLUP);
pinMode(open2, INPUT_PULLUP);
pinMode(open3, INPUT_PULLUP);
pinMode(horn, OUTPUT);

SWSerial.begin(9600);
//ST.autobaud();
ST.setTimeout(950);
myPID.SetOutputLimits(-127, 127);
myPID.SetSampleTime(50);
//for debug only
//Serial.begin(9600);
joyxtotal += analogRead(joy1);
joyytotal += analogRead(joy2);
joyxtotal += analogRead(joy1);
joyytotal += analogRead(joy2);
joyxtotal += analogRead(joy1);
joyytotal += analogRead(joy2);
joyxtotal += analogRead(joy1);
joyytotal += analogRead(joy2);
joyxtotal += analogRead(joy1);
joyytotal += analogRead(joy2);
joyxtotal /= 5;
joyytotal /= 5;
errorx = joyxtotal-512;
errory = joyytotal-512;
joyxtotal = 0;
joyytotal = 0;
samples = 0;
steeringtotal = 0;
digitalWrite(horn, LOW);
}

void loop() {

if (samples < samplenumber) {
  joyxtotal += analogRead(joy1);
  joyxtotal -= errorx;
  joyytotal += analogRead(joy2);
  joyytotal -= errory; 
  steeringtotal += analogRead(steeringpot);
  samples ++; 
}
if (samples >= samplenumber)  {
  joyx = (joyxtotal/samples);
  joyy = (joyytotal/samples);
  steering = (steeringtotal/samples);
  samples = 0;
  joyxtotal = 0;
  joyytotal = 0;
  steeringtotal = 0;
  joyturn = map(joyx, 0, 1023, -50, 50);
  joypower = map(joyy, 0, 1023, -127, 127);
  if (joyturn <= 2 && joyturn >= -2 && joypower <= 3 && joypower >= -3) {
    joyturn = 0;
    joypower = 0;
  }
  Setpoint = map(joyx, 0, 1023, 100, 923);
  Input = map(steering, leftmax, rightmax, 0, 1023);
  gap = abs(Setpoint-Input); //distance away from setpoint
  if (gap < 100)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }  
  myPID.Compute();
  
}

drivemode = digitalRead(button2);

if (drivemode == HIGH)  {
   myPID.SetMode(MANUAL);
   ST.drive(joypower);
   ST.turn(joyturn);
   sampledone = 0;
   //Serial.write("Power ");
   //Serial.println(joypower);
   //Serial.write("Turn ");
   //Serial.println(joyturn);
}
// This section will be used for PID control mode when button is held down
if (drivemode == LOW) {
   myPID.SetMode(AUTOMATIC);
   ST.drive(joypower);
   ST.turn(Output);
   sampledone = 0;
  
   Serial.write("steering");
   Serial.println(steering);
   Serial.write("Setpoint");
   Serial.println(Setpoint);
   Serial.write("Input");
   Serial.println(Input);
   Serial.println(Output);
  
  }  
/*
horn = digitalRead(button1);
if (horn = LOW) {
  analogWrite(hornout, hornvolume);
}
if (horn = HIGH) {
  analogWrite(hornout, 0); 
}
*/
}

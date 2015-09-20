
/*--------------------------------------------------------------
  Program:      LEUV MOTOR CONTROL
  
  Description:  Read wii nunchuck buttons and joystick and control 
                2 sabertooth 2x60 motor controllers
  
  Hardware:     Arduino Pro mini with wii Nunchuck
                
  Date:         September, 2015
 
  Author:       Chris Low

 */
 
//included libraries
#include <SoftwareSerial.h>
#include <Sabertooth.h>

//Set upsoftware seirial tx only on pin 11
SoftwareSerial SWSerial(NOT_A_PIN, 11);
Sabertooth ST(128, SWSerial);

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
const int samplenumber = 5;
const int hornvolume =128;
int joyx;
int joyy;
int horn;
int hornout;
int steering;
int samples;
int joyxtotal;
int joyytotal;
int steeringtotal;
int sampleready;
int drivemode;
int joyturn;
int joypower;
int sampledone;


void setup() {
// set pinmodes so they are not floating

pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(rcin1, INPUT_PULLUP);
pinMode(rcin2, INPUT_PULLUP);
pinMode(open1, INPUT_PULLUP);
pinMode(open2, INPUT_PULLUP);
pinMode(open3, INPUT_PULLUP);
pinMode(horn, OUTPUT);

//variables to 0
samples = 0;
joyxtotal = 0;
joyytotal = 0;
steeringtotal = 0;
digitalWrite(horn, LOW);
SWSerial.begin(9600);
ST.autobaud();
//for debug only
//Serial.begin(9600);
}

void loop() {

if (samples < samplenumber) {
  joyxtotal += analogRead(joy1);
  joyytotal += analogRead(joy2); 
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
  sampledone = 1;
}

drivemode = digitalRead(button2);
if (drivemode == HIGH && sampledone == 1)  {
  joyturn = map(joyx, 0, 1024, -50, 50);
  joypower = map(joyy, 0, 1024, -127, 127);
  if (joyturn <= 10 && joyturn >= -10) {
    joyturn = 0;
  }
  if (joypower <= 10 && joypower >= -10) {
    joypower = 0;
  }
  ST.drive(joypower);
  ST.turn(joyturn);
  //Serial.write("Power ");
  //Serial.println(joypower);
  //Serial.write("Turn ");
  //Serial.println(joyturn);
  sampledone = 0;
}
// This section will be used for PID control mode when button is held down
if ((drivemode == LOW) && sampledone == 1) {
  joyturn = map(joyx, 0, 1024, -127, 127);
  joypower = map(joyy, 0, 1024, -127, 127);
  if (joyturn <= 10 && joyturn >= -10) {
    joyturn = 0;
  }
  if (joypower <= 10 && joypower >= -10) {
    joypower = 0;
  }
  ST.drive(joypower);
  ST.turn(joyturn);

}
horn = digitalRead(button1);
if (horn = LOW) {
  analogWrite(hornout, hornvolume);
}
if (horn = HIGH) {
  analogWrite(hornout, 0); 
}
}

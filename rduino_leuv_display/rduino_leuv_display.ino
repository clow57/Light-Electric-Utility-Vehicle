
/*--------------------------------------------------------------
  Program:      LEUV DISPLAY

  Description:  Display information and change parameters for LCD
                For Solar Electric Utility Vehicle
  
  Hardware:     Arduino Pro mini with 4x20 LCD Display
                
  Date:         11 September, 2015
 
  Author:       Chris Low

  References: 

*/

//included libraries
#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 5, 4, 3, 2);




//Assign pins
//need to change variable types
const int button1 = A0;
const int button2 = A1;
const int button3 = A2;
const int current1 = A5;
const int current2 = A4;
const int current3 = A3;
const int light = 10;
const int fan = 9;
const int temp = 12;
const int keysense = A6;
const int open1 = 6;
const int open2 = 11;

const int debouncedelay = 200;
int page;
int view;
int menu;
int buttonstate1;
int buttonstate2;
int buttonstate3;
int lastdebounce;

//teperature sensor on pin 8
#define ONE_WIRE_BUS_PIN 12

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS_PIN);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Assign the addresses of your 1-Wire temp sensors.
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
//DeviceAddress Probe06 = { 0x28, 0x58, 0xA4, 0xCC, 0x05, 0x00, 0x00, 0xA3 }; 
//DeviceAddress Probe03 = { 0x28, 0xC4, 0xA0, 0xCD, 0x05, 0x00, 0x00, 0xFF };
//DeviceAddress Probe01 = { 0x28, 0x24, 0xDB, 0xCC, 0x05, 0x00, 0x00, 0x44 };
//DeviceAddress Probe05 = { 0x28, 0xDC, 0x83, 0xCC, 0x05, 0x00, 0x00, 0x3C };
//DeviceAddress Probe04 = { 0x28, 0xB5, 0xBC, 0xCD, 0x05, 0x00, 0x00, 0x0D };
//DeviceAddress Probe02 = { 0x28, 0xD7, 0x5E, 0xCD, 0x05, 0x00, 0x00, 0xF9 };

void setup() {
 // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  page = 1;
  view = 0;
  menu = 0;
  lastdebounce = 0;
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(open1, INPUT_PULLUP);
  pinMode(open2, INPUT_PULLUP);
  pinMode(fan, OUTPUT);
  pinMode(light, OUTPUT);
  lcd.setCursor(3,0);
  lcd.write("SOLAR UTILITY");
  lcd.setCursor(6,1);
  lcd.write("VEHICLE");
  delay(2000);
  lcd.clear();
 // Debug only
 // Serial.begin(9300);
}

void loop() {
/* debug only
Serial.write("page");
Serial.println(page);
Serial.write("menu");
Serial.println(menu);
Serial.write("view");
Serial.println(view);
*/
if (page ==  1) {
   if (view == 0) {
      lcd.setCursor(0,0);
      lcd.write("Batt");
      lcd.setCursor(0,1);
      lcd.write("Amp In");
      lcd.setCursor(0,2);
      lcd.write("Max Temp");
      lcd.setCursor(13,0);
      lcd.write("SOC");
      lcd.setCursor(12,1);
      lcd.write("out");
      lcd.setCursor(7,3);
      lcd.write("Light");
      lcd.setCursor(16,3);
      lcd.write("Next");
      lcd.setCursor(9,0);
      lcd.write("V");
      lcd.setCursor(19,0);
      lcd.write("%");
      lcd.setCursor(13,2);
      lcd.write("C");
      view = 1;
      }
   if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          lastdebounce=millis();
        }
        if (buttonstate2 ==LOW) {
           lastdebounce=millis();
        }
        if (buttonstate3 ==LOW) {
          page=2;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
        }     
    
     }
  }
}
if (page ==  2) {
   if (view == 0) {
     lcd.setCursor(0,0);
     lcd.write("Panel");
     lcd.setCursor(0,1);
     lcd.write("Batt");
     lcd.setCursor(0,3);
     lcd.write("Back");
     lcd.setCursor(7,3);
     lcd.write("Light");
     lcd.setCursor(16,3);
     lcd.write("Next");
     lcd.setCursor(10,0);
     lcd.write("V");
     lcd.setCursor(17,0);
     lcd.print("A");
     lcd.setCursor(10,1);
     lcd.write("V");
     lcd.setCursor(17,1);
     lcd.write("A");
     view = 1;
  }
  if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        buttonstate1 = digitalRead(button1);
        buttonstate2 = digitalRead(button2);
        buttonstate3 = digitalRead(button3);
        if (buttonstate1 ==LOW) {
          page=1;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
        }
        if (buttonstate2 ==LOW) {
          lastdebounce=millis();
        }
        if (buttonstate3 ==LOW) {
          page=3;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
        } 
      }    
   }
}
if (page ==  3) {
      if (view == 0) {
        lcd.setCursor(0,0);
        lcd.write("MFR");
        lcd.setCursor(0,1);
        lcd.write("MRR");
        lcd.setCursor(0,2);
        lcd.write("BF");
        lcd.setCursor(0,3);
        lcd.write("Back");
        lcd.setCursor(7,3);
        lcd.write("Light");
        lcd.setCursor(16,3);
        lcd.write("Next");
        lcd.setCursor(8,0);
        lcd.write("C");
        lcd.setCursor(8,1);
        lcd.print("C");
        lcd.setCursor(8,2);
        lcd.write("C");
        lcd.setCursor(11,0);
        lcd.write("MFL");
        lcd.setCursor(11,1);
        lcd.write("MRL");
        lcd.setCursor(11,2);
        lcd.write("BR");
        lcd.setCursor(0,3);
        lcd.setCursor(19,0);
        lcd.write("C");
        lcd.setCursor(19,1);
        lcd.print("C");
        lcd.setCursor(19,2);
        lcd.write("C");
        view = 1;
      }
      if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          page=2;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          page=4;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          } 
      }  
  }
}
if (page ==  4) {
      if (view == 0) {
        lcd.setCursor(6,0);
        lcd.write("Current");
        lcd.setCursor(0,1);
        lcd.write("In");
        lcd.setCursor(0,2);
        lcd.write("MR");
        lcd.setCursor(0,3);
        lcd.write("Back");
        lcd.setCursor(7,3);
        lcd.write("Light");
        lcd.setCursor(16,3);
        lcd.write("next");
        lcd.setCursor(7,1);
        lcd.write("A");
        lcd.setCursor(7,2);
        lcd.print("A");
        lcd.setCursor(11,1);
        lcd.write("MF");
        lcd.setCursor(11,2);
        lcd.write("Aux");
        view = 1;
      }
      if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          page=3;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          page=5;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          } 
     }   
   }
}
if (page ==  5) {
      if (view == 0) {
        if (menu ==0) {
          lcd.setCursor(3,1);
          lcd.write("Winch Control");
          lcd.setCursor(0,3);
          lcd.write("Back");
          lcd.setCursor(6,3);
          lcd.write("Control");
          lcd.setCursor(16,3);
          lcd.write("Next");
          view = 1;
        }
        if (menu ==1) {
          lcd.setCursor(3,1);
          lcd.write("Winch Control");
          lcd.setCursor(0,3);
          lcd.write("In");
          lcd.setCursor(8,3);
          lcd.write("Exit");
          lcd.setCursor(17,3);
          lcd.write("Out");
          view = 1;
          
        }      
      }
      if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          page = 4;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu = 1;
          view= 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          page =6;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          } 
     }
      if(menu==1&&(millis()>lastdebounce+debouncedelay)) {
        if (buttonstate1 ==LOW) {
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu = 0;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          lastdebounce=millis();
          } 
     }        
   }
}
if (page ==  6) {
      if (view == 0) {
        if (menu== 0) {
          lcd.setCursor(2,0);
          lcd.write("Light Brightness");
          lcd.setCursor(0,3);
          lcd.write("Back");
          lcd.setCursor(8,3);
          lcd.write("Edit");
          lcd.setCursor(16,3);
          lcd.write("Next");
          view = 1;   
        }
        if (menu== 1) {
          lcd.setCursor(2,0);
          lcd.write("Light Brightness");
          lcd.setCursor(0,3);
          lcd.write("Down");
          lcd.setCursor(8,3);
          lcd.write("Save");
          lcd.setCursor(18,3);
          lcd.write("Up");
          view = 1;   
        }   
      }
      if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          page=5;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu=1;
          lcd.clear();
          view = 0;
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          page =7;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          } 
     }  
      if(menu==1&&(millis()>lastdebounce+debouncedelay)) {
        if (buttonstate1 ==LOW) {
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu=0;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          lastdebounce=millis();
          } 
     }  
   }
}
if (page ==  7) {
      if (view == 0) {
        if (menu == 0) {
          lcd.setCursor(4,0);
          lcd.write("Fan On Temp");
          lcd.setCursor(11,1);
          lcd.write("C");
          lcd.setCursor(0,3);
          lcd.write("Back");
          lcd.setCursor(8,3);
          lcd.write("Edit");
          lcd.setCursor(16,3);
          lcd.write("Next");
          view = 1;      
        }
        if (menu == 1) {
          lcd.setCursor(4,0);
          lcd.write("Fan on Temp");
          lcd.setCursor(11,1);
          lcd.write("C");
          lcd.setCursor(0,3);
          lcd.write("Down");
          lcd.setCursor(8,3);
          lcd.write("Save");
          lcd.setCursor(18,3);
          lcd.write("Up");
          view = 1;      
        }
      }  
      if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          page=6;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu=1;
          lcd.clear();
          view=0;
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          page=8;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          } 
     }
      if(menu==1&&(millis()>lastdebounce+debouncedelay)) {
        if (buttonstate1 ==LOW) {
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu=0;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          lastdebounce=millis();
          } 
     }    
   }
}
if (page ==  8) {
      if (view == 0) {
        if (menu ==0){
        lcd.setCursor(1,0);
          lcd.write("Over Temp Warning");
          lcd.setCursor(11,1);
          lcd.write("C");
          lcd.setCursor(0,3);
          lcd.write("Back");
          lcd.setCursor(8,3);
          lcd.write("Edit"); 
          view = 1; 
        }
        if(menu == 1) {
          lcd.setCursor(1,0);
          lcd.write("Over Temp Warning");
          lcd.setCursor(11,1);
          lcd.write("C");
          lcd.setCursor(0,3);
          lcd.write("Down");
          lcd.setCursor(8,3);
          lcd.write("save");
          lcd.setCursor(18,3);
          lcd.write("Up");
          view = 1;    
        }
      }
      if(millis()>lastdebounce+debouncedelay) {
      buttonstate1 = digitalRead(button1);
      buttonstate2 = digitalRead(button2);
      buttonstate3 = digitalRead(button3);
      if(menu==0) {
        if (buttonstate1 ==LOW) {
          page=7;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu=1;
          lcd.clear();
          view = 0;
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          lastdebounce=millis();
          } 
     } 
     if(menu==1&&(millis()>lastdebounce+debouncedelay)) {
        if (buttonstate1 ==LOW) {
          lastdebounce=millis();
          }
        if (buttonstate2 ==LOW) {
          menu=0;
          view = 0;
          lcd.clear();
          lastdebounce=millis();
          }
        if (buttonstate3 ==LOW) {
          lastdebounce=millis();
          } 
     }   
   }
}
}

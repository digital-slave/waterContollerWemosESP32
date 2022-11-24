#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <stdlib.h>
//39 (0x27)

#define wateringPin 16 
#define wateringPin2 17

long int beginingTime = 0;
long int timeRemaining = 0;

//watering system timming
const int minutes = 1;
const int waterFrequencey = 3; ///in 24 hours 24 hour clock




//LCD preset string and type
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
const char* switchStateOn = "Switch Open";
const char* switchStateOff = "Switch Closed";





void setup() {
  Serial.begin(115200);

  //LCD
  //--------------------------------------

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Watering System");
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("Starting Server");
  //-------------------------------------

  //PIN CONFIGURATION
  //-------------------------------------
  pinMode(wateringPin, OUTPUT);
  pinMode(wateringPin2, OUTPUT);


  delay(1000);

  //-------------------------------------


}

void loop() 
{
  Serial.print("beginingTime :");
  Serial.println(beginingTime);
  //begin pumping
  if(beginingTime == 0){
    waterSwitch("ON", minutes);
    beginingTime = millis();
    Serial.print("beginingTime :");
    Serial.println(beginingTime);
  
  }
  delay(1000);
  //set gpio high
  //set lcd display

  if( (millis()-(minutes*60000)) >= (beginingTime + (minutes*60000))   ){
    waterSwitch("OFF", minutes);
    beginingTime = 0;
  }
  delay(1000);
  //stop
  //set gpio low
  // lcd display show off
}



void waterSwitch(const String status, int minutesRemaining){

  String minRemainStr = String(minutesRemaining); //Display function is fuked and can only take a string to lcd.print with
  beginingTime = millis();          //Start point in time 
                                    //setup LCD for new MODE -- watering mode
  lcd.clear();                      // Only  clar LCD on mode change
  display("Rem. Time: ", 1, 0 );    //SET mode and center word
  display(minRemainStr, 1, 11); 
  display("Watering: ", 0, 0);      //display(string, row int, col int)//Set bottom row 1 to watering:
  if(status == "ON"){
    digitalWrite(wateringPin, HIGH);
    display("ON", 0, 11);
  }
  if(status == "OFF"){
    digitalWrite(wateringPin, LOW);
    display("OFF", 0, 11);
  }
    return;
}

void display(String text, int row, int col)
{
  lcd.setCursor(col, row);
  lcd.print(text);

  return;
}



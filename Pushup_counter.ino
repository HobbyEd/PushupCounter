#include <Wire.h> //LiquidCrystal I2C Lib from Frank de Brabander 
#include <LiquidCrystal_I2C.h>

//HC-SR04
#define echoPin  2
#define trigPin  3
#define resetPin 4

float duration; //micro second
float d_cm;
boolean trigUp = false;
boolean trigDown = false;
float counterPushUp=0;

//Create an instance of the display
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  lcd.init();
  //turn on the backlight of the display
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Welcome by the");
  lcd.setCursor(0,1);
  lcd.print("Pushup Counter");
  
  //Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //
  pinMode(resetPin,INPUT_PULLUP);
  
  delay(5000);
  lcd.setCursor(0,1);
  lcd.print("              ");
 }

void loop()
{
  //reset by switch
  if(digitalRead(resetPin)==0){
    trigUp=false;
    trigDown=false;
    counterPushUp=0;
  }
  
  // generate pusle trigger
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  // receive, convert time (us) to cm
  duration = pulseIn(echoPin,HIGH);
  d_cm = duration * 0.034/2.;
  
  //trigger body 
  if (d_cm>15 && d_cm<=30){
    trigUp = true;
  } else if (d_cm < 10){
    trigDown = true;
  } else if(d_cm >30) {
  }
  //counter
  if (trigUp==true && trigDown==true){
    counterPushUp=counterPushUp+0.5;
    trigUp=false;
    trigDown=false;
  }
  
  lcd.setCursor(0,0);
  lcd.print("Pushup Counter");
  lcd.setCursor(0,1); 
  lcd.print(counterPushUp); 
}

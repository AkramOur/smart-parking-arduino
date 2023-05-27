#include <LiquidCrystal.h>
#include <Servo.h>
const int rs = 12, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo inServo;
const int cap1=9,cap2=10,cap3=8,capServ=7;
void setup() {
  Serial.begin(9600);
  pinMode(cap1,INPUT);
  pinMode(cap2,INPUT);
  pinMode(cap3,INPUT);
  pinMode(capServ,INPUT);
  inServo.attach(11);
  lcd.begin(16, 2);
  lcd.print("getting data....");
}



void loop(){
  lcd.clear();
  int nb=nbPlaceeDispo();
  lcd.print(String(nb)+" places libres");
  Serial.println(digitalRead(cap1));
  Serial.println(digitalRead(cap2));
  Serial.println(digitalRead(cap3));
  Serial.println("***********************");
  delay(500);
}

int nbPlaceeDispo(){
  int nb=3;
  if(digitalRead(cap1) == 0) nb--;
  if(digitalRead(cap2) == 0) nb--;
  if(digitalRead(cap3) == 0) nb--;
  return nb;
}

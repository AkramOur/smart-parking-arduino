#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int etat=0 ,etat2=1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  pinMode(9,OUTPUT);
  pinMode(7,INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
//  lcd.print("2 places dispo");
}

void loop() {
  if(digitalRead(8) == 0){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
    
  }
  if(digitalRead(7) == 0){
    digitalWrite(9,HIGH);

  }else{
    digitalWrite(9,LOW);

  }
  if(digitalRead(8) == 0 && digitalRead(7) == 0){
      etat=1;
    }else if(digitalRead(8) == 0 || digitalRead(7) == 0){
      etat=2;
    }else {
      etat=3;
    }
  if(etat != etat2){
    lcd.clear();
    if(digitalRead(8) == 0 && digitalRead(7) == 0){
      lcd.print("0 place dispo");
    }else if(digitalRead(8) == 0 || digitalRead(7) == 0){
      lcd.print("1 place dispo");
    }else {
      lcd.print("2 places dispo");
    }
    
  }
  etat2=etat;
}

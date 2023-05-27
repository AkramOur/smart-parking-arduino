#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FirebaseArduino.h>
#include <Servo.h>
#define capServ D7
#define cap1 D5
#define cap2 D6
#define cap3 D0
//#define cap4 
#define LED1 D1
#define LED2 D2
#define LED3 D3
Servo inServo;
const char* ssid = "IOT_LAB";
const char* password = "20192019";
const char* firebase_host = "smartparking-147f9-default-rtdb.firebaseio.com";
const char* firebase_auth = "PqdKw9zTujkmJK4Y4ctmT3JNVW5vvaJRv15At7Xc";


void setup() {
  pinMode(capServ,INPUT);
  pinMode(cap1,INPUT);
  pinMode(cap2,INPUT);
  pinMode(cap3,INPUT);
  //pinMode(cap4,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  inServo.attach(D4);
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
   Serial.println("HTTP server started");
   Firebase.begin(firebase_host,firebase_auth);
}

void loop() {
  int closed = Firebase.getInt("closed");
  if(!closed){
    int n = Firebase.getInt("dor");
    if(n==1 && digitalRead(capServ) == 0){
      inServo.write(0);
      delay(2000);
      inServo.write(90);
    }
    Firebase.setInt("dor",0);
    putDataFirebase();
  }
}

void putDataFirebase()
{
  
  delay(500);
  if(digitalRead(cap1) == 1){
    digitalWrite(LED1,LOW);
      Firebase.setString("place1","libre");      
  }else{
    digitalWrite(LED1,HIGH);
      Firebase.setString("place1","reserve");
  }
  if(digitalRead(cap2) == 1){
      Firebase.setString("place2","libre");
      digitalWrite(LED2,LOW);
  }else{
      Firebase.setString("place2","reserve");
      digitalWrite(LED2,HIGH);
  }
  if(digitalRead(cap3) == 1){
      Firebase.setString("place3","libre");
      digitalWrite(LED3,LOW);
  }else{
      Firebase.setString("place3","reserve");
      digitalWrite(LED3,HIGH);
  }
}

int nbPlaceeDispo(){
  int nb=3;
  if(digitalRead(cap1) == 0) nb--;
  if(digitalRead(cap2) == 0) nb--;
  if(digitalRead(cap3) == 0) nb--;
  return nb;
}

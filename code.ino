#include<Servo.h>

int mindist = 50; //can be changed in order to change how closer the bot gets to the obstacle before stopping

int trigPin = 9;
int echoPin = 10;
int servopin = 8;
int lmotor = 11;
int rmotor = 12;
int angle = 90;
int turndelay = 2; //Seconds taken to turn, change according to surface (needs a bit of trial and error)
Servo myservo;

long duration;
int dist;

void setup(){
  myservo.attach(servopin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lmotor, OUTPUT);
  pinMode(rmotor, OUTPUT);
  myservo.write(angle);
}

void loop(){
  int dis = distance();
  if(dis>mindist){
    digitalWrite(lmotor,HIGH);
    digitalWrite(rmotor,HIGH);
  }
  else{
    digitalWrite(lmotor,LOW);
    digitalWrite(rmotor,LOW);
    myservo.write(0);
    delay(1000);
    int ldis = distance();
    myservo.write(180);
    delay(2000);
    int rdis = distance();
    myservo.write(90);
    if(ldis>rdis){
      digitalWrite(lmotor,LOW);
      digitalWrite(rmotor,HIGH);
      delay(turndelay*1000);
      digitalWrite(lmotor,LOW);
      digitalWrite(rmotor,LOW);            
    }
    else{
      digitalWrite(lmotor,HIGH);
      digitalWrite(rmotor,LOW);
      delay(turndelay*1000);
      digitalWrite(lmotor,LOW);
      digitalWrite(rmotor,LOW);        
    }
  }
}

int distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist= duration*0.034/2;
  return dist;
}

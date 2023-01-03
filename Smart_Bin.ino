#include <Servo.h> //servo library
#include <LiquidCrystal.h>
Servo servo;
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);
int trigPin = 6;
int echoPin = 5;
int trigPin2 = 4;
int echoPin2 = 13;
int servoPin = 7;
int led= 12;
long duration, dist, average;
long aver[3]; //array for average
long duration2, dist2, average2;
long aver2[3];
void setup() {
 Serial.begin(9600);
 servo.attach(servoPin);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);

 servo.write(0); //close cap on power on
 delay(100);
 servo.detach();

}
void measure() {
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1; //obtain distance
}
void measure2() {

digitalWrite(trigPin2, LOW);
delayMicroseconds(5);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin2, LOW);
pinMode(echoPin2, INPUT);
duration2 = pulseIn(echoPin2, HIGH);
dist2 = (duration2/2) / 29.1;

}
void loop() {
 for (int i=0;i<=2;i++) { //average distance
 measure();
 aver[i]=dist;
 delay(10); //delay between measurements
 }
dist=(aver[0]+aver[1]+aver[2])/3;
for (int j=0;j<=2;j++) { //average distance
 measure2();
 aver2[j]=dist2;
 delay(10); //delay between measurements
 }
dist2=(aver2[0]+aver2[1]+aver2[2])/3;

if ( dist2<30 ) 
{

 servo.attach(servoPin);
 delay(1);
 servo.write(0);
 delay(1000);
 servo.detach();
 digitalWrite(12,LOW);

 lcd.clear();
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("I am Smart but,");
 lcd.setCursor(0,1);
 lcd.print("I am 90% full...");
}

else if ( dist<50 ) {
//Change distance as per your need
servo.attach(servoPin);
 delay(1);

servo.write(150);
 digitalWrite(12,HIGH);
delay(3000);

 lcd.clear();
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Cap Open.");
 lcd.setCursor(0,1);
 lcd.print("Use Me...!!! ;)");
}
else if ( dist>50 )
{
 servo.attach(servoPin);
 delay(1);
 servo.write(0);
 delay(1000);
 servo.detach();
 digitalWrite(12,LOW);

 lcd.clear();
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print(" Group No. :- 3");
 lcd.setCursor(0,1);
 lcd.print("I am Smart Bin:)"); 
}
Serial.print(dist); 
}

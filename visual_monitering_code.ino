//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 80// sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
#define SENSE A5

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  // eye blink 
  pinMode(A3, OUTPUT);
  pinMode(SENSE, INPUT);//existing
  myservo.attach(10);  
  myservo.write(90); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  //edit
  

  
  //eye blink
  if(digitalRead(SENSE))
{
  
 delay(40);// existing
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  turnRight();
  moveStop();
  }
 else
 {
  moveForward();
 }
 distance = readPing();
}
else
{
  delay(40);
  delay (2000);
  if(digitalRead(SENSE))
  {
    
 delay(40);// existing
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  turnRight();
  moveStop();
  }
 else
 {
  moveForward();
 }
 distance = readPing();
  }
  else
  {
    
    moveSttop();
     digitalWrite(A3, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(A3, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
  digitalWrite(A3, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(A3, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);
   moveForward(); 
    }

}


}


int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
  } 

  void moveSttop() {//new
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  digitalWrite(A3, HIGH);  // turn the LED on (HIGH is the voltage level)
   delay(1000);                      // wait for a second
   digitalWrite(A3, LOW);   // turn the LED off by making the voltage LOW
   delay(1000);
  

  
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
    }
  }
}


void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < 90 ; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  


 
void turnRight() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD); 
  motor1.setSpeed(130);
  motor2.setSpeed(130);
  motor3.setSpeed(130);
  motor4.setSpeed(130);
  delay(1500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
 
}  

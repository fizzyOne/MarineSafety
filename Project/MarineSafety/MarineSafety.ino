/**
 * This program is written for a project to automate journey through sea a bit. 
 * This does NOT automate every function. But will make sure a bit of safety.
 * <br/>
 * NOTE: THIS IS PROJECT UNDER DEVELOPMENT. NO ASSURANCE OF COMPLETE SAFETY IS GIVEN WITH THIS.
 * 
 * <br/>
 * *ENGINEPIN = 1;
  *
  *WHEEL: 9;
  *
  *LEFT:
  * trigPin1 = 2;
  * echoPin1 = 3;
  *FRONT:
  * trigPin2 = 5;
  * echoPin2 = 6;
  *RIGHT:
  * trigPin3 = 7;
  * echoPin3 = 8;
  *
  *DISTANCES:
  * distAlert = 50;
  * distTurn = 30;
  * distStop = 10;
 * 
 * @author  aHmEd HaFiZ
 * @version 1.2
 * @since 2018-05-21
 */

/**
 * IMPORTS
 */
#include <Servo.h>
// engine pin
const int enginePin = 1;

// defines pins numbers
// U.S.S 1 : Left
const int trigPin1 = 2;
const int echoPin1 = 3;
// U.S.S 2 : Front
const int trigPin2 = 5;
const int echoPin2 = 6;
// U.S.S 3 : Right
const int trigPin3 = 7;
const int echoPin3 = 8;

// alert stuff
int piezoPin = 10;

// wheel
Servo wheel;

// distances
const int distAlert = 50;
const int distTurn = 30;
const int distStop = 15;

//DISTANCE AND DURATION
int distance, duration; //used to be int.. test

int initPos = 90;

/**
 * first run
 */
void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin3 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin3 as an Input
  
  pinMode(trigPin2, OUTPUT); // Sets the trigPin3 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin3 as an Input
  
  pinMode(trigPin3, OUTPUT); // Sets the trigPin3 as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin3 as an Input

  wheel.attach(9);
//  wheel.writeMicroseconds(1500);
  wheel.write(initPos);
  
//  engine.attach(1);
  
  Serial.begin(9600); // Starts the serial communication

}

/**
 * Get EchoPin based on USS number
 * 
 * @para ussn Number given to sensor
 * 
 * U.S.S 1 : Left
 * trigPin1 = 2;
 * int echoPin1 = 3;
 * 
 * U.S.S 2 : Front
 * trigPin2 = 5;
 * echoPin2 = 6;
 * 
 * U.S.S 3 : Right
 * trigPin3 = 7;
 * echoPin3 = 8;
 */
int getEchoPin(int ussn) {
  int pin;
  switch(ussn) {
    case 1:
      pin = echoPin1;
      break;
    case 2:
      pin = echoPin2;
      break;
    case 3:
      pin = echoPin3;
      break;
    default: 
      pin = echoPin2;
  }
  return pin;
}

/**
 * Get TriggerPin based on USS number
 * 
 * @para ussn Number given to sensor
 * 
 * U.S.S 1 : Left
 * trigPin1 = 2;
 * int echoPin1 = 3;
 * 
 * U.S.S 2 : Front
 * trigPin2 = 5;
 * echoPin2 = 6;
 * 
 * U.S.S 3 : Right
 * trigPin3 = 7;
 * echoPin3 = 8;
 * 
 * @return Trigger Pin number based on USSN
 * 
 */
int getTrigPin(int ussn) {
  int pin;
  switch(ussn) {
    case 1:
      pin = trigPin1;
      break;
    case 2:
      pin = trigPin2;
      break;
    case 3:
      pin = trigPin3;
      break;
    default: 
      pin = trigPin2;
  }
  return pin;
}

/**
 * @param ussn : UltraSonic Sensor Number
 * 1. Left
 * 2. Front
 * 3. Right
 * @return  distance measured and calculated from ultrasonic sensor
 */

 
int getDist(int ussn){
//  int trip = getTrigPin(ussn);
//  int echop = getEchoPin(ussn);
// testing

  int trip = trigPin2;
  int echop = echoPin2;
  
  digitalWrite(trip, HIGH);
  delayMicroseconds(10);
//  delay(1000);
  digitalWrite(trip, LOW);

  duration = pulseIn(echop, HIGH);
//  distance = (duration/2)/29.1;
  distance =(duration*0.034)/2;

  return distance;
}


/**
 * take actions based on distance
 */

 
void checkDist() {
  
  int dist = (getDist(2)); // 2 because we checking only front sensor
  
  Serial.println("------------------------------");
  Serial.println(dist);

  
  if ((dist < distAlert) && (dist > distTurn)) 
  {
    Serial.println("Alert!");
    Alert(); 
//    resetTurn();
  }
  else if ((dist < distTurn) && (dist > distStop))
  {   
    Serial.println("Turning");
    int lft = getDist(1);   //left
    int rght = getDist(3);  //right
    
//    turn(lft, rght);
      turn(20,60);
  }
  else if  (dist < distStop)
  {
    Serial.println("Engine Off");
    stopEng();
//    resetTurn();
    
  }
  else 
  {
   resetTurn();
     
  }
  delay(1000);
}

/**
 * main loop
 */
void loop() {

  checkDist();

}

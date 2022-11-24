#include <afstandssensor.h> //Ultrasonic sensor library
#include <AceRoutine.h> //Multitasking library

using namespace ace_routine;

AfstandsSensor afstandssensor(8, 9); //Setup of the ultrasonic sensor pin. The first is the trigger and the second is the echo
AfstandsSensor afstandssensor2(2, 3);

//Setup of the stepper motor pin
const int m21 = 4;
const int m22 = 5;
const int m23 = 6;
const int m24 = 7;
const int m11 = A5;
const int m12 = A4;
const int m13 = A3;
const int m14 = A2;

//Milliseconds of delay between motor's coils activation
const int motordelay = 4;

int distance; //Front ultrasonic sensor's output
int wall = 7; //Millimeters of distance between the utrasonic sensor and the obstacle that trigger the device to change direction
int distance2; //Left ultrasonic sensor's output

bool st0p = true; //Variable for the activation of the front ultrasonic sensor
bool sens2 = false; //Variable for the activation of the left ultrasonic sensor


COROUTINE(sensor1) {
  COROUTINE_LOOP() {
    COROUTINE_AWAIT(st0p); //Yields until condition become true
    COROUTINE_DELAY(1000);
    distance = afstandssensor.afstandCM(); //Distance from obstacle in centimeters
    Serial.println(distance);
    COROUTINE_YIELD(); //Yields execution back to the caller
  }
}

COROUTINE(sensor2) {
  COROUTINE_LOOP() {
    COROUTINE_AWAIT(sens2);
    COROUTINE_DELAY(1000);
    distance2 = afstandssensor2.afstandCM();
    Serial.println(distance2);
    COROUTINE_YIELD();
  }
}

COROUTINE(forward) {
  COROUTINE_LOOP() {
    COROUTINE_AWAIT(st0p);
//Code to turn the wheels and make the device go forward
//----------------------------------
    digitalWrite(m11, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m12, LOW);
    digitalWrite(m22, LOW);
    digitalWrite(m13, LOW);
    digitalWrite(m23, LOW);
    digitalWrite(m14, HIGH);
    digitalWrite(m24, HIGH);
    delay(motordelay);
    digitalWrite(m11, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m12, LOW);
    digitalWrite(m22, LOW);
    digitalWrite(m13, HIGH);
    digitalWrite(m23, HIGH);
    digitalWrite(m14, LOW);
    digitalWrite(m24, LOW);
    delay(motordelay);
    COROUTINE_YIELD();
    digitalWrite(m11, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m12, HIGH);
    digitalWrite(m22, HIGH);
    digitalWrite(m13, LOW);
    digitalWrite(m23, LOW);
    digitalWrite(m14, LOW);
    digitalWrite(m24, LOW);
    delay(motordelay);
    digitalWrite(m11, HIGH);
    digitalWrite(m21, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m22, LOW);
    digitalWrite(m13, LOW);
    digitalWrite(m23, LOW);
    digitalWrite(m14, LOW);
    digitalWrite(m24, LOW);
    delay(motordelay);
//----------------------------------
  }
}

COROUTINE(left) {
  COROUTINE_LOOP() {
    COROUTINE_DELAY(2000);
    COROUTINE_AWAIT(distance2 > wall && sens2==true);
    COROUTINE_DELAY(9000); //This is a necessary delay to make the device turn without hitting the obstacle
    st0p = false;
    for (int i = 0; i < 677; i++) {
//Code to turn the wheels and make the device go left
//----------------------------------
      digitalWrite(m11, HIGH);
      digitalWrite(m21, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m22, LOW);
      digitalWrite(m13, LOW);
      digitalWrite(m23, LOW);
      digitalWrite(m14, LOW);
      digitalWrite(m24, HIGH);
      delay(motordelay);
      digitalWrite(m11, LOW);
      digitalWrite(m21, LOW);
      digitalWrite(m12, HIGH);
      digitalWrite(m22, LOW);
      digitalWrite(m13, LOW);
      digitalWrite(m23, HIGH);
      digitalWrite(m14, LOW);
      digitalWrite(m24, LOW);
      delay(motordelay);
      digitalWrite(m11, LOW);
      digitalWrite(m21, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m22, HIGH);
      digitalWrite(m13, HIGH);
      digitalWrite(m23, LOW);
      digitalWrite(m14, LOW);
      digitalWrite(m24, LOW);
      delay(motordelay);
      digitalWrite(m11, LOW);
      digitalWrite(m21, HIGH);
      digitalWrite(m12, LOW);
      digitalWrite(m22, LOW);
      digitalWrite(m13, LOW);
      digitalWrite(m23, LOW);
      digitalWrite(m14, HIGH);
      digitalWrite(m24, LOW);
      delay(motordelay);
//----------------------------------
    }
    sens2 = false;
    st0p = true;
  }
}

COROUTINE(right) {
  COROUTINE_LOOP() {
    COROUTINE_DELAY(2000);
    COROUTINE_AWAIT(distance < wall);
    COROUTINE_DELAY(1000);
    st0p = false;
    for (int i = 0; i < 677; i++) {
//Code to turn the wheels and make the device go left
//----------------------------------
      digitalWrite(m21, HIGH);
      digitalWrite(m11, LOW);
      digitalWrite(m22, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m23, LOW);
      digitalWrite(m13, LOW);
      digitalWrite(m24, LOW);
      digitalWrite(m14, HIGH);
      delay(motordelay);
      digitalWrite(m21, LOW);
      digitalWrite(m11, LOW);
      digitalWrite(m22, HIGH);
      digitalWrite(m12, LOW);
      digitalWrite(m23, LOW);
      digitalWrite(m13, HIGH);
      digitalWrite(m24, LOW);
      digitalWrite(m14, LOW);
      delay(motordelay);
      digitalWrite(m21, LOW);
      digitalWrite(m11, LOW);
      digitalWrite(m22, LOW);
      digitalWrite(m12, HIGH);
      digitalWrite(m23, HIGH);
      digitalWrite(m13, LOW);
      digitalWrite(m24, LOW);
      digitalWrite(m14, LOW);
      delay(motordelay);
      digitalWrite(m21, LOW);
      digitalWrite(m11, HIGH);
      digitalWrite(m22, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m23, LOW);
      digitalWrite(m13, LOW);
      digitalWrite(m24, HIGH);
      digitalWrite(m14, LOW);
      delay(motordelay);
//----------------------------------
    }
    st0p = true;
    sens2 = true;
  }
}

void setup() {
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m13, OUTPUT);
  pinMode(m14, OUTPUT);
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m13, LOW);
  digitalWrite(m14, LOW);

  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m23, OUTPUT);
  pinMode(m24, OUTPUT);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m23, LOW);
  digitalWrite(m24, LOW);

  Serial.begin(9600);

  CoroutineScheduler::setup();
}

void loop() {
  CoroutineScheduler::loop();
}

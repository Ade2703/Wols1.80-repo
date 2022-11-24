#include <AceRoutine.h>
#include <NewPing.h>
using namespace ace_routine;


#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 250

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int m11 = 4;
const int m12 = 5;
const int m13 = 6;
const int m14 = 7;
const int m21 = 8;
const int m22 = 9;
const int m23 = 10;
const int m24 = 11;

const int motordelay = 4;

int distance, wall = 9;

bool st0p = true;

COROUTINE(sensor1) {
  COROUTINE_LOOP() {
    COROUTINE_AWAIT(st0p);
    COROUTINE_DELAY(1000);
    unsigned int uS = sonar.ping();
    distance = sonar.convert_cm(uS);
    if (distance == 0) {
      distance = 2000; //out of range
    }
    Serial.println(distance);
    COROUTINE_YIELD();
  }
}

COROUTINE(forward) {
  COROUTINE_LOOP() {
    COROUTINE_AWAIT(st0p);
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
  }
}

COROUTINE(left) {
  COROUTINE_LOOP() {
    COROUTINE_DELAY(2000);
    COROUTINE_AWAIT(distance < wall);
    COROUTINE_DELAY(1000);
    Serial.println("ciao");
    st0p = false;
    for (int i = 0; i < 680; i++) {
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
    }
    st0p=true;
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

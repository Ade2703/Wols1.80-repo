
const int m11 = 0;
const int m12 = 1;
const int m13 = 2;
const int m14 = 3;
const int m21 = 4;
const int m22 = 5;
const int m23 = 6;
const int m24 = 7;

const int motordelay = 4;

void forward() {
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
}

void loop() {
  forward();
}

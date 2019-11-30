#include <Servo.h>

const int echoPinSensor1 = 8;
const int trigPinSensor1 = 9;
const int echoPinSensor2 = 6;
const int trigPinSensor2 = 7;
const int echoPinSensor3 = 4;
const int trigPinSensor3 = 5;

Servo baseServo;
int basePosition = 0;

void setup() {
  baseServo.attach(3);
  setupInit(echoPinSensor1, trigPinSensor1);
  setupInit(echoPinSensor2, trigPinSensor2);
  setupInit(echoPinSensor3, trigPinSensor3);
  Serial.begin(115200);
}

void setupInit(int echoPin, int trigPin) {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  changeBasePosition();
  baseServo.write(basePosition);
  delay(500);
}

void changeBasePosition() {
  float pulseSensor1 = getPulse(echoPinSensor1, trigPinSensor1);
  float pulseSensor2 = getPulse(echoPinSensor2, trigPinSensor2);
  float pulseSensor3 = getPulse(echoPinSensor3, trigPinSensor3);
  float minimum = min(pulseSensor1, min(pulseSensor2, pulseSensor3));
  if (minimum == pulseSensor1) {
    basePosition = 135;
  }
  else if (minimum == pulseSensor2) {
    basePosition = 90;
  }
  else {
    basePosition = 45;
  }
}

float getPulse(int echoPin, int trigPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration;
}

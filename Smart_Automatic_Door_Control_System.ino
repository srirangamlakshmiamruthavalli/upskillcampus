#include <Servo.h>

Servo doorMotor;

int trigPin = 9;
int echoPin = 10;
int buzzer = 8;

long duration;
int distance;

unsigned long lastDetectedTime = 0;
int threshold = 50;
int delayTime = 3000;

bool doorOpen = false;  // ⭐ state tracking

void setup() {
  doorMotor.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  doorMotor.write(0); // closed
}

void loop() {
  // Ultrasonic trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Person detected
  if (distance > 0 && distance < threshold) {
    lastDetectedTime = millis();

    if (!doorOpen) {  // open only once
      doorMotor.write(0);
      digitalWrite(buzzer, HIGH);
      doorOpen = true;
    }
  } 
  else {
    digitalWrite(buzzer, LOW);

    // Close after delay
    if (doorOpen && (millis() - lastDetectedTime > delayTime)) {
      doorMotor.write(90);
      doorOpen = false;
    }
  }

  delay(100);
}
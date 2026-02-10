#include <Servo.h>
Servo myServo;

// Sensor & control pins
const int irSensorPin = 8;       // Pushbutton simulates IR/flame sensor

// Gearmotor control (L293D pins)
const int motorLeftIn1 = 3;      // L293D IN1
const int motorLeftIn2 = 4;      // L293D IN2
const int motorRightIn1 = 5;     // L293D IN3
const int motorRightIn2 = 9;     // L293D IN4

// Output devices
const int ledPin = 7;            // LED pin
const int buzzerPin = 6;         // Buzzer pin
const int servoPin = 10;         // Servo signal pin

void setup() {
  // Sensor input
  pinMode(irSensorPin, INPUT);

  // Motor pins
  pinMode(motorLeftIn1, OUTPUT);
  pinMode(motorLeftIn2, OUTPUT);
  pinMode(motorRightIn1, OUTPUT);
  pinMode(motorRightIn2, OUTPUT);

  // Output devices
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Attach the servo
  myServo.attach(servoPin);
  myServo.write(0);  // Start at angle 0
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);

  if (sensorValue == LOW) {
    // Flame detected → turn robot and activate alert
    digitalWrite(motorLeftIn1, LOW);
    digitalWrite(motorLeftIn2, HIGH);   // Left motor backward

    digitalWrite(motorRightIn1, HIGH);
    digitalWrite(motorRightIn2, LOW);   // Right motor forward

    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    myServo.write(90);  // Aim sprayer or rotate
  } else {
    // No flame → move forward, turn off alerts
    digitalWrite(motorLeftIn1, HIGH);
    digitalWrite(motorLeftIn2, LOW);

    digitalWrite(motorRightIn1, HIGH);
    digitalWrite(motorRightIn2, LOW);

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    myServo.write(0);  // Reset servo position
  }

  delay(50);  // Debounce delay
}

#include <Servo.h>

Servo leftServo;
Servo rightServo;

// Pins
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 3;

// Settings
const int safeDistance = 20;
const unsigned long stuckTime = 3000; // 3 seconds

// Timing variables
unsigned long obstacleStartTime = 0;
bool obstacleTimerRunning = false;

void setup() {
  Serial.begin(9600);

  leftServo.attach(5);
  rightServo.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  stopRobot();
  startupTune();
}

void loop() {
  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // OBSTACLE DETECTED
  if (distance <= safeDistance) {

    stopRobot();

    // Start timer if first time seeing obstacle
    if (!obstacleTimerRunning) {
      obstacleTimerRunning = true;
      obstacleStartTime = millis();
    }

    // If obstacle stays for 3 seconds → turn right
    if (millis() - obstacleStartTime >= stuckTime) {
      alertTune();
      turnRight();
      delay(3000); // turning duration

      obstacleTimerRunning = false; // reset after turning
    }
  }

  // NO OBSTACLE → MOVE FORWARD
  else {
    obstacleTimerRunning = false;
    moveForwardSlow();
  }

  delay(100);
}

// ---------------- DISTANCE ----------------
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);

  float distance = duration * 0.0343 / 2;
  return distance;
}

// ---------------- MOVEMENT ----------------
void moveForwardSlow() {
  leftServo.write(125);
  rightServo.write(55);
}

void stopRobot() {
  leftServo.write(90);
  rightServo.write(90);
}

void turnRight() {
  // Right turn (adjust if direction is opposite)
  leftServo.write(110);
  rightServo.write(100);
}

// ---------------- SOUND ----------------
void startupTune() {
  tone(buzzerPin, 1000); delay(150);
  tone(buzzerPin, 1500); delay(150);
  tone(buzzerPin, 2000); delay(200);
  noTone(buzzerPin);
}

void alertTune() {
  tone(buzzerPin, 2000); delay(120);
  tone(buzzerPin, 1200); delay(120);
  tone(buzzerPin, 2000); delay(120);
  noTone(buzzerPin);
}
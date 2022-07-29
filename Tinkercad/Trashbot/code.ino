// C++ code
//
#include <Servo.h>

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_7;

void setup()
{
  servo_7.attach(7, 500, 2500);
}

void loop()
{
  if (0.006783 * readUltrasonicDistance(9, 8) < 40) {
    servo_7.write(90);
  } else {
    servo_7.write(180);
  }
  delay(10); // Delay a little bit to improve simulation performance
}

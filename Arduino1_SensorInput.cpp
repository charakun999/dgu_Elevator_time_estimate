// First arduino work as a sensory input pod, gets PIR infos and Ultrasonic distance informations.

#include <Wire.h>

const int PIR1 = 7;
const int PIR2 = 8;
const int trig1 = 9;
const int echo1 = 10;
const int trig2 = 11;
const int echo2 = 12;
const int trig3 = 13;
const int echo3 = A0;

void setup() {
  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  
  Wire.begin(); // Join I2C bus as a master
  Serial.begin(9600);
}

void loop() {
  int human1 = digitalRead(PIR1);
  int human2 = digitalRead(PIR2);
  
  int waitTime1 = 0;
  int waitTime2 = 0;

//EV1's one cycle is 60sec, EV2's one cycle is 45sec. one LED is for 1 meter, and it stands for one elevator cap.


// EV1 segment
  if (human1 == 1) {
    long distance1 = measureDistance(trig1, echo1);
    if (distance1 < 100) {
      waitTime1 = 120; // Less than 1 meter
    } else if (distance1 < 200) {
      waitTime1 = 60; // Less than 2 meters but >= 1 meter
    }
    Serial.print("EV1 Wait Time: ");
    Serial.print(waitTime1);
    Serial.println(" sec");
  }


//EV2 segment
  if (human2 == 1) {
    long distance2 = measureDistance(trig2, echo2);
    if (distance2 < 100) {
      waitTime2 = 90; // Less than 1 meter
      long distance3 = measureDistance(trig3, echo3);
      if (distance3 < 100) {
        waitTime2 += 45; // Additional 45 seconds for UL3
      }
    } else if (distance2 < 200) {
      waitTime2 = 45; // Less than 2 meters but >= 1 meter
    }
    Serial.print("EV2 Wait Time: ");
    Serial.print(waitTime2);
    Serial.println(" sec");
  }

  // Send wait times to Arduino 2 via I2C
  Wire.beginTransmission(8); // Transmit to device #8
  Wire.write(waitTime1);
  Wire.write(waitTime2);
  Wire.endTransmission();

  delay(1000);
}

long measureDistance(int trigPin, int echoPin) {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  return distance;
}
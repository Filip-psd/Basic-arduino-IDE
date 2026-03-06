#include "A.h"
#include "esp_system.h"
#include <ESP32Servo.h>

Servo servoMotor;

const int resetButtonPin = 4;
const int dacPin = 25;
const int sampleRate = 8000;
const int servoPin = 13;
const int buttonPin = 4;
const unsigned long xTime = 3000;  
const unsigned long yTime = 2000;
const int STOP = 90;
const int FULL_CW  = 0;
const int FULL_CCW = 180;

bool sequenceRunning = false;
bool playedOnce = false;
bool running = false;

void setup() {
  pinMode(resetButtonPin, INPUT_PULLUP);
  dacWrite(dacPin, 128);   // mid-scale bias

  servoMotor.setPeriodHertz(50);
  servoMotor.attach(servoPin, 500, 2400);
  servoMotor.write(STOP);

  pinMode(buttonPin, INPUT_PULLUP);
}



void loop() {

  if (digitalRead(resetButtonPin) == LOW) {
    delay(50);
    if (digitalRead(resetButtonPin) == LOW) {
      esp_restart();
    }
  }
  if (!playedOnce) {
    for (int i = 0; i < sounddata_length; i++) {
      dacWrite(dacPin, sounddata_data[i]);
      delayMicroseconds(1000000 / sampleRate);
    }
    playedOnce = true;
  }


}
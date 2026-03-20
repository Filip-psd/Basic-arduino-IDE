#include <EEPROM.h>
#define EEPROM_SIZE 1
const int buttonPin=4;
const int ledPin=16;
int ledState = HIGH;
int buttonState;
int LastButtonState = LOW;
unsigned long lastDebounceTime = 0 ;
unsigned long debounceDelay = 50 ;


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
EEPROM.begin(EEPROM_SIZE);
pinMode(buttonPin, INPUT);
pinMode(ledPin, OUTPUT);
ledState = EEPROM.read(0);
digitalWrite(ledPin,ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
int reading = digitalRead(buttonPin);
// check to see if you just pressed the button
// (i.e. the input went from LOW to HIGH), and you've waited long enough
// since the last press to ignore any noise:
// If the switch changed, due to noise or pressing:
if (reading != LastButtonState) {
// reset the debouncing timer
lastDebounceTime = millis();
}
if ((millis() - lastDebounceTime) > debounceDelay) {
// whatever the reading is at, it's been there for longer than the debounce
// delay, so take it as the actual current state:
// if the button state has changed:
if (reading != buttonState) {
buttonState = reading;
// only toggle the LED if the new button state is HIGH
if (buttonState == HIGH) {
ledState = !ledState;
}
}
}
// save the reading. Next time through the loop, it'll be the lastButtonState:
LastButtonState = reading;
// if the ledState variable is different from the current LED state
if (digitalRead(ledPin)!= ledState) {
Serial.println("State changed");
// change the LED state
digitalWrite(ledPin, ledState);
// save the LED state in flash memory
EEPROM.write(0, ledState);
EEPROM.commit();
Serial.println("State saved in flash memory");
}
}

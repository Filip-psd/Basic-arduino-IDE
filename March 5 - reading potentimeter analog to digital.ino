const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot

void setup() {
  // initialize serial communication at 115200
  Serial.begin(115200);
}

void loop() {
 sensorValue = analogRead(analogInPin) ;
 Serial.print("Nigger-electricution-prerequisite=");
 Serial.print(sensorValue);
 delay(1000);
}
 const int trigger_pin = D6;
 const int echo_pin = D7;
 const int led_pin = D5;
 long duration;
 int distance;
 int brightness;

void setup() {
  // put your setup code here, to run once:
 pinMode(trigger_pin, OUTPUT);
 pinMode(echo_pin, INPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(trigger_pin, LOW); 
 delayMicroseconds(2);
 digitalWrite(trigger_pin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger_pin, LOW);
 duration = pulseIn(echo_pin, HIGH);
 distance = duration*0.034/2;
 brightness = map(distance, 10, 20, 255, 0);
 brightness = constrain(brightness, 0, 255);
 analogWrite(led_pin, brightness);
 Serial.print("Distance=");
 Serial.println(distance);
}

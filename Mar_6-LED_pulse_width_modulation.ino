const int ledPin = 2; 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
 for(int dutyCycle=0 ; dutyCycle<255 ; dutyCycle++){
  analogWrite(ledPin, dutyCycle) ;
  delay(10) ;
 }


 for(int dutyCycle=255 ; dutyCycle>0 ; dutyCycle-- ){
  analogWrite(ledPin, dutyCycle) ;
  delay(10) ;
 } 
 }

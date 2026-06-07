#include <user_interface.h>
uint32_t bootCount ;
#define second_conversion_factor 1000000 
#define sleep_time 5 
void print_wakeup_reason() {
struct rst_info* wakeup_reason = system_get_rst_info();
switch (wakeup_reason->reason) {
        case REASON_EXT_SYS_RST : Serial.println("Wakeup caused by external signal using RTC_IO") ; break ;
        case REASON_DEEP_SLEEP_AWAKE : Serial.println("Wakeup caused by board reset"); break;
        default: Serial.printf("Other reset reason: %d\n", wakeup_reason->reason); break;
}
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  print_wakeup_reason();
  Serial.println("Setup ESP8266 to sleep for every" + String(sleep_time) + "seconds") ;
  Serial.println("Going to sle-e-e-e-e-p") ;
  Serial.flush() ;
  system_deep_sleep_instant(sleep_time * second_conversion_factor) ;
}

void loop()
{

}

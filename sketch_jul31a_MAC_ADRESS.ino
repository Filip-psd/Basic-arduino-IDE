#include <WiFi.h>

void setup() {
  WiFi.mode(WIFI_MODE_STA); //puts esp32 into station mode, allowing it to connect to a natwork
  Serial.begin(115200);
  Serial.println("MAC adress: ");
  Serial.print(WiFi.macAddress()); //yields the mac adress of the board

}

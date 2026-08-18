#include <esp_now.h>
#include <WiFi.h>
#define CHANNEL 1

uint8_t newData;

void ReceivedData (const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len){
  Serial.print("The data received: ");
  Serial.println(*data); //later, something could be done with the data if it were saved via the memcpy fction, for now  whe script just receives whatever was transmitted
  
  memcpy(&newData, data, sizeof(newData)); // memcpy(&to, from, size) - the destination needs to be a predefined variable
  Serial.print("New data: ");
  Serial.println(3 * newData); // example, the data is now stored and can be reused ofr eg. reprinting
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP); //ESP 32 is configured as an access point
  WiFi.softAP("RX_1", "1234567890", CHANNEL, 0); //starting the network as an access point - the network name and password are defined here, the ESP32 is becoming
  //the access point, not connecting to any external ones, format: WiFi.softAP("name", "password", CHANNEL, 0)
  esp_now_init();
  esp_now_register_recv_cb(ReceivedData); //function that runs every time data is received from the transmitter
}

void loop() {

}

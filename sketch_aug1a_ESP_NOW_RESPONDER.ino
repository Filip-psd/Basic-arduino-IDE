#include <WiFi.h>
#include <esp_now.h>

 struct structMessage { // defining data structure with transmitted message 
  char a[64];
  int b;
  float c;
  bool d;
};  //payload transmitted to responder board - needs to match byte for byte

struct structMessage myData; //structured object

void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) { //receive - side callback active immediately upon packet arriving, so loop can stay empty
  memcpy(&myData, incomingData, sizeof(myData)); //&myData is the destination (address of your local struct), incomingData is the source pointer (already a uint8_t* since memcpy's 
  // destination/source parameters are void*, which any pointer type converts to implicitly and sizeof(myData) defines how many bytes to copy
  Serial.print("data received");
  Serial.println(len);
  Serial.print("Character object received: ");
  Serial.println(myData.a);
  Serial.print("Integer object received: ");
  Serial.println(myData.b);
  Serial.print("Float object received: " );
  Serial.println(myData.c);
  Serial.println("Boolean received: ");
  Serial.print(myData.d);
} 

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if(esp_now_init()!=ESP_OK){
  Serial.println("Initializing failed - error");
  return; 
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
 //nothing goes in the loop, since callback function prints data onto serial monitor
}

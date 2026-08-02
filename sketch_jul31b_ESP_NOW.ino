#include <WiFi.h>
#include <esp_now.h>
#include <iostream>

int int_value;
bool boolyan_value;
float float_value; 

uint8_t macAdress[] = {0x8C, 0x94, 0xDF, 0x60, 0xDC, 0x18}; //mac adress of responder under unasigned 8 bit integer datatype within an array
struct struct_message {
 char a[64];
 int b;
 float c;
 bool d;
};
struct_message myData;
esp_now_peer_info_t peerInfo; // struct type providded by ESP_NOW library - bundles mac adress, wifi channel, encryption settings and everything
//to know about other device, needs to be filled before calling esp_now_add_peer

void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) { //
  Serial.print("Last Packet send status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "sending successful" : "sending failed"); //callback function, its signature must match what the
  //library expects in esp_now_send_cb_t, its going to be called whenever an attempt finishes
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //set esp as a wifi station
 
  if(esp_now_init() !=ESP_OK){
    Serial.println("initialization failed"); //initialize ESP NOW
    return;
 }

  esp_now_register_send_cb(OnDataSent); // OnDataSent is a function called whenever data has been sent, callback function registration line
  
  memcpy(peerInfo.peer_addr, macAdress, 6); //memcpy(destination, source, num_bytes) - copies 6 bytes of the mac array into peerInfo struct
  peerInfo.channel= 0; // 0 tells ESP-NOW to use whatever WiFi channel the device is currently on rather than forcing a specific channel.
  peerInfo.encrypt = false; // disables ESP-NOW's optional packet encryption for this peer
  
  if(esp_now_add_peer(&peerInfo)!=ESP_OK){ 
    Serial.println("failed to add peer"); //adding peer 
    return;
  }
}

void loop() {
  int_value = random(1,20);
  float_value = 1.3*int_value;
  boolyan_value != boolyan_value; 

  strcpy(myData.a, "hello"); //formatting structured data - strcpy(destination, source). copies the string into chara[64] array, hello is a string literal
  // which is stored as const char* pointing to that text in read-only memory, strcpy copies in byte by byte into the char array
  myData.b = int_value;
  myData.c = float_value;
  myData.d = boolyan_value;

  esp_err_t result = esp_now_send(macAdress, (uint8_t *) &myData, sizeof(myData)); //core transmission call
  if(result==ESP_OK){
    Serial.println("sending complete");
  } else{
    Serial.println("sending incomplete - error");
    delay(2000);
  }
}



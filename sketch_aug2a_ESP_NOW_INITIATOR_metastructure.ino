// include these two libraries for any esp_now script:
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

//type with ESP_NOW peer info parameters:
esp_now_peer_info_t responder;

//the actual data we want to send defined in the 8 bit integer datatype
uint8_t data = 0;

// defining the function that will run upon callback from Initiator to Responder
//the callback function will require 2 parameters: a pointer to the sending packet information and an error status code
void SentData (const esp_now_send_info_t *info, esp_now_send_status_t status){
  Serial.print("Data sent: ");
  Serial.println(data);
}

//defining the function that will scan for responders
void ScanForResponder (){
  int8_t NetworkScan = WiFi.scanNetworks(); //the WiFi.scanNetworks returns an array with integer number of networks found

  for(int i = 0; i<NetworkScan; i++){
    String SSID = WiFi.SSID(i); // obtains the name of each detected network
    String MacAdress = WiFi.BSSIDstr(i); //obtains the mac address of each detected network

    if (SSID.indexOf("RX")==0) { // I have no idea whether RX would actually work since RX is in receivers and other ESP boards are tachnically both receivers and initiators
    //the if statement runs only if RX has been found at position 0 in the mac adress string, so at the beginning
      int mac[6]; //declaring a 6 element integer array to contain the mac adress
      //c.str converts arduino string into const char* since sscanf does not recognize the string class 
      //"%x:%x:%x:%x:%x:%x": this is the format string telling sscanf to expect six hexadecimal numbers separated by colons
      //scanf("format string", comma separated list of adresses of variables) - in scanf placeholders are written, giving adress of variables rather than variables themselves
      if (6==sscanf(MacAdress.c_str(), "%x:%x:%x:%x:%x:%x", //scanf returns the number of successfully assigned fields, so the statement runs if that equals 6 (filled mac address)
       &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] )){
        for (int ii = 0; ii < 6;ii++){
          responder.peer_addr[ii] = (uint8_t) mac[ii]; // copies each parsed value into responder.peer_addr[], casting from int down to uint8_t
        }
      }
      responder.channel = CHANNEL; //sets peer channel
      responder.encrypt = 0;
      break;
    }
  }

}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init(); //initialize esp_now
  esp_now_register_send_cb(SentData); //registering a callback function
   ScanForResponder(); // !!IMPORTANT NOTE!! - instead of a function scanning for a responder, I could have just defined an array containing the mac address like so:
  /* uint8_t macAdress[] = {0x8C, 0x94, 0xDF, 0x60, 0xDC, 0x18};*/
    esp_now_add_peer(&responder); //registering responder as a peer, passing a memory adress to the peer

}

void loop() {
  esp_now_send(responder.peer_addr, &data, sizeof(data)); // esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  data++;
  delay(3000);
}

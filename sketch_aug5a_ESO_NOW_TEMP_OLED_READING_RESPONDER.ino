#include <esp_now.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct struct_message {
  float temperature;
  float pressure;
  float altitude;
};

struct struct_message2 {
  int light;
};

struct_message dataFromSensor1;
struct_message2 dataFromSensor2;
bool sensor1Received = false;
bool sensor2Received = false;

void OnDataParsed (const esp_now_recv_info_t *recv_info, const uint8_t *data, int len){
memcpy(&incomingData, data, sizeof(incomingData));
Serial.println("Data received!");
oled.clearDisplay();
oled.setCursor(0, 0);
oled.setTextSize(1);
oled.setTextColor(SSD1306_WHITE);
oled.println("Multisensor: ");
oled.print("Temperature: ");
oled.println(incomingData.temperature);
oled.print("Pressure: ");
oled.println(incomingData.pressure/100);
oled.print("Altitude: ");
oled.println(incomingData.altitude);
oled.display();
}

void setup() {
  Serial.begin(115200);
if (!oled.begin (SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed")); 
  while (true); 
} 
  WiFi.mode(WIFI_STA);
  if(esp_now_init()!=ESP_OK){
  Serial.println("Initializing failed - error");
  return; 
  }
  esp_now_register_recv_cb(OnDataParsed);
}

void loop() {

}

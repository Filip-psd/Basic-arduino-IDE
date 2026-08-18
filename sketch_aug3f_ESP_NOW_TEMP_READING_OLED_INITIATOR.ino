#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <esp_now.h>
#include <WiFi.h>

Adafruit_BMP280 bmp; 

uint8_t macAddress[] = {0x8C, 0x94, 0xDF, 0x60, 0xDC, 0x18};

struct struct_message {
  float temperature;
  float pressure;
  float altitude;
};

struct struct_message package;

void sensorRead (){
package.temperature = bmp.readTemperature();
package.pressure = bmp.readPressure();
package.altitude = bmp.readAltitude(1013.25);
delay(2000);
}

esp_now_peer_info_t responderInfo; 

void parsedData (const wifi_tx_info_t *tx_info, esp_now_send_status_t status){
  Serial.print("Package status ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "sending successful" : "sending failed");
  Serial.printf("T: %.2f  P: %.2f  A: %.2f\n", package.temperature, package.pressure, package.altitude);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Wire.begin();

 if(esp_now_init() != ESP_OK){
    Serial.println("failed to connect");
    return;
  }
  esp_now_register_send_cb(parsedData);
  memcpy(responderInfo.peer_addr, macAddress, 6);
  responderInfo.channel = 0;
  responderInfo.encrypt = false;

  if(esp_now_add_peer(&responderInfo)!=ESP_OK){ 
    Serial.println("failed to add responder"); 
    return;
  }

  while ( !Serial ) delay(100);   
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(0x76);
   Serial.println(status);
  
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  sensorRead();
  esp_err_t result = esp_now_send(macAddress, (uint8_t *) &package, sizeof(package)); 
  if(result==ESP_OK){
    Serial.println("Parsing complete");
  } else{
    Serial.println("Parsing incomplete - error");
    delay(2000);
  }
}

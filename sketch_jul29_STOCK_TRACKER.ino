#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>
#include <esp_system.h> 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const int buttonpin = 5;

Adafruit_SSD1306 oled (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "TP-Link_D36D";
const char* password = "30056282";

void setup() {
  Serial.begin(115200);
  pinMode(buttonpin, INPUT_PULLUP);
  if (!oled.begin (SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(true);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP adress: ");
  Serial.print(WiFi.localIP());
}

void readPrice(int x, int y, const String& stockName){
  String httpRequestAddress = "https://finnhub.io/api/v1/quote?symbol=" + stockName + "&token=d9jo8d9r01qr77bneov0d9jo8d9r01qr77bneovg";
  HTTPClient http;
  http.begin(httpRequestAddress);
  int code = http.GET();

  if(code==200){
    String payload = http.getString();
    JsonDocument doc;
    deserializeJson (doc, payload);

    float previousClosing = doc["pc"];
    float current = doc["c"];
    float percentagePriceDiff = ((current-previousClosing)/(previousClosing))*100;
    oled.clearDisplay();
    oled.setTextSize(2);
    oled.setTextColor(WHITE);
    oled.setCursor(x,y);
    oled.println(stockName);

    oled.setTextSize(1);
    oled.setCursor(0,25);
    oled.print(current);
    oled.println("USD");
    oled.print(percentagePriceDiff);
    oled.print("%");
    oled.display();
  }   else {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.println("Error in HTTP request");
    oled.display();
  }
  http.end();
}

void buttonSkip (int totalTime){
  int timeElapsed;
  while(timeElapsed < totalTime){
  if(digitalRead(buttonpin==LOW)){
    delay(10);
    return; // return 0 (void function), meaning it skips to the next iteration
  }
  delay(10);
  timeElapsed=+10;
  }
}



void loop() {
  int time = 3000;
  readPrice(0, 0, "AAPL"); buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "AMZN"); buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "TSLA"); buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "MSFT"); buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "PFE");  buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "OXY");  buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "EBAY"); buttonSkip(3000); oled.clearDisplay();
  readPrice(0, 0, "FDX");  buttonSkip(3000); oled.clearDisplay();
}

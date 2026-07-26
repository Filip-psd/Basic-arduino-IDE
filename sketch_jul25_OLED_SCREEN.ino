#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //including libraries necessary for OLED screen
#include "flag.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


Adafruit_SSD1306 OLED_DISPLAY (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); //declaring OLED_DISPLAY, an object with the arguments of screen height and width, a pointer to
// Wire (global objet for I2C communication), and -1 being the reset pin number (telling the library there is no reset pin)

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


  const uint8_t *frames[] = { //an array whose elements are pointers to uint8_t data
  bitmap_1,
  bitmap_2,
  bitmap_3,
  bitmap_4,
  bitmap_5,
  bitmap_6,
  bitmap_7,
  bitmap_8,
  bitmap_9,
  bitmap_10,
  bitmap_11,
  bitmap_12,
  bitmap_13,
  bitmap_14,
  bitmap_15,
  bitmap_16,
  bitmap_17,
  bitmap_18,
  bitmap_19,
  bitmap_20,
  bitmap_21,
  bitmap_22,
  bitmap_23,
  bitmap_24,
  bitmap_25,
  bitmap_26,
  bitmap_27,
  bitmap_28,
  bitmap_29,
  bitmap_30,
  bitmap_31,
  bitmap_32,
  bitmap_33,
  bitmap_34,
  bitmap_35,
  bitmap_36,
  bitmap_37,
  bitmap_38,
  bitmap_39,
  bitmap_40,
  bitmap_41,
  bitmap_42,
  bitmap_43,
  bitmap_44,
  bitmap_45,
  bitmap_46,
  bitmap_47,
  bitmap_48,
  bitmap_49,
  bitmap_50,
};

  const int FRAME_COUNT = sizeof(frames) / sizeof(frames[0]);; //size of all frames : size of one frame = frame count


void setup() {
Serial.begin(115200);
if (!OLED_DISPLAY.begin (SSD1306_SWITCHCAPVCC, 0x3C)) { // if OLED_display fails to initialize, the IDE prints a message
  Serial.println(F("SSD1306 allocation failed")); // F() tells the compiler to keep the string linear in flash memory, useful practise not to overload RAM
  while (true); // runs infinitely, so if OLED fails to initialize, void loop() does not activate
} 

}

void loop() {
  delay(1000);
  OLED_DISPLAY.clearDisplay(); 
  OLED_DISPLAY.setTextSize(1);         
  OLED_DISPLAY.setTextColor(WHITE);    
  OLED_DISPLAY.setCursor(15, 0); //set position on display      
  OLED_DISPLAY.println(" work in progress:"); 
  OLED_DISPLAY.display(); //display on OLED

  int analogValue=analogRead(4);
  float voltage = floatMap (analogValue, 0, 4095, 0, 3.3); //float map, mapping bits from ADC to voltage values
  Serial.print("Analog value: ");
  Serial.println(analogValue);
  Serial.print("Voltage value: ");
  Serial.println(voltage);
  delay(1);

  int percentage;
  percentage = map (analogValue, 0, 4095, 0, 100); 
  OLED_DISPLAY.println("");
  OLED_DISPLAY.setCursor(47, 25);
  OLED_DISPLAY.setTextSize(2);
  OLED_DISPLAY.print(percentage);
  OLED_DISPLAY.print("%");
  OLED_DISPLAY.display();

  int barX = 0;
  int barY = 44;
  int barHeight = 20;
  int barWidth = 128; 
  int fillWidth = map(percentage, 0, 100, 0, barWidth -3);
  OLED_DISPLAY.drawRect(barX, barY, barWidth, barHeight, WHITE);
  OLED_DISPLAY.fillRect(barX +2, barY +2, fillWidth, barHeight -3, WHITE);
  OLED_DISPLAY.display(); 

  while(percentage==100){
    for (int i = 0; i < FRAME_COUNT; i++) {
    OLED_DISPLAY.clearDisplay();

    OLED_DISPLAY.drawBitmap(
      0,
      0,
      frames[i], //iterating through frames using a for loop
      128,
      64,
      SSD1306_WHITE
    );

    OLED_DISPLAY.display();

    delay(40);   // 25 FPS
  }
}
  } // good reference for useful OLED commands: https://esp32io.com/tutorials/esp32-oled

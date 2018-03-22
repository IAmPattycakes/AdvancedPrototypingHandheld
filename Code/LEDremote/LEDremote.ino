#include <RotaryEncoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <EEPROM.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();

RotaryEncoder encoder(14, 27);

#define upBtn 16
#define dnBtn 17   //RX pin
#define cntrBtn 26 //TX pin

#define menuWidth 55

#define EEPROM_SIZE 256

void setup() {
  EEPROM.begin(EEPROM_SIZE);
  Serial.begin(115200);
  Serial.println("Began");
  pinMode(upBtn, INPUT);
  pinMode(dnBtn, INPUT);
  pinMode(cntrBtn, INPUT);
  initScreen();
}

void loop() {
  EEPROM.write(0, NULL);
  Serial.println(char(EEPROM.read(0)));
  drawMenu();
  updateEncoders();
  checkButtons();
  drawPicker();
  delay(99999);
}

void updateEncoders() {
  static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    pos = newPos;
  }
}

void checkButtons() {
  
  if(digitalRead(upBtn) == HIGH) {
    tft.println("Hello World Up");
    Serial.println("Up");
  }
  if(digitalRead(dnBtn) == HIGH) {
    tft.println("Hello World Down");
    Serial.println("Down");
  }
  if(digitalRead(cntrBtn) == LOW) {
    tft.println("Hello World Center");
    Serial.println("Center");
  }
}

void initScreen() {
  tft.init();
  tft.setRotation(1);
  tft.setTextColor(0xF000, 0x0000);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.fillScreen(0x0000);
  splashScreen();
}



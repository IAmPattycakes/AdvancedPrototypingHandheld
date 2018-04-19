#include <RotaryEncoder.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <EEPROM.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti WiFiMulti;

TFT_eSPI tft = TFT_eSPI();

RotaryEncoder encoder(14, 27);

#define upBtn 16
#define dnBtn 17   //RX pin
#define cntrBtn 26 //TX pin

#define menuWidth 55

#define EEPROM_SIZE 256

int currMenuItem = 1;
int encoderHome = 0;
boolean drawAgain = true;

void setup() {
  EEPROM.begin(EEPROM_SIZE);
  Serial.begin(115200);
  Serial.println("Began");
  pinMode(upBtn, INPUT);
  pinMode(dnBtn, INPUT);
  pinMode(cntrBtn, INPUT);
  initScreen();
  splashScreen();
  initWifi();
  tft.fillScreen(0x0000);
}

void loop() {
  Serial.println(currMenuItem);
  drawMenu();
  switch (currMenuItem) {
    case 0:
      drawHelpScreen();
      if (digitalRead(dnBtn) == HIGH) {
        delay(250);
        currMenuItem = 1;
      } else if (digitalRead(upBtn) == HIGH) {
        delay(250);
        currMenuItem = 2;
      }
      break;
    case 1:
      drawPicker();
      if (digitalRead(dnBtn) == HIGH) {
        delay(250);
        currMenuItem = 2;
      } else if (digitalRead(upBtn) == HIGH) {
        delay(250);
        currMenuItem = 0;
      }
      break;
    case 2:
      drawAboutScreen();
      if (digitalRead(dnBtn) == HIGH) {
        delay(250);
        currMenuItem = 0;
      } else if (digitalRead(upBtn) == HIGH) {
        delay(250);
        currMenuItem = 1;
      }
      break;
  }
  updateEncoders();
}

void updateEncoders() {
  int prev = encoder.getPosition();
  encoder.tick();
  if(prev != encoder.getPosition()) {
    drawAgain = true;
  }
}

void initScreen() {
  tft.init();
  tft.setRotation(1);
  tft.setTextColor(0xF000, 0x0000);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.fillScreen(0x0000);
}

int currPickerMode = 0;
float currHue = 0;
float currSat = 0;
float currVal = 0;
float currRed = 0;
float currGreen = 0;
float currBlue = 0;

uint32_t sendTimer = 0;


void drawPicker() {
  if (millis() - sendTimer > 500) {
    Serial.print(currHue);
    Serial.print(" ");
    Serial.print(currSat);
    Serial.print(" ");
    Serial.print(currVal);
    Serial.print(" ");
    Serial.print(currRed);
    Serial.print(" ");
    Serial.print(currGreen);
    Serial.print(" ");
    Serial.print(currBlue);
    Serial.print(" ");
    hsv convert;
    convert.h = currHue;
    convert.s = currSat;
    convert.v = currVal;
    rgb converted = hsv2rgb(convert);
    currRed = converted.r;
    currGreen = converted.g;
    currBlue = converted.b;
    String request = "192.168.2.1/color?r=";
    request += currRed;
    request += "&g=";
    request += currGreen;
    request += "&b=";
    request += currBlue;
    http.begin(request);
  }
  if (drawAgain) {
    drawHueSlider(56, 110, 104, 10);
    drawSatValSquare(56, 0, 104);
    drawPickerText(currPickerMode);
    drawAgain = false;
  }
  //Button input time
  if (digitalRead(cntrBtn) == LOW) {
    delay(250);
    currPickerMode++;
    currPickerMode = currPickerMode % 3;
    encoderHome = encoder.getPosition();
  }
  if (currPickerMode == 0) {
    currHue = float(encoder.getPosition()) / 255;
    if (currHue > 1) {
      encoderHome++;
    } else if (currHue < 0) {
      encoderHome--;
    }
  }
  if (currPickerMode == 1) {
    currSat = float(encoder.getPosition());
    if (currSat > 360) {
      encoderHome++;
    } else if (currSat < 0) {
      encoderHome--;
    }
  }
  if (currPickerMode == 2) {
    currVal = float(encoder.getPosition()) / 255;
    if (currVal > 360) {
      encoderHome++;
    } else if (currVal < 0) {
      encoderHome--;
    }
  }
  Serial.println(currPickerMode);
}
// Draws the static, always rainbow hue selector bar.
void drawHueSlider(int xStart, int yStart, int xWidth, int yHeight) {
  float ratio = float(256) / float(xWidth);
  for (int i = 0; i < xWidth; i++) {
    int r = 0;
    int g = 0;
    int b = 0;
    if (float(i) / xWidth < .33) {
      r = 256 - (i % (xWidth / 3) * 3 * ratio);
      g = (i % (xWidth / 3) * 3 * ratio) - 1;
    } else if (float(i) / xWidth < .66) {
      g = 256 - (i % (xWidth / 3) * 3 * ratio);
      b = (i % (xWidth / 3) * 3 * ratio) - 1;
    } else {
      b = 256 - (i % (xWidth / 3) * 3 * ratio);
      r = (i % (xWidth / 3) * 3 * ratio) - 1;
    }
    tft.drawFastVLine(i + xStart, yStart, yHeight, color24to16(r, g, b));
  }
}
// Draws the square that displays the Saturation/value of the current hue.
void drawSatValSquare(int xStart, int yStart, int sideLength) {
  float ratio = float(1) / float(sideLength);
  for (int y = yStart; y < sideLength + yStart; y++) {
    for (int x = xStart; x < sideLength + xStart; x++) {
      hsv currhsv;
      currhsv.h = currHue * 360.0;
      currhsv.s = float(x - xStart) * ratio;
      currhsv.v = 1 - float(y - yStart) * ratio;
      rgb currrgb = hsv2rgb(currhsv);
      tft.drawPixel(x, y, color24to16(currrgb.r * 256.0, currrgb.g * 256.0, currrgb.b * 256.0));
    }
  }
}
// Draws the text that indicates which axis the user is currently manipulating with a white highlight.
void drawPickerText(int modeNum) {
  int textNum = modeNum * 2;
  String pickerText[] = {"HUE", "   ", "SAT", "  ", "BRIGHT"};
  tft.setCursor(56, 120);
  tft.setTextSize(1);
  for (int i = 0; i < 5; i++) {
    if (i == textNum) {
      tft.setTextColor(0x0000, 0xffff);
    } else {
      tft.setTextColor(0xffff, 0x0000);
    }
    tft.print(pickerText[i]);
  }
}

void sendColorData(int r, int g, int b) {

}


//Converts 24 bit color (8, 8, 8) to 16 bit (5, 6, 5)
uint16_t color24to16(uint8_t r, uint8_t g, uint8_t b) {
  r >>= 3;
  g >>= 2;
  b >>= 3;
  return (b + (g * 32) + (r * 2048));
}

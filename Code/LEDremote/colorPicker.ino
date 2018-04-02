void drawPicker() {
  drawHueSlider(56, 110, 104, 10);
  drawPickerText(1);
}

void drawHueSlider(int xStart, int yStart, int xWidth, int yHeight) {
  float ratio = float(256) / float(xWidth);
  for (int i = 0; i < xWidth; i++) {
    int r = 0;
    int g = 0;
    int b = 0;
    if (float(i) / xWidth < .33) {
      r = 256 - (i % (xWidth / 3) * 3 * ratio);
      g = (i % (xWidth / 3) * 3 * ratio);
    } else if (float(i) / xWidth < .66) {
      g = 256 - (i % (xWidth / 3) * 3 * ratio);
      b = (i % (xWidth / 3) * 3 * ratio);
    } else {
      b = 256 - (i % (xWidth / 3) * 3 * ratio);
      r = (i % (xWidth / 3) * 3 * ratio);
    }
    tft.drawFastVLine(i + xStart, yStart, yHeight, color24to16(r, g, b));
  }
}

void drawSatValSquare(int xStart, int yStart, int sideLength) {
  for(int y = yStart; y <sideLength + yStart; y++) {
    for(int x = xStart; x < sideLength + xStart; x++) {
      tft.drawPixel(x, y, 
    }
  }
}

void drawPickerText(int modeNum) {
  tft.setCursor(56, 120);
  tft.setTextSize(1);
  tft.setTextColor(0x0000, 0xffff);  
  tft.print("HUE");
  tft.setTextColor(0xffff, 0x0000);
  tft.print("    SAT    VAL");
  
}

uint16_t color24to16(uint8_t r, uint8_t g, uint8_t b) {
  r >>= 3;
  g >>= 2;
  b >>= 3; 
  return (b + (g * 32) + (r * 2048));
  Serial.println("Hi");
}

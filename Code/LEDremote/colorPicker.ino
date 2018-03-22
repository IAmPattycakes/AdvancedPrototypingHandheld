void drawPicker() {
  drawHueSlider(56, 110, 104, 10);
}

void drawHueSlider(int xStart, int yStart, int xWidth, int yHeight) {
  float ratio = float(255) / float(xWidth);
  for (int i = 0; i < xWidth; i++) {
    int r = 0;
    int g = 0;
    int b = 0;
    if (float(i) / xWidth < .33) {
      r = 255 - (i % (xWidth / 3) * 3 * ratio);
      g = i % (xWidth / 3) * 3 * ratio;
    } else if (float(i) / xWidth < .66) {
      g = 255 - (i % (xWidth / 3) * 3 * ratio);
      b = i % (xWidth / 3) * 3 * ratio;
    } else {
      b = 255 - (i % (xWidth / 3) * 3 * ratio);
      r = i % (xWidth / 3) * 3 * ratio;
    }
    tft.fillRect( 10, 10, 20, 20, 63519);
    Serial.print("Output: ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.print(b);
    Serial.println();
    tft.drawFastVLine(i + xStart, yStart, yHeight, RGB24to16bit((r * 256 * 256) + (g * 256) + b));
  }
}

uint16_t RGB24to16bit (uint32_t c) {
  //Color is a 24 bit unsigned int represented in hex as 0xRRGGBB
  //This function turns that into 0xRGGB for display on the TFT screen.

  int r = (c / 65536) / 8; //Grabs the most significant digit of the red color,
  int g = ((c % 65536) / 256) / 4; // Initially pulls out 8 bit number, then takes most significant 6
  int b = (c % 256) / 8; // takes most significant 5 bits of B
  Serial.println("Input: ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(b);
  Serial.println();
  return (r * 16 * 16 * 16) + (g * 16) + b;
}

void drawPickerText(int modeNum) {

}


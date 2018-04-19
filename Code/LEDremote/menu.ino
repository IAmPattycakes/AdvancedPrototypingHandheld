
void drawMenu() {
  tft.drawFastVLine(menuWidth, 0, 128, 0xFFFF);

  tft.setTextColor(0xFFFF, 0x0000);
  tft.setCursor(0, 0);
  tft.print("About");
  tft.setCursor(0, 10);
  tft.print("Help");
  tft.setCursor(0, 20);
  tft.setTextColor(0x0000, 0xFFFF);
  tft.print("Lightbulb");
  tft.setCursor(0, 30);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.print("WiFi");
}

void drawMenuItem(int itemNum, String itemName) {
  String itemString = itemName;
  if (itemString.length() < 8) {
    // itemString +=
  }
  if (itemNum == currMenuItem) {
    tft.setTextColor(0x0000, 0xFFFF);
  } else {
    tft.setTextColor(0xFFFF, 0x0000);
  }
  tft.setCursor(0, itemNum * 8);
  tft.print(itemName);
}


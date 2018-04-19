String aboutScreenStuff[] = 
{
  "This device was", 
  "created by",
  "Patrick Groh. It",
  "is to be used",
  "with the smart",
  "home thing that",
  "he is also",
  "making. It makes",
  "lights do pretty",
  "things."
};

int scrollAmount = 0;

void drawAboutScreen() {
  
  if(encoderHome >= encoder.getPosition()) {
    scrollAmount = 0;
    encoderHome = encoder.getPosition();
  } else {
    scrollAmount = encoder.getPosition() - encoderHome;
  }
  
  tft.setTextColor(0xFFFF, 0x0000);
  for(int i = scrollAmount; i < 10; i++) {
    tft.setCursor(57, (i - scrollAmount) * 8);
    tft.println(aboutScreenStuff[i]);
  }
}


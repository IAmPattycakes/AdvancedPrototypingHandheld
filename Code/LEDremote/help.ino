String helpScreenStuff[] = 
{ /////////////////////
  "The UP and DOWN", //
  "buttons are for", //
  "scrolling up and",//
  "down the main",   //
  "menu on the ",    //
  "left. The center",//
  "wheel is for",    //
  "interacting with",//
  "the screen on",   //
  "the right, by",   //
  "either scrolling",//
  "by turning it,",  //
  "or pressing down",//
  "to select or",    //
  "change modes",    //
};

void drawHelpScreen() {
  
  if(encoderHome >= encoder.getPosition()) {
    scrollAmount = 0;
    encoderHome = encoder.getPosition();
  } else {
    scrollAmount = encoder.getPosition() - encoderHome;
  }
  
  tft.setTextColor(0xFFFF, 0x0000);
  for(int i = scrollAmount; i < 15; i++) {
    tft.setCursor(57, (i - scrollAmount) * 8);
    tft.println(helpScreenStuff[i]);
  }
}


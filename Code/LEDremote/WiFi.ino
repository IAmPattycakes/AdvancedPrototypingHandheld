/*
 * Wifi information in the EEPROM will be in a format with: 
 * a written bit (bit 0) to see if the Wifi information has been written before, 
 * a NULL character before the SSID information, 
 * a string of characters with the SSID information,
 * another NULL character between the SSID and password, signifying the end of SSID
 * a string of characters for the password
 * another NULL character to signify the password has ended. 
 */
// This is the list of the characters that will be chosen via the wifi SSID/password pickers
#define characterSelection = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+,.<>/?"
HTTPClient http;

void initWifi() {
  if(EEPROM.read(0) == 0) { // begins WiFi picker if the "set"
    wifiPicker();
  } 
  Serial.println("hi");
  WiFiMulti.addAP(wifiSSID().c_str(), wifiPassword().c_str());
  while(!(WiFiMulti.run() == WL_CONNECTED) && millis() < 5000) {
    Serial.println("hi");
    tft.setCursor(20, 100);
    tft.println("Connecting to WiFi");
  }

}

void wifiConnecting() {
  Serial.println("Waiting for connection");
  delay(500);
}

void wifiPicker() {
  int field = 0;
  String currentSSID;
  String currentPassword;
  switch(field) {
    case 0: //Enter SSID
    currentSSID = pickSSID().c_str();
    break;
    case 1: //Enter password
    break;
    case 2: //Confirmation button
    break;
  }
}

String pickSSID() {
  while(digitalRead(upBtn) == 0 && digitalRead(dnBtn) == 0) {
    int buttonStatus = 1; //Center button uses reverse logic
    switch(buttonStatus) {
      case 1: 
      
      break;
      case 0:
      delay(1); //Just wait in here, very basic debouncing.
      buttonStatus = digitalRead(cntrBtn);
      break;
    }
  }
}

String wifiSSID() {
  return "HackBerry";
  int startingPos = SSIDStartingPos();
  String returner = ""; //Initialize the return string
  for(int i = startingPos; i < EEPROM_SIZE; i++) {
    if(EEPROM.read(i) == NULL) {
      return returner; //Returns full SSID after finding the NULL character
    }
    returner += EEPROM.read(i); //Concatenates the currently read character of the SSID
  }
  return returner;
}

String wifiPassword() {
  return "CreativeTechnologies!";
  int startingPos = passwordStartingPos();
  String returner = ""; //Initialize the return string
  for(int i = startingPos; i < EEPROM_SIZE; i++) {
    if(EEPROM.read(i) == NULL) {
      return returner; //Returns full SSID after finding the NULL character
    }
    returner += EEPROM.read(i); //Concatenates the currently read character of the SSID
  }
  return returner;
}

int SSIDStartingPos() {
  for(int i = 1; i < EEPROM_SIZE; i++) {
    if(EEPROM.read(i) == NULL) return i + 1; //Returns i + 1 for beginning of SSID
  }
  return -1; // Returns -1 if it cannot find a proper position
}

int passwordStartingPos() {
  for(int i = SSIDStartingPos() + 1; i < EEPROM_SIZE; i++) {
    if(EEPROM.read(i) == NULL) return i + 1; //Returns i + 1 for beginning of SSID
  }
  return -1;
}


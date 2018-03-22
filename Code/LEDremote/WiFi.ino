/*
 * Wifi information in the EEPROM will be in a format with: 
 * a written bit (bit 0) to see if the Wifi information has been written before, 
 * a NULL character before the SSID information, 
 * a string of characters with the SSID information,
 * another NULL character between the SSID and password, signifying the end of SSID
 * a string of characters for the password
 * another NULL character to signify the password has ended. 
 */

#define characterSelection = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+,.<>/?"

void initWifi() {
  if(EEPROM.read(0) == 0) {
    wifiPicker();
  } 
  WiFi.begin(wifiSSID().c_str(), wifiPassword().c_str());
  while(WiFi.status() != WL_CONNECTED) {
    wifiConnecting();
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


#include <LiquidCrystal.h>

boolean isConn = false;

String inStr = "";
boolean strComplete = false;

int p = 0;

LiquidCrystal lcd(11, 12, 5, 4, 3, 2);

int connHello(int p) {
  if (p == 4) {
    lcd.setCursor(11, 1);
    lcd.print("   ");
  }
  else if (p >= 1) {
    lcd.setCursor(10 + p, 1);
    lcd.print(".");
    
    return p + 1;
  }
  else {
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Comp Info");
    
    lcd.setCursor(0, 1);
    lcd.print("\xA8\x6F\xE3\xBA\xBB\xC6\xC0\x65\xBD\xB8\x65");
  }
  
  return 1;
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
}

void loop() {
  if (isConn == false) {
    p = connHello(p);
  }

  inStr = Serial.readStringUntil('\n');

  if (inStr.length() > 0) {
    strComplete = true;
  }
  else if (isConn == true) {
    isConn = false;
    p = 0;
    
    Serial.setTimeout(1000);

    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("\x4F\xAC\xA5\xA0\x4B\x41\x3A");
    
    lcd.setCursor(0, 1);
    lcd.print("\x48\x65\xBF \x6F\xBF\xB3\x65\xBF\x61");
    
    delay(3000);
  }
  
  if (strComplete) {
    String cmd = getValue(inStr, '|', 0);

    if (cmd == "HLEO" && isConn == false) {
      Serial.println("HBLN");
      
      isConn = true;
    
      lcd.setCursor(0, 1);
      lcd.print("\xA8\x6F\xE3\xBA\xBB\xC6\xC0\x65\xBD\x6F\x21   ");
    
      delay(3000);

      Serial.println("REDY");
      Serial.setTimeout(5000);

      lcd.clear();
      
      lcd.setCursor(0, 0);
      lcd.print(" \xE1\xA8 \x2D \x2D.\x2D\x25");
      
      lcd.setCursor(0, 1);
      lcd.print("\x4F\xA4\xA9 \x2D \x2D.\x2D\x25");
    }
    else if (cmd == "DATA" && isConn == true) {
      float cpu = getValue(inStr, '|', 1).toFloat();
      float ram = getValue(inStr, '|', 2).toFloat();
  
      String cpuout = String(cpu, 1);
      String ramout = String(ram, 1);

      lcd.setCursor(6, 0);

      if (cpu < 10) {
        lcd.print(cpuout + "\x25  ");
      }
      else if (cpu >= 100) {
        lcd.print(cpuout + "\x25");
      }
      else {
        lcd.print(cpuout + "\x25 ");
      }
    
      lcd.setCursor(6, 1);
    
      if (ram < 10) {
        lcd.print(ramout + "\x25  ");
      }
      else if (ram >= 100) {
        lcd.print(ramout + "\x25");
      }
      else {
        lcd.print(ramout + "\x25 ");
      }
    }
  
  inStr = "";
    strComplete = false;
  }
}

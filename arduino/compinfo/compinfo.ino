#include <LiquidCrystal.h>

boolean isConn = false;

String inStr = "";
boolean strComplete = false;

int page = 1;

int p = 0;
int t = 0;
int s = 0;

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

String byteConvertStr(float bytes) {
  int i = 0;
  
  for (i; i < 4; i++) {
    if (bytes < 1000) {
      break;
    }
    
    bytes = bytes / 1024;
  }

  String value = String(bytes, 2);

  if (i == 0) {
    return String(bytes, 0) + " \xA0       ";
  }
  else if (i == 1) {
    return value + " \x4B\xB2   ";
  }
  else if (i == 2) {
    return value + " \x4D\xB2   ";
  }
  else if (i == 3) {
    return value + " \xA1\xB2   ";
  }
  else {
    return value + " \x54\xB2   ";
  }
}

void percentCpuRam(float cpu, float ram) {
  lcd.setCursor(0, 0);
  lcd.print(" \xE1\xA8 \x2D ");

  lcd.setCursor(6, 0);
  
  if (cpu == -1) {
    lcd.print("\x2D.\x2D\x25      ");
  }
  else {
    String cpuout = String(cpu, 1);
    
    lcd.print(cpuout + "\x25      ");
  }

  lcd.setCursor(0, 1);
  lcd.print("\x4F\xA4\xA9 \x2D ");

  lcd.setCursor(6, 1);
  
  if (ram == -1) {
    lcd.print("\x2D.\x2D\x25      ");
  }
  else {
    String ramout = String(ram, 1);
    
    lcd.print(ramout + "\x25      ");
  }
}

void valueRam(float ramcur, float ramttl) {
  lcd.setCursor(0, 0);
  lcd.print("\x4F\xA4\xA9 \x2D ");

  lcd.setCursor(6, 0);
  
  if (ramcur == -1) {
    lcd.print("\x2D \xA0       ");
  }
  else {
    String ramcurout = byteConvertStr(ramcur);

    lcd.print(ramcurout);
  }

  lcd.setCursor(0, 1);
  lcd.print("   \xB8\xB7 ");

  lcd.setCursor(6, 1);
  
  if (ramttl == -1) {
    lcd.print("\x2D \xA0       ");
  }
  else {
    String ramttlout = byteConvertStr(ramttl);

    lcd.print(ramttlout);
  }
}

void percentSwap(float swap) {
  lcd.setCursor(0, 0);
  lcd.print("\xAA\xA8 \x2D ");

  lcd.setCursor(5, 0);
  
  if (swap == -1) {
    lcd.print("\x2D.\x2D\x25       ");
  }
  else {
    String swapout = String(swap, 1);
    
    lcd.print(swapout + "\x25       ");
  }

  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void valueSwap(float swapcur, float swapttl) {
  lcd.setCursor(0, 0);
  lcd.print("\xAA\xA8 \x2D ");

  lcd.setCursor(5, 0);
  
  if (swapcur == -1) {
    lcd.print("\x2D \xA0        ");
  }
  else {
    String swapcurout = byteConvertStr(swapcur);

    lcd.print(swapcurout);
  }

  lcd.setCursor(0, 1);
  lcd.print("  \xB8\xB7 ");

  lcd.setCursor(5, 1);
  
  if (swapttl == -1) {
    lcd.print("\x2D \xA0        ");
  }
  else {
    String swapttlout = byteConvertStr(swapttl);

    lcd.print(swapttlout);
  }
}

void percentCpuAvg(float cpuavg1, float cpuavg5, float cpuavg15) {
  if (page == 5) {
    lcd.setCursor(0, 0);
    lcd.print("\xE1\xA8\x43\x70\x31 \x2D ");
  
    lcd.setCursor(8, 0);
    
    if (cpuavg1 == -1) {
      lcd.print("\x2D.\x2D\x25  ");
    }
    else {
      String cpuavg1out = String(cpuavg1, 1);
      
      lcd.print(cpuavg1out + "\x25  ");
    }
  
    lcd.setCursor(0, 1);
    lcd.print("\xE1\xA8\x43\x70\x35 \x2D ");
  
    lcd.setCursor(8, 1);
    
    if (cpuavg5 == -1) {
      lcd.print("\x2D.\x2D\x25  ");
    }
    else {
      String cpuavg5out = String(cpuavg5, 1);
      
      lcd.print(cpuavg5out + "\x25  ");
    }
  }
  else if (page == 6) {
    lcd.setCursor(0, 0);
    lcd.print("\xE1\xA8\x43\x70\x31\x35 \x2D ");
  
    lcd.setCursor(9, 0);
    
    if (cpuavg15 == -1) {
      lcd.print("\x2D.\x2D\x25 ");
    }
    else {
      String cpuavg15out = String(cpuavg15, 1);
      
      lcd.print(cpuavg15out + "\x25 ");
    }

    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
}

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
}

void loop() {
  if (isConn == false) {
    p = connHello(p);
  }
  else {
    p = 0;
  }

  inStr = Serial.readStringUntil('\n');

  if (inStr.length() > 0) {
    strComplete = true;
  }
  else if (isConn == true) {
    if (t == 2) {
      isConn = false;
      
      page = 1;
      
      t = 0;
      s = 0;

      Serial.setTimeout(1000);

      lcd.clear();
    
      lcd.setCursor(0, 0);
      lcd.print("\x4F\xAC\xA5\xA0\x4B\x41\x3A");
    
      lcd.setCursor(0, 1);
      lcd.print("\x48\x65\xBF \xE3\x61\xBD\xBD\xC3\x78");
    
      delay(3000);
    }
    else {
      switch (page) {
        case 1:
          percentCpuRam(-1, -1);
          break;
        case 2:
          valueRam(-1, -1);
          break;
        case 3:
          percentSwap(-1);
          break;
        case 4:
          valueSwap(-1, -1);
          break;
        case 5:
        case 6:
          percentCpuAvg(-1, -1, -1);
          break;
      }

      if (s == 9) {
        if (page != 6) {
          page++;
        }
        else {
          page = 1;
        }

        s = 0;
      }
      else {
        s++;  
      }
    }
    
    t++;
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
      Serial.setTimeout(1500);

      lcd.clear();
      percentCpuRam(-1, -1);
    }
    else if (cmd == "DATA" && isConn == true) {
      t = 0;

      switch (page) {
        case 1:
          percentCpuRam(getValue(inStr, '|', 1).toFloat(), getValue(inStr, '|', 2).toFloat());
          break;
        case 2:
          valueRam(getValue(inStr, '|', 3).toFloat(), getValue(inStr, '|', 4).toFloat());
          break;
        case 3:
          percentSwap(getValue(inStr, '|', 5).toFloat());
          break;
        case 4:
          valueSwap(getValue(inStr, '|', 6).toFloat(), getValue(inStr, '|', 7).toFloat());
          break;
        case 5:
        case 6:
          percentCpuAvg(getValue(inStr, '|', 8).toFloat(), getValue(inStr, '|', 9).toFloat(), getValue(inStr, '|', 10).toFloat());
          break;
      }

      if (s == 9) {
        if (page != 6) {
          page++;
        }
        else {
          page = 1;
        }

        s = 0;
      }
      else {
        s++;  
      }
    }
    else if (cmd == "BYEL" && isConn == true) {
      isConn = false;

      Serial.setTimeout(1000);
      
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("\xA4\x61\xB3\x65\x70\xC1\x65\xBD\x6F");

      delay(3000);
    }
  
    inStr = "";
    strComplete = false;
  }
}

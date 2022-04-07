



uint32_t effTimer; // таймер для эффектов
uint32_t IRTimer; // таймер для эффектов
int effTMil = 110; // задержка таймера
int effTMil_curr; // чтоб выбирать для каждого эффекта
bool irGo = true;
bool effOn = false; // запущен эффект
bool timerRef = false;
byte cauntIR = 0;


void control() {
  
  if (IRLremote.available()) {
    irGo = true;
    auto data = IRLremote.read();
    IRdata = data.command;
    if (effOn) {
      effTMil = 400;
      if (timerRef) {
        timerRef = false;
        IRTimer = millis();
      }
    }
  }

  if (millis() - IRTimer >= 2000) {
    effTMil = effTMil_curr;
    timerRef = true;
  }

  if (irGo) {
    irGo = false;
    
    if (IRdata == ON) {
      ButNumClick = 4;
    } else if (IRdata == OFF) {
      ButNumClick = 3;
    }

    switch (IRdata) {
      case BRUGN_UP: 
        ButNumClick = 1;
        break;
      case BRUGN_DOWN:
        ButNumClick = 2;
        break;
      case BUT_R:
        ButNumClick = 5;
        effOn = false;
        break;
      case BUT_G:
        ButNumClick = 6;
        effOn = false;
        break;
      case BUT_B:
        ButNumClick = 7;
        effOn = false;
        break;
      case BUT_W:
        ButNumClick = 8;
        effOn = false;
        break;
      case COLOR_0:
        ButNumClick = 9;
        effOn = false;
        break;
      case COLOR_1:
        ButNumClick = 10;
        effOn = false;
        break;
      case COLOR_2:
        ButNumClick = 11;
        effOn = false;
        break;
      case COLOR_3:
        ButNumClick = 13;
        effOn = false;
        break;
      case COLOR_4:
        ButNumClick = 14;
        effOn = false;
        break;
      case COLOR_5:
        ButNumClick = 15;
        effOn = false;
        break;
      case COLOR_6:
        ButNumClick = 17;
        effOn = false;
        break;
      case COLOR_7:
        ButNumClick = 18;
        effOn = false;
        break;
      case COLOR_8:
        ButNumClick = 19;
        effOn = false;
        break;
     case COLOR_9:
        ButNumClick = 21;
        effOn = false;
        break;
     case COLOR_10:
        ButNumClick = 22;
        effOn = false;
        break;
        
      case EFFECT_0:
        ButNumClick = 12;
        effOn = true;
        break;
      case EFFECT_1:
        ButNumClick = 16;
        effOn = true;
        break;
      case EFFECT_2:
        ButNumClick = 20;
        effOn = true;
        break;
      case EFFECT_3:
        ButNumClick = 24;
        effOn = true;
        break;

      case BUT_TYPES:
        typeLents = !typeLents;
        // Serial.print("typeLents : "); Serial.println(typeLents);
        if (typeLents == 0) {
          lents.setBrightness(0);
          delay(100);
          lents.setBrightness(Brightness);
        } else if (typeLents == 1) {
          strip.setBrightness(0);
          strip.begin();
            for (int i = 0; i < number; i++) {
              strip.send(mRGB(0, 0, 0));
            }
          strip.end();
          delay(100);
          strip.setBrightness(Brightness);
          strip.begin();
            for (int i = 0; i < number; i++) {
              strip.send(colorWSD);
            }
          strip.end();
        }
        break;
    }
    Serial.print("ButNumClick : "); Serial.println(ButNumClick);
  }
}



// Команды для WSD ленты


void wsd_comands() {

  if (ButNumClick == 3) { // OFF
    ButNumClick = ButNumClick_last;
    if (Startap == false) return;
    Startap = false;
    for (int i = Brightness; i > 0; i--) {
      strip.setBrightness(i);
      if (effOn == false) {
        strip.begin();
          for (int i = 0; i < number; i++) {
            strip.send(colorWSD);
          }
        strip.end();
      } 
       else { // эффект ?????
         //rainbow();
         strip.setBrightness(0);
         strip.begin();
            for (int i = 0; i < number; i++) {
              strip.send(colorWSD);
            }
          strip.end();
       }
      delay(2);
    }
    // strip.setBrightness(0);
  } else if (ButNumClick == 4) { // ON
    ButNumClick = ButNumClick_last;
    if (Startap == true) return;
    Startap = true;
    for (int i = 0; i < Brightness; i++) {
      strip.setBrightness(i);
      if (effOn == false) {
        strip.begin();
          for (int i = 0; i < number; i++) {
            strip.send(colorWSD);
          }
        strip.end();
        delay(2);
      } else {
        strip.setBrightness(Brightness);
        strip.begin();
          for (int i = 0; i < number; i++) {
            strip.send(colorWSD);
          }
        strip.end();
      }
    }
  }

  if (Startap == false) return;

  if (ButNumClick == 1) {
    ButNumClick = ButNumClick_last;
    for (int i = 0; i < 64; i++) {
      Brightness++;
      if (Brightness > 255) {
        Brightness = 255;
        break;
      }
      strip.setBrightness(Brightness);
      if (effOn == false) { // если не эффект
        strip.begin();
          for (int i = 0; i < number; i++) {
            strip.send(colorWSD);
          }
        strip.end();
      } else { // если эффект
        // даже нет смысла делать :(
      }
      delay(2);
    }
    // Serial.print("Brightness: "); Serial.println(Brightness);
  } else if (ButNumClick == 2) {
    ButNumClick = ButNumClick_last;
    for (int i = 0; i < 64; i++) {
      Brightness--;
      if (Brightness < 64) {
        Brightness = 64;
        break;
      }
      strip.setBrightness(Brightness);
      if (effOn == false) { // если не эффект
        strip.begin();
          for (int i = 0; i < number; i++) {
            strip.send(colorWSD);
          }
        strip.end();
      }
      delay(2);
    }
    // Serial.print("Brightness: "); Serial.println(Brightness);
  }

  if (ButNumClick == 12) {
    effOn = true;
    ButNumClick_last = ButNumClick;
    effTMil_curr = 30;
    rainbow();
  } else if (ButNumClick == 16) {
    ButNumClick_last = ButNumClick;
    effTMil_curr = 30;
    effOn = true;
    fire();
  } else if (ButNumClick == 20) {
    ButNumClick_last = ButNumClick;
    effOn = true;
    effTMil_curr = 30;
    commets();
  } else if (ButNumClick == 24) {
    ButNumClick_last = ButNumClick;
    effTMil_curr = 45;
    effOn = true;
    bpm();
  }

  if (ButNumClick == 5) {
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(255, 0, 0);
    fadeToWs(255, 0, 0);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 6) {
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(0, 255, 0);
    fadeToWs(0, 255, 0);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 7) {
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(0, 0, 255);
    fadeToWs(0, 0, 255);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 8) {
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(255, 255, 255);
    fadeToWs(255, 255, 255);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 9) { // COLOR_0
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(220, 90, 20);
    fadeToWs(220, 90, 20);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 10) { // COLOR_1
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(40, 230, 20);
    fadeToWs(40, 230, 20);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 11) { // COLOR_2
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(23, 108, 172);
    fadeToWs(23, 108, 172);
    ButNumClick = 0;
    //effOn = false;
  } else if (ButNumClick == 13) { // COLOR_3
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(220, 71, 47);
    fadeToWs(220, 71, 47);
    ButNumClick = 0;
  } else if (ButNumClick == 14) { // COLOR_4
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(12, 153, 196);
    fadeToWs(12, 153, 196);
    ButNumClick = 0;
  } else if (ButNumClick == 15) { // COLOR_5
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(76, 19, 60);
    fadeToWs(76, 19, 60);
    ButNumClick = 0;
  } else if (ButNumClick == 17) { // COLOR_6
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(222, 95, 50);
    fadeToWs(222, 95, 50);
    ButNumClick = 0;
  } else if (ButNumClick == 18) { // COLOR_7
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(4, 82, 144);
    fadeToWs(4, 82, 144);
    ButNumClick = 0;
  } else if (ButNumClick == 19) { // COLOR_8
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(105, 6, 34);
    fadeToWs(105, 6, 34);
    ButNumClick = 0;
  } else if (ButNumClick == 21) { // COLOR_9
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(220, 180, 16);
    fadeToWs(219, 194, 16);
    ButNumClick = 0;
  } else if (ButNumClick == 22) { // COLOR_10
    ButNumClick_last = ButNumClick;
    colorWSD = mRGB(238, 10, 51);
    fadeToWs(238, 10, 51);
    ButNumClick = 0;
  }
  //    if (ButNumClick == 11) { // COLOR_2
  //      colorWSD = mRGB(23, 108, 172);
  //      fadeToWs_Stop = false;
  //      if (!fadeToWs_Stop) {
  //        fadeToWs(23, 108, 172); // плавно перейти в новый колор
  //      }
  //      ButNumClick = 0;
  //    }
}


void rainbow() {
  if (millis() - effTimer >= effTMil) {
    static byte counter = 0;
    static int i = 0;
    strip.begin();
      for (int i = 0; i < number; i++) {
        strip.send(mWheel8(counter + i * 255 / number)); // выводим радугу
      }
    strip.end();
    counter += 3;
    effTimer = millis();
  }
}

void fire() {
  if (millis() - effTimer >= effTMil) {
    static int count = 0;
    count += 10;
    strip.begin();
      for (int i = 0; i < number; i++) {
        strip.send(CRGBtoData(ColorFromPalette(fire_p, inoise8(i * 25, count), 255, LINEARBLEND)));
      }
    strip.end();
    effTimer = millis();
  }
}


// бегущие частицы 1D, потоковая версия

#define COLOR_STEP 10 // шаг цвета, интересные 151, 129
#define PART_SP 1 // скорость движения частиц
#define LEDS_AM 10 // количество светодиодов
#define PART_AM 50 // макс. количество частиц
#define FADE_VAL 100 // скорость затухания

int numbers = 100; // количество светодиодов
int tailSize = 2; // длина
int partsPos[100]; // массив для позиций всех частиц
byte partsCol[100]; // цвет частиц
byte partsBrig[100]; // яркость частиц
int partsEx = 0; // количество активных частиц
int lastPart; // младшая частица ???
bool sensor, sensor_last;
bool commHid = true; // комета скрылось
byte curColor = 255; // текущий цвет
byte curBrig = 255; // текущая яркость
byte brig_level; // шаг изменения яркости

mData color = mWheel8(140);  // тут храним цвет

int commetSize = 0; // текущий размер кометы
int headCommet; // голова новой комметы
int respavnPoint = 10; // Рандомная точка появления новой комметы


void commets() {

  if (millis() - effTimer >= effTMil) {

    for (int i = 0; i < partsEx; i++) {
      partsPos[i] += 1;
    }
    
    if (partsEx > 0) {
      headCommet++;
    }
  
    if (partsPos[0] >= numbers) {
      for (int i = 0; i < partsEx - 1; i++) { // ???
        partsPos[i] = partsPos[i + 1];
        partsCol[i] = partsCol[i + 1];
        partsBrig[i] = partsBrig[i + 1];
      }
      partsEx--;
    }
  
    if (headCommet > respavnPoint) {
      tailSize = random(6, 12);
      curBrig = 255;
      curColor += 34;
      brig_level = 255 / tailSize;
      respavnPoint = random(numbers/10, numbers/4);
      commetSize = 0;
    }
    
    if (partsEx < 100) { // partsEx < tailSize
      if (commetSize < tailSize) {
        if (commetSize == 0) { // если это начало новой комметы
          headCommet = 0;
        }
        commetSize++;
        partsEx++;
        partsPos[partsEx - 1] = 0;
        partsCol[partsEx - 1] = curColor;
        partsBrig[partsEx - 1] = curBrig;
        curBrig -= brig_level;
      }
    }
  
    lastPart = partsEx - 1; // младшая частица
  
    strip.begin();
      for (int i = 0; i < numbers; i++) {
        if (lastPart >= 0 && i > partsPos[lastPart] - 1 and i <= partsPos[lastPart]) {
          color = mWheel8(partsCol[lastPart], partsBrig[lastPart]);
          if (i == partsPos[lastPart]) lastPart--;
        } else {
          color = mRGB(0, 0, 0); // иначе чёрный
        }
        //for (int i = 0; i < 2; i++) {
          strip.send(color);
        //}
      }
    strip.end();

    effTimer = millis();
  }
  
}

void bpm() {
  if (millis() - effTimer >= effTMil) {
    uint8_t BeatsPerMinute = 10;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 65, 255);
    strip.begin();
      for (int i = 0; i < number; i++)
        strip.send(CRGBtoData(ColorFromPalette(palette, (i*2), beat-0+(i*3))));
    strip.end();
    effTimer = millis();
  }
    // uint8_t beat = beatsin8(10, 65, 255);
    //Serial.print("beat: "); Serial.println(beat);
}


void fadeToWs(byte WSend_R, byte WSend_G, byte WSend_B) {
  int deltaR = WSend_R - WSstart_R;
  int deltaG = WSend_G - WSstart_G;
  int deltaB = WSend_B - WSstart_B;
  //  Serial.print("deltaR: "); Serial.println(deltaR);
  //  Serial.print("deltaG: "); Serial.println(deltaG);
  //  Serial.print("deltaB: "); Serial.println(deltaB);

  int deltaMax = 0;
  if (abs(deltaR) > deltaMax) deltaMax = abs(deltaR);
  if (abs(deltaG) > deltaMax) deltaMax = abs(deltaG);
  if (abs(deltaB) > deltaMax) deltaMax = abs(deltaB);
  //  Serial.print("deltaMax: "); Serial.println(deltaMax);

  float stepR = (float)deltaR / deltaMax;
  float stepG = (float)deltaG / deltaMax;
  float stepB = (float)deltaB / deltaMax;
  //  Serial.print("stepR: "); Serial.println(stepR);
  //  Serial.print("stepG: "); Serial.println(stepG);
  //  Serial.print("stepB: "); Serial.println(stepB);

  if (deltaMax == 0) {
    return;
    //Serial.print("Делить на 0 нельзя!");
  }

  uint32_t stepDelay = (float)1000 * 50 / deltaMax;
  //Serial.print("stepDelay: "); Serial.println(stepDelay);

  float thisR = WSstart_R, thisG = WSstart_G, thisB = WSstart_B;

  for (int i = 0; i < deltaMax; i++) {
    thisR += stepR;
    thisG += stepG;
    thisB += stepB;

    WSstart_R = thisR;
    WSstart_G = thisG;
    WSstart_B = thisB;

    strip.begin();
    for (int i = 0; i < number; i++) {
      strip.send(mRGB(WSstart_R, WSstart_G, WSstart_B)); // плавно перейти в новый колор
    }
    strip.end();

    uint32_t us_timer = micros();
    while (micros() - us_timer <= stepDelay);
  }

  //  Serial.print("thisR: "); Serial.println(thisR);
  //  Serial.print("thisG: "); Serial.println(thisG);
  //  Serial.print("thisB: "); Serial.println(thisB);

  //fadeToWs_Stop = true;
}




















//

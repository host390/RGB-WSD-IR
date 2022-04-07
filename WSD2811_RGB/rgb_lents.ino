

// Команды для RGB ленты


int setTimeFadeTo = 200;
int stepPerud;
int thisColor; // для эффектов
bool setParams = true;

void rgb_comands() {
  
  if (ButNumClick == 3) {
    ButNumClick = ButNumClick_last;
    if (Startap == false) return;
    Startap = false;
    for (int i = Brightness; i > 0; i--) {
      lents.setBrightness(i);
      delay(2);
    }
    lents.setBrightness(0);
  }

  if (ButNumClick == 4) {
    ButNumClick = ButNumClick_last;
    if (Startap == true) return;
    Startap = true;
    for (int i = 0; i < Brightness; i++) {
      lents.setBrightness(i);
      delay(2);
    }
  }

  if (Startap == false) return; // всё выключено

  if (ButNumClick == 1) {
    ButNumClick = ButNumClick_last;
    for (int i = 0; i < 64; i++) {
      Brightness++;
      if (Brightness > 255) {
        Brightness = 255;
        break;
      }
      lents.setBrightness(Brightness);
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
      lents.setBrightness(Brightness);
      delay(2);
    }
    // Serial.print("Brightness: "); Serial.println(Brightness);
  }

  if (ButNumClick == 5) {
      lents.fadeTo(255, 0, 0, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 6) {
      lents.fadeTo(0, 255, 0, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 7) {
      lents.fadeTo(0, 0, 255, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 8) {
      lents.fadeTo(255, 255, 255, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 9) { // COLOR_0
      lents.fadeTo(240, 90, 20, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 10) { // COLOR_1
      lents.fadeTo(40, 230, 20, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 11) { // COLOR_2
      lents.fadeTo(23, 108, 172, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 13) { // COLOR_3
      lents.fadeTo(220, 71, 47, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 14) { // COLOR_4
      lents.fadeTo(12, 153, 196, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 15) { // COLOR_5
      lents.fadeTo(76, 19, 60, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 17) { // COLOR_6
      lents.fadeTo(222, 95, 50, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 18) { // COLOR_7
      lents.fadeTo(4, 82, 144, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 19) { // COLOR_8
      lents.fadeTo(105, 6, 34, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 21) { // COLOR_9
      lents.fadeTo(219, 194, 16, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } else if (ButNumClick == 22) { // COLOR_10
      lents.fadeTo(238, 10, 51, setTimeFadeTo);
      ButNumClick_last = ButNumClick;
    } 
    
  if (ButNumClick == 12) { // Rainbow
    ButNumClick_last = ButNumClick;
    stepPerud = 60; // преьюд изменений
    rainbow_rgb();
  } else if (ButNumClick == 16) { // Fire
    ButNumClick_last = ButNumClick;
    stepPerud = 40;
    fire_rgb();
  } else if (ButNumClick == 20) { // Commet
    ButNumClick_last = ButNumClick;
    stepPerud = 18;
    commet_rgb();
  } else if (ButNumClick == 24) { // BPM
    ButNumClick_last = ButNumClick;
    stepPerud = 30;
    bpm_rgb();
  }
}


bool color_step_flag = true;
void bpm_rgb() {
  if (millis() - effTimer >= stepPerud) {
    uint8_t beat = beatsin8(10, 46, Brightness);
    Serial.print("beat: "); Serial.println(beat);
    lents.setBrightness(beat);
    if (beat > Brightness - 10) {
      color_step_flag = true;
    }
    if (beat < 49 and color_step_flag) {
      color_step_flag = false;
      Serial.println("ziro");
      thisColor += 100;
      if (thisColor > 1530) thisColor = 0;
      lents.colorWheel(thisColor);
    }
    effTimer = millis();
  }
}


int brig_step = 255;
void commet_rgb() {
  if (millis() - effTimer >= stepPerud) {
    lents.setBrightness(brig_step);
    brig_step -= 3;
    Serial.print("brig_step: "); Serial.println(brig_step);
    if (brig_step <= 0) {
      brig_step = Brightness;
      thisColor += 100;
      if (thisColor > 1530) thisColor = 0;
      lents.colorWheel(thisColor);
      lents.setBrightness(0);
      delay(60);
    }
    effTimer = millis();
  }
}


#define STEPCOLOR 6 // шаг цветов
void rainbow_rgb() {
  if (millis() - effTimer >= stepPerud) {
    effTimer = millis();
    thisColor += STEPCOLOR;
    if (thisColor > 1530) thisColor = 0;
    lents.colorWheel(thisColor);
  }
}


#define SMOOTH_K 0.25 // коэффициент сглаживания
#define TIME_CHANGE 200 // период изменения огня
#define MAX_BRIGHT 255 // макс яркость (жёлтый)
#define MIN_BRIGHT 30 // мин яркость (красный)
int val, rndVal;
uint32_t prevTime;
int noize = 0;
void fire_rgb() {
  if (millis() - effTimer >= stepPerud) {
    
    /* 1-ый вариант
    if (millis() - prevTime > TIME_CHANGE) {
      rndVal = random(0, 13) * 10;
      prevTime = millis();
    }
    val = val * (1 - SMOOTH_K) + rndVal * SMOOTH_K;
    lents.colorWheel(val);
    Serial.print("val: "); Serial.println(val);
    lents.setBrightness(map(val, 0, 120, MIN_BRIGHT, MAX_BRIGHT));
    */
    
    ///* 2-ый вариант
    int val = inoise8(noize);
    noize += 12;
    //Serial.print("val: "); Serial.println(map(val, 0, 255, 0, 120));
    lents.colorWheel(map(val, 0, 255, 0, 120));
    lents.setBrightness(map(val, 0, 255, MIN_BRIGHT, Brightness));
    Serial.print("val: "); Serial.println(map(val, 0, 255, MIN_BRIGHT, Brightness));
    effTimer = millis();
    //*/
    
  }
}






















//

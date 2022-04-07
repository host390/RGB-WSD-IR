
/*
   multi RGB WSD Contriller RGB лента + WSD2811
*/



// ОСНОВНЫЕ НАСТРОЙКИ
#define TYPELENTS 1 // 0 - RGB, 1 - WSD2811
#define TYPE_LENTS LED_WS2811
#define PIN_IP 2 // Куда подключен ИК приёмник


// Для WSD
#define ALL_NUMBER 100 // Количество светодиодов
#define STRIP_PIN 4 // ПИН ленты
 
// Для RGB
#define CHANNAL_R 3
#define CHANNAL_G 5
#define CHANNAL_B 6




// Кнопки пульта RGB
#define BRUGN_UP    0x6D3891A1
#define BRUGN_DOWN  0x6A23CCA1
#define OFF         0xE4CFA1
#define ON          0xFDD00AA1
#define BUT_R       0xA3161CA1
#define BUT_G       0xA00157A1
#define BUT_B       0x36C25AA1

#define BUT_W       0x83AD13A1 // 0x33AD95A1

#define COLOR_0     0xC17CEFA1
#define COLOR_1     0xBE682AA1
#define COLOR_2     0x55292DA1
#define COLOR_3     0xF75A7AA1
#define COLOR_4     0xF445B5A1
#define COLOR_5     0x8B06B8A1
#define COLOR_6     0x7E836CA1
#define COLOR_7     0x7B6EA7A1
#define COLOR_8     0x122FAAA1
#define COLOR_9     0xB460F7A1
#define COLOR_10    0xB14C32A1
#define EFFECT_0    0x521468A1
#define EFFECT_1    0x87F1F3A1
#define EFFECT_2    0xF1AE5A1
#define EFFECT_3    0x44F870A1

#define BUT_TYPES   0x480D35A1 // РОЗОВАЯ ДОЛЖНО БЫТЬ !!!


#include <IRLremote.h>
CHashIR IRLremote;


#include <GyverRGB.h>
GRGB lents(CHANNAL_R, CHANNAL_G, CHANNAL_B);  // куда подключены цвета (R, G, B)

#include <FastLEDsupport.h> // вкл поддержку FL
//#define NUM_LEDS 100 // >>>>>> ??????
#define FRAMES_PER_SECOND 60
uint8_t gHue = 0;
DEFINE_GRADIENT_PALETTE(heatmap_gp) {   // делаем палитру огня
  0,     0,  0,  0,     // black
  128,   255,  0,  0,   // red
  224,   255, 255,  0,  // bright yellow
  255,   255, 255, 255  // full white
};
CRGBPalette16 fire_p = heatmap_gp;
//CRGB leds[NUM_LEDS];


#define CRT_PGM // ???
#define COLOR_DEBTH 3 // байт на цвет

#include <microLED.h> // version: 3.5
// microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2811, ORDER_GRB, CLI_HIGH, SAVE_MILLIS> strip; // с буфером
microLED<0, STRIP_PIN, MLED_NO_CLOCK, TYPE_LENTS, ORDER_GRB, CLI_HIGH, SAVE_MILLIS> strip; // без буфера

mData colorWSD = mRGB(255, 0, 0); // своя переменная нужна - mData

byte typeLents = TYPELENTS; // 0 - RGB, 1 - WSD2811 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte ButNumClick = 0; // Каждой кнопке дадим номер
byte ButNumClick_last = 0; // номер предыдущий
byte brigLevels = 2; // уровень яркости
uint32_t IRdata; // значение с IR пульта
bool Startap = true; // OFF ON
bool runningDots_true = false;
bool light_ON_Click = false;
bool light_OFF_Click = false;
bool color_Show; // флаг для смены режима
int number = ALL_NUMBER; // 300 WS2811 светодиодов количество чипов 25 макисмум
int Brightness = 128; // яркость


void setup() {
  Serial.begin(9600);
  IRLremote.begin(PIN_IP);

  pinMode(CHANNAL_R, OUTPUT);
  pinMode(CHANNAL_G, OUTPUT);
  pinMode(CHANNAL_B, OUTPUT);

  TCCR1B &= ~_BV(WGM12);
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
  TCCR2A |= _BV(WGM20);
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

  lents.setGammaBright(true); // вкл/выкл коррекции яркости

  if (typeLents == 0) {
    lents.setBrightness(Brightness);
    lents.setRGB(255, 0, 0);
  } else if (typeLents == 1) {
    lents.setBrightness(Brightness);
    int allNumb = 2000; // надо запомнить сколько всего
    strip.begin();
      for (int i = 0; i < allNumb; i++) {
        strip.send(mRGB(0, 0, 0));
      }
    strip.end();
    delay(100);
    strip.begin();
    // lents.setBrightness(250); // почему не даётся яркость в начале ???
      for (int i = 0; i < number; i++) {
        strip.send(colorWSD);
      }
    strip.end();

  }
  delay(1000);
}

byte WSstart_R = 255;
byte WSstart_G = 0;
byte WSstart_B = 0;
bool fadeToWs_Stop = false;
int arrJuggle[] {};
int g = 0;
int randommm;
byte dothue = 0;
byte brig = 63;


void loop() {

  /* Проверка кодов
  if (IRLremote.available()) {
    // Get the new data from the remote
    auto data = IRLremote.read();

    // Print the protocol data
    Serial.print(F("Address: 0x"));
    Serial.println(data.address, HEX);
    Serial.print(F("Command: 0x"));
    Serial.println(data.command, HEX);
  }
  return;
  */

  
  control();
  
  if (typeLents == 0) {
    rgb_comands();
  } else if (typeLents == 1) {
    wsd_comands();
  }
 
}




//void juggle() {
//  fadeToBlackBy(leds, NUM_LEDS, 65);
//  byte dothue = 0;
//  for (int i = 0; i < 15; i++) {
//    leds[beatsin16(i + 5, 0, NUM_LEDS - 1)] |= CHSV(dothue, 127, 255);
//    dothue += 127;
//  }
//  FastLED.show();
//  FastLED.delay(1000 / FRAMES_PER_SECOND);
//}

//void confetti() {
//  // random colored speckles that blink in and fade smoothly
//  fadeToBlackBy( leds, NUM_LEDS, 13);
//  int pos = random16(NUM_LEDS);
//  leds[pos] += CHSV( gHue + random8(NUM_LEDS), 175, 255);
//  FastLED.show();
//  FastLED.delay(1000 / FRAMES_PER_SECOND);
//}

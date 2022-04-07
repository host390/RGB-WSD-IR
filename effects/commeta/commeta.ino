

///* microLED поток

// бегущие частицы 1D, потоковая версия
#define STRIP_PIN 4 // пин ленты
//#define SOUND_PIN A0    // пин звука
#define COLOR_STEP 10 // шаг цвета, интересные 151, 129
#define PART_SP 1 // скорость движения частиц
#define LEDS_AM 10 // количество светодиодов
#define PART_AM 50 // макс. количество частиц
#define FADE_VAL 100 // скорость затухания


// микролед
#include <microLED.h>
microLED < 0, STRIP_PIN, -1, LED_WS2811, ORDER_GRB, CLI_AVER > strip;


// тинилед (чуть быстрее работает)
//#define TLED_PORT PORTD
//#define TLED_DDR DDRD
//#include "tinyLED.h"
//tinyLED<STRIP_PIN> strip;
//#include "VolAnalyzer.h"

//VolAnalyzer sound(SOUND_PIN);


void setup() {
  Serial.begin(9600);
  strip.setBrightness(255);  // для тинилед не нужно, яркость и так максимум


  strip.begin();
  for (int i = 0; i < 100; i++) {
    strip.send(mRGB(0, 0, 0));
  }
  strip.end();
  delay(1000);
  // определяем длину хвоста при текущих настройках
  //tailSize = 1;
  //byte color = 255;

  //  while (color > 0) { // пока яркость выше 0
  //    color = fade8(color, FADE_VAL); // гасим
  //    tailSize++; // хвост растёт
  //  }


  
  
}




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

void loop() {

  for (int i = 0; i < partsEx; i++) {
    partsPos[i] += 1;
  }
  if (partsEx > 0) {
    headCommet++;
  }
  //Serial.print("headCommet: "); Serial.println(headCommet);
  //Serial.print("partsPos[0]: "); Serial.println(partsPos[0]);

  if (partsPos[0] >= numbers) {
    for (int i = 0; i < partsEx - 1; i++) { // ???
      partsPos[i] = partsPos[i + 1];
      partsCol[i] = partsCol[i + 1];
      partsBrig[i] = partsBrig[i + 1];
    }
    partsEx--;
    //Serial.print("partsEx: "); Serial.println(partsEx);
  }

  if (headCommet > respavnPoint) {
    tailSize = random(6, 12);
    curBrig = 255;
    curColor += 34;
    brig_level = 255 / tailSize;
    respavnPoint = random(numbers/10, numbers/4);
    //Serial.print("respavnPoint: "); Serial.println(respavnPoint);
    //Serial.println("Новая Коммета");
    commetSize = 0;
  }
  
  //if (commHid == true) {
    if (partsEx < 100) { // partsEx < tailSize
      if (commetSize < tailSize) {
        if (commetSize == 0) { // если это начало новой комметы
          headCommet = 0;
        }
        commetSize++;
        //Serial.print("commetSize: "); Serial.println(commetSize);
        partsEx++;
        //Serial.print("partsEx: "); Serial.println(partsEx);
        partsPos[partsEx - 1] = 0;
        partsCol[partsEx - 1] = curColor;
        partsBrig[partsEx - 1] = curBrig;
        curBrig -= brig_level;
      }
      //partsEx++;
      //Serial.print("partsEx: "); Serial.println(partsEx);
      //partsPos[partsEx - 1] = 0; 
    }
  //}
      //partsCol[partsEx - 1] = curColor;
      //partsBrig[partsEx - 1] = curBrig;
      //curBrig -= brig_level;
    //} else {
      //commHid = false;
    //}
    
   //}

  lastPart = partsEx - 1; // младшая частица
  //Serial.print("lastPart: "); Serial.println(lastPart);
  
  strip.begin();
    for (int i = 0; i < numbers; i++) {
      if (lastPart >= 0 && i > partsPos[lastPart] - 1 and i <= partsPos[lastPart]) {
        // color = mWheel8(123, 140);
        
        color = mWheel8(partsCol[lastPart], partsBrig[lastPart]);
        if (i == partsPos[lastPart]) lastPart--;
        //strip.send(color);
      } else {
        color = mRGB(0, 0, 0); // иначе чёрный
        //strip.send(color);
      }
      for (int i = 0; i < 2; i++) {
        strip.send(color);
      }
      
      
    }
  strip.end();


  //Serial.println();
  delay(30);




  return;




  






  
  /*
  // color = getFade(color, 100);
  // color = mWheel8(100);
  static int brigLevel = 255 / 3;
  static int brig = 255;
  
  strip.begin();
    for (int i = 0; i < numbers; i++) {
      strip.send(color); 
    }
  strip.end();

  delay(1000);


  // brigLevel = 255 / 3;
  brig -= brigLevel;
  strip.setBrightness(brig);
  //color = getFade(color, 255 / 3);
  return;
  */
  
  // двигаем активные частицы //partsPos[0] = partsPos[0] + 1;
  for (int i = 0; i < partsEx; i++) {
    partsPos[i] += 1;
    // Serial.print("partsPos["); Serial.print(i); Serial.print("] = "); Serial.println(partsPos[i]);
  }

  // самая дальняя частица вышла за ленту
  if (partsPos[0] >= numbers) {
    // перематываем массив на ячейку влево
    for (int i = 0; i < tailSize - 1; i++) {
      partsPos[i] = partsPos[i + 1];
      //Serial.print("partsPos["); Serial.print(i); Serial.print("] = "); Serial.println(partsPos[i]);
      // partsCol[i] = partsCol[i + 1];
    }
    partsEx--; // уменьшаем количество активных частиц
    // Serial.print("Всего частиц: "); Serial.println(partsEx);
    if (partsEx == 0) {
      commHid = true;
      curBrig = 255;
      curColor += 60;
      brig_level = 255 / tailSize;
      // Serial.print("brig_level: "); Serial.println(brig_level);
    }
  }
  
  if (commHid == true) {
    if (partsEx < tailSize) { // есть место в буфере // partsEx < tailSize 
      partsEx++; // добавляем частицу
      // Serial.print("Всего частиц: "); Serial.println(partsEx);
      partsPos[partsEx - 1] = 0; // её позиция
      partsCol[partsEx - 1] = curColor; // цвет
      partsBrig[partsEx - 1] = curBrig; // и яркость
      curBrig -= brig_level; // уменьшаем яркость
    } else {
      commHid = false;
    }
  }

  lastPart = partsEx - 1; // младшая частица
  //Serial.print("lastPart: "); Serial.println(lastPart);

  ///*
  strip.begin();

    for (int i = 0; i < numbers; i++) {
      
      // хвост текущей активной частицы попадает на текущий светодиод
      if (i > partsPos[lastPart] - 1 and i <= partsPos[lastPart]) {
        
        color = mWheel8(partsCol[lastPart], partsBrig[lastPart]); // color = mRGB(255, 0, 0);
        
        // позиция i совпала со светодиодом - переходим к следующей
        if (i == partsPos[lastPart]) lastPart--;
      } else color = mRGB(0, 0, 0);   // иначе чёрный
      strip.send(color);
    }

  strip.end();
  //*/
  
  //Serial.println();
  delay(40);
  
//  while (1) {
//    sensor = digitalRead(7);
//    if (sensor == HIGH and sensor_last == LOW) {
//      //Serial.println("Click");
//      delay(300);
//      break;
//    }
//    sensor_last = sensor;
//  }



  //Serial.println(digitalRead(7));
  //delay(100);
  //delay(3000);



  /*

    if (partsEx + 1 <= 2) { // есть место в буфере
    partsEx++; // добавляем частицу
    Serial.print("Всего частиц: "); Serial.println(partsEx);
    partsPos[partsEx - 1] = 0; // её позиция
    }



    if (partsPos[0] > 9) {
    partsPos[0] = 0;
    Serial.println();
    }

    //Serial.print("Позиция светодиода: "); Serial.println(partsPos[0]);
    lastPart = partsEx - 1; // младшая частица
    Serial.print("lastPart: "); Serial.println(lastPart);
    strip.begin();
    for (int i = 0; i < numbers; i++) {
      if (i > partsPos[lastPart] - 2 && i <= partsPos[lastPart]) {  // lastPart >= 0  i > partsPos[lastPart] - tailSize
          color = mRGB(255, 0, 0);
      } else {
        color = mRGB(0, 0, 255);
      }
      strip.send(color);
    }
    strip.end();



    delay(1000);
    //delay(10000);
    //delay(10000);
    //delay(10000);

  */


}



void function() {

  //if (sound.tick()) { // если анализ звука завершён (~10мс)

  // двигаем активные частицы
  for (int i = 0; i < partsEx; i++) partsPos[i] += PART_SP;

  // самая дальняя частица вышла за ленту
  if (partsPos[0] >= LEDS_AM) {
    // перематываем массив на ячейку влево
    for (int i = 0; i < PART_AM - 1; i++) {
      partsPos[i] = partsPos[i + 1];
      partsCol[i] = partsCol[i + 1];
    }
    partsEx--;    // уменьшаем количество активных частиц
  }

  //if (sound.pulse()) {              // зарегистрирован скачок
  if (partsEx + 1 <= PART_AM) {   // есть место в буфере
    partsEx++;                    // добавляем частицу
    partsPos[partsEx - 1] = 0;    // её позиция
    partsCol[partsEx - 1] = curColor; // и цвет
    // curColor += COLOR_STEP;       // мотаем цвет
  }
  //}

  // начинаем потоковую отправку
  strip.begin();
  mData color = 0;  // тут храним цвет
  int lastPart = partsEx - 1; // младшая частица
  // проходимся по всем светодиодам
  for (int i = 0; i < LEDS_AM; i++) {
    // хвост текущей активной частицы попадает на текущий светодиод
    if (lastPart >= 0 && i > partsPos[lastPart] - tailSize && i <= partsPos[lastPart]) {
      // личный цвет частицы
      color = mWheel8(partsCol[lastPart]);
      // гасим в разницу в позиции раз
      for (int k = 0; k < partsPos[lastPart] - i; k++) color = getFade(color, FADE_VAL);
      // позиция частицы совпала со светодиодом - переходим к следующей
      if (i == partsPos[lastPart]) lastPart--;
    } else color = 0;   // иначе чёрный
    // включаем светодиод
    if (i < LEDS_AM) strip.send(color);
  }
  strip.end();



  //}
}















/* Микро лед рандомные огоньки
  // #include <FastLED.h>
  // бегущие частицы 1D, версия с MicroLED
  #define STRIP_PIN 4     // пин ленты
  //#define SOUND_PIN A0    // пин звука
  //#define COLOR_STEP 151  // шаг цвета, интересные 151, 129
  #define LEDS_AM 60 // количество светодиодов
  #define P_SPEED 2 // скорость движения

  #define COLOR_DEBTH 3
  #include <microLED.h>
  microLED <LEDS_AM, STRIP_PIN, -1, LED_WS2812, ORDER_GRB, CLI_AVER> strip;

  //#include "VolAnalyzer.h"
  //VolAnalyzer sound(SOUND_PIN);

  byte curColor = 0; // текущий цвет

  byte sizeCommet = 6; // длина комметы
  byte BrignesCommStep; // Шаг яркости
  int BrigbComm = 255; // Яркость комметы

  int numStep = 0; // Сколько прошла коммета

  byte respavn;

  void setup() {
  strip.setBrightness(255);
  Serial.begin(9600);
  // настройки анализатора звука
  //sound.setVolK(15);        // снизим фильтрацию громкости (макс. 31)
  //sound.setVolMax(255);     // выход громкости 0-255
  //sound.setPulseMax(200);   // сигнал пульса
  //sound.setPulseMin(150);   // перезагрузка пульса
  BrignesCommStep = 255 / sizeCommet;
  Serial.print("Шаг яркости: "); Serial.println(BrignesCommStep);

  respavn = random(0, LEDS_AM);
  }

  int val;
  int val_last;
  int max_val;
  int caunter = 0;


  void loop() {

  //  val = inoise8(caunter);
  //  if (val < val_last) {
  //    max_val = val_last;
  //    Serial.print("Точка максимума: "); Serial.println(max_val);
  //  }
  //  if (val > val_last)
  //  val_last = val;
  //  caunter += 7;
  //  Serial.println(val);
  //  delay(100);

  //  max_val = random(130, 255);
  //  Serial.print("Точка максимума: "); Serial.println(max_val);
  //  delay(100);
  //  return;


  //if (sound.tick()) {   // если анализ звука завершён (~10мс)
    // перематываем массив светодиодов на P_SPEED вправо

    for (int k = 0; k < P_SPEED; k++) {
      numStep++;
      for (int i = LEDS_AM - 1; i > 0; i--) {
        strip.leds[i] = strip.leds[i - 1];
      }
    }

    if (numStep > sizeCommet + respavn) { // если дошло до конца
      Serial.print("numStep: "); Serial.println(numStep);
      numStep = 0;
      curColor += 46;
      sizeCommet = random(6, 12);
      Serial.print("sizeCommet: "); Serial.println(sizeCommet);
      BrigbComm = random(130, 255);
      Serial.print("BrigbComm: "); Serial.println(BrigbComm);
      BrignesCommStep = BrigbComm / sizeCommet;
      Serial.print("Шаг яркости: "); Serial.println(BrignesCommStep);
      respavn = random(0, LEDS_AM);
      Serial.print("respavn: "); Serial.println(respavn);
    }

    //val = inoise8(caunter); // находим точку максимума
    //caunter += 15;
    //Serial.println(val);
    // резкий звук - меняем цвет
    //if (sound.pulse()) curColor += COLOR_STEP;


    // берём текущий цвет с яркостью по громкости (0-255)
    //Serial.print("яркость: "); Serial.println(BrigbComm);
    mData color = mWheel8(curColor, BrigbComm);
    BrigbComm -= BrignesCommStep;
    if (BrigbComm < 0) BrigbComm = 0;

    // красим P_SPEED первых светодиодов
    for (int i = 0; i < P_SPEED; i++) {
      strip.set(i, color);
    }

    // выводим
    strip.show();

    delay(30);
  //}
  }

*/





/* FastLED огоньки друг за другом
  // бегущие частицы 1D, версия с FastLED
  #define STRIP_PIN 4 // пин ленты
  // #define SOUND_PIN A0 // пин звука

  #define COLOR_STEP 151 // шаг цвета, интересные 151, 129
  #define P_SPEED 1 // скорость движения
  #define LEDS_AM 60 // количество светодиодов

  #include <FastLED.h>
  CRGB leds[LEDS_AM];

  //#include "VolAnalyzer.h"
  //VolAnalyzer sound(SOUND_PIN);

  byte curColor = 0; // текущий цвет

  void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, STRIP_PIN, GRB>(leds, LEDS_AM);
  FastLED.setBrightness(255);

  // настройки анализатора звука
  //sound.setVolK(15);        // снизим фильтрацию громкости (макс. 31)
  //sound.setVolMax(255);     // выход громкости 0-255
  //sound.setPulseMax(200);   // сигнал пульса
  //sound.setPulseMin(150);   // перезагрузка пульса
  }

  int brig = 255;
  byte colorRand = 123;
  int numPush = 0;
  // CRGB color = CHSV(random(0, 256), 255, brig);


  void loop() {
  //if (sound.tick()) { // если анализ звука завершён (~10мс)

    for (int k = 0; k < P_SPEED; k++) { // перематываем массив светодиодов на P_SPEED вправо
      numPush++;
      // Serial.println(numPush);
      for (int i = LEDS_AM - 1; i > 0; i--) {
        leds[i] = leds[i - 1];
        //Serial.print("leds["); Serial.print(i); Serial.print("] = "); Serial.println(i - 1);
        //delay(1000);
      }
    }

    // резкий звук - меняем цвет
    // if (sound.pulse()) curColor += COLOR_STEP;
    if (numPush > 40) {
      numPush = 0;
      brig = 255;
      colorRand = random(0, 256);
    }
    CRGB color = CHSV(colorRand, 255, brig);
    // берём текущий цвет с яркостью по громкости (0-255)
    brig = brig - 30;
    if (brig < 0) brig = 0;
    // Serial.println(brig);
    // красим P_SPEED первых светодиодов
    for (int i = 0; i < P_SPEED; i++) {
      //Serial.print("leds["); Serial.print(i); Serial.print("] = "); Serial.println("RED");
      leds[i] = color;
    }


    // выводим
    FastLED.show();
    delay(10);

  // }
  }
*/

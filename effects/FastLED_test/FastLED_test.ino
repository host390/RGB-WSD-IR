
#define pinIR 2
#include <IRLremote.h>
CHashIR IRLremote;

// Кнопки пульта RGB
#define BRUGN_UP    0x6D3891A1
#define BRUGN_DOWN  0x6A23CCA1
#define OFF         0xE4CFA1
#define ON          0xFDD00AA1
#define BUT_R       0xA3161CA1
#define BUT_G       0xA00157A1
#define BUT_B       0x36C25AA1
#define BUT_W       0x33AD95A1
#define COLOR_0     0xC17CEFA1
#define COLOR_1     0xBE682AA1
#define COLOR_2     0x55292DA1
#define EFFECT_0    0x521468A1



#include <FastLED.h>
#define LED_PIN 4
#define COLOR_ORDER GRB
#define CHIPSET WS2811
#define NUM_LEDS 100
#define BRIGHTNESS 140
#define FRAMES_PER_SECOND 60

bool gReverseDirection = false;
uint8_t gHue = 0;
CRGBPalette16 gPal; // ???
CRGB leds[NUM_LEDS];

uint32_t IRdata; // значение с IR пульта

void setup() {
  Serial.begin(9600);
  IRLremote.begin(pinIR);

  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.clear();
  FastLED.show();
  delay(100);
  //FastLED.showColor(CRGB::Red);
  //FastLED.show();
  //delay(1000);
//  for(int i = 0; i < NUM_LEDS; i++) {
//    leds[i].setRGB(255, 68, 221);
//  }
//  FastLED.show();
  gPal = HeatColors_p;
}

uint8_t regim;
long timerRGB;


byte dothue = 0;
void loop() {

  //fadeToBlackBy(leds, NUM_LEDS, 65);
  //dothue = 0;
  //for(int i = 0; i < 15; i++) {
    // Serial.print(beatsin16(i+5, 0, NUM_LEDS-1)); Serial.print(',');
    //leds[beatsin16(i + 5, 0, NUM_LEDS-1)] |= CHSV(dothue, 127, 255);
    //Serial.print("dothue: "); Serial.println(dothue);
    //dothue += 127;
  //}
  //Serial.println();
  //FastLED.show();
  //delay(1000);
//  FastLED.showColor(CRGB::Red);

  //leds[2] |= CHSV(20, 127, 255);

//  FastLED.show();
//  delay(2000);
//  FastLED.delay(1000 / FRAMES_PER_SECOND);



  /*
  // Serial.println("Смотрю");
  if (IRLremote.available()) {
    auto data = IRLremote.read();
    IRdata = data.command;
    //Serial.print(F("Address: 0x")); Serial.println(data.address, HEX);
    //Serial.print(F("Command: 0x")); Serial.println(data.command, HEX);
    switch(IRdata) {
      case OFF:
        Serial.println("OFF");
        break;
      case ON:
        Serial.println("ON");
        break;
      case BUT_R:
        Serial.println("BUT_R");
        break;
      case BUT_G:
        Serial.println("BUT_G");
        break;
      case BUT_B:
        Serial.println("BUT_B");
        break;
    }
  }

  if (millis() - timerRGB >= 6000) {
      timerRGB = millis();
      // regim = random(0, 10);
      regim++;
      if (regim > 9) regim = 0;
      Serial.print("Режим: "); Serial.println(regim);
  }
  
  regim = 3;
   
  switch (regim) {
    case 0:
      confetti();
      break;
    case 1:
      sinelon();
      break;
    case 2:
      bpm();
      break;
    case 3:
      juggle();
      break;
    case 4:
      rainbow_march();
      break;
    case 5:
      Fire();
      break;
    case 6:
      pride();
      break;
    case 7:
      fill_grad();
      break;
    case 8:
      Fire2012WithPalette(); 
      break;
    case 9:
      Staloktit(); 
      break;
    case 10:
      // Flamish(); 
      break;
  }
*/

//  uint8_t BeatsPerMinute = 10;
//  CRGBPalette16 palette = PartyColors_p;
//  uint8_t beat = beatsin8( BeatsPerMinute, 65, 255);
//  for(int i = 0; i < NUM_LEDS; i++) { 
//    // leds[i] = ColorFromPalette(palette, (i*2), beat-0+(i*3));
//    Serial.print("i*2: "); Serial.println(i*2);
//    Serial.print("beat-0+(i*3): "); Serial.println(beat-0+(i*3));
//    delay(1000);
//  }
//  delay(100000);

  sinelon();
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  
}

void sinelon() {
  // fadeToBlackBy(leds, NUM_LEDS, 13);
  int pos = beatsin16(3, 0, NUM_LEDS-1);
  leds[pos] = CHSV(127, 255, 127);
}

void bpm() {
  uint8_t BeatsPerMinute = 10;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 65, 255);
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = ColorFromPalette(palette, (i*2), beat-0+(i*3));
  }
}

void test() {
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}

void confetti() {
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, NUM_LEDS, 13);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(NUM_LEDS), 175, 255);
}

void juggle() {
  fadeToBlackBy(leds, NUM_LEDS, 65);
  byte dothue = 0;
  for(int i = 0; i < 15; i++) {
    leds[beatsin16(i+5, 0, NUM_LEDS-1)] |= CHSV(dothue, 127, 255);
    dothue += 127;
  }
}


uint8_t thishue = 0;                                          
int8_t thisrot = 1;                                           
uint8_t deltahue = 1;                                         
bool thisdir = 0; 

void rainbow_march() {                                            
  uint8_t secondHand = (millis() / 1000) % 60;               
  static uint8_t lastSecond = 99;                                    
  
  if (thisdir == 0) thishue += thisrot; else thishue-= thisrot;  
  fill_rainbow(leds, NUM_LEDS, thishue, deltahue);                                       

  if (lastSecond != secondHand) {                            
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: thisrot=1; deltahue=5; break;
      case  5: thisdir=-1; deltahue=10; break;
      case 10: thisrot=5; break;
      case 15: thisrot=5; thisdir=-1; deltahue=20; break;
      case 20: deltahue=30; break;
      case 25: deltahue=2; thisrot=5; break;
      case 30: break;
    }
  }
} 


#define COOLING  60
#define SPARKING 120
void Fire() {
  static byte heat[NUM_LEDS];

  for( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }
  
  if( random8() < SPARKING ) {
    int y = random8(32);
    heat[y] = qadd8( heat[y], random8(160,255) );
  }

  for( int j = 0; j < NUM_LEDS; j++) {
    byte colorindex = scale8(heat[j], 240);
    CRGB color = ColorFromPalette(gPal, colorindex);
    int pixelnumber;
    if (gReverseDirection) {
      pixelnumber = j;
    } else {
      pixelnumber = (NUM_LEDS-1) - j;
    }
    leds[pixelnumber] = color;
  }
}

void pride() {
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}

void fill_grad() {
  uint8_t starthue = beatsin8(5, 0, 255);
  uint8_t endhue = beatsin8(7, 0, 255);
  
  if (starthue < endhue) {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);    // If we don't have this, the colour fill will flip around. 
  } else {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
  }
}

void Fire2012WithPalette() {
  static byte heat[NUM_LEDS];

    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    for( int j = 0; j < NUM_LEDS; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = j;
      } else {
        pixelnumber = (NUM_LEDS-1) - j;
      }
      leds[pixelnumber] = color;
    }
}

int idex = 0;

void Staloktit() {                       
  static int pos = 0;
  idex = idex + 1;
  if (idex == (NUM_LEDS - pos)) 
  {
    pos++;
    idex = 0;
  }
  if (pos == NUM_LEDS)
  {
    pos = 0;
    delay(1000);
  } 
  for (int i = 0; i < (NUM_LEDS - pos); i++ ) {
    if (i == idex) {
      leds[i] = CHSV(random (65) + 95, random (200), 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  delay(10);
}


/* //------------------------Flamish-----------------------------

int TOP_INDEX = int(NUM_LEDS / 2);
int BOTTOM_INDEX = 0;
int EVENODD = NUM_LEDS % 2;

int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN = ( i + TOP_INDEX ) % NUM_LEDS;
  }
  return iN;
}

int horizontal_index(int i) {
  //-ONLY WORKS WITH INDEX < TOPINDEX
  if (i == BOTTOM_INDEX) {
    return BOTTOM_INDEX;
  }
  if (i == TOP_INDEX && EVENODD == 1) {
    return TOP_INDEX + 1;
  }
  if (i == TOP_INDEX && EVENODD == 0) {
    return TOP_INDEX;
  }
  return NUM_LEDS - i;
}

void Flamish() {                        
int idelay = random(0, 25);//
  float hmin = 0.1; float hmax = 45.0;//
  float hdif = hmax - hmin;
  int randtemp = random(0, 5);//
  float hinc = (hdif / float(TOP_INDEX)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= TOP_INDEX; i++ ) {
    ihue = ihue + hinc;
    leds[i] = CHSV(255, 255, 255);
    int ih = horizontal_index(i);
    leds[ih] = CHSV(255, 255, 255);
    leds[TOP_INDEX].r = 255; leds[TOP_INDEX].g = 255; leds[TOP_INDEX].b = 255;
    LEDS.show();
    delay(idelay);
  }
}
*/




















//

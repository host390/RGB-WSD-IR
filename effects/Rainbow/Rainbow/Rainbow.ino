

#include <FastLED.h> // V3.3.3
#include "sav_button.h"
#include <Encoder.h>
//-------------------------------

#define LED_PIN 4
#define NUM_LEDS 30
#define BRIGHTNESS 200
#define FRAMES_PER_SECOND 60

//--------------------------------
SButton button1(4,50,2000,4000,1000);
Encoder myEnc(2, 3);

CRGB leds[NUM_LEDS]; // Define the array of leds (Определить массив светодиодов)

CRGBPalette16 gPal;

//----------------------------------------------------------------------------------
int TOP_INDEX = int(NUM_LEDS / 2);
int BOTTOM_INDEX = 0;
int EVENODD = NUM_LEDS % 2;
int idex = 0;
bool gReverseDirection = false;
uint8_t gHue = 0;



void setup() {
  delay(3000); // sanity delay
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  
  gPal = HeatColors_p;
  button1.begin();
}
//-----------------------------------------------------------------------------------------------
uint8_t regim = 2;

void lenta_run() {
  // random16_add_entropy(random());
  switch (regim) {
    case 0:
      one_color_all(0, 0, 0); 
      LEDS.show();
      break;
    case 1:
      fill_grad();
      break;
    case 2:
      confetti();
      break;
    case 3:
      sinelon();
      break;
    case 4:
      pride();
      break;
    case 5:
      bpm();
      break;
    case 6:
      juggle();
      break;
    case 7:
      rainbow_march();
      break;
    case 8:
      Fire2012WithPalette(); 
      break;
  }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


void user_input() {
  switch(button1.Loop()) {
    case SB_CLICK:
       regim++;
       if (regim > 8)
        regim = 0;
       break;
  }

  static long oldPosition = 0;
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;

    if (newPosition > 255) newPosition = 255;
    else if (newPosition < 0) newPosition = 0;
    myEnc.write(newPosition);
    
    Serial.println(newPosition);
    FastLED.setBrightness( newPosition );
  }
}

void loop() {
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);

  // lenta_run();
  // user_input();
}

//------------------------------------------------------------
void one_color_all(int cred, int cgrn, int cblu) {       //Погасить светодиоды
  for (int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}
//------------------------------------------------------------                                       
uint8_t thishue = 0;                                          
int8_t thisrot = 1;                                           
uint8_t deltahue = 1;                                         
bool thisdir = 0; 

//-----------------------------------------------------------
void rainbow_march() {                                            
  
  uint8_t secondHand = (millis() / 1000) % 60;               
  static uint8_t lastSecond = 99;
   {                                       
  
  if (thisdir == 0) thishue += thisrot; else thishue-= thisrot;  
  fill_rainbow(leds, NUM_LEDS, thishue, deltahue);            
  
}                            

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

//-----------------------------------------------------------


void confetti() {
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 13);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(NUM_LEDS), 175, 255);
}


//------------------------------------------------------------



void sinelon() {
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 13);
  int pos = beatsin16( 3, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( 127, 255, 127);
}



//--------------------------------------------
void bpm() {
  uint8_t BeatsPerMinute = 10;
 CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 65, 255);
  for( int i = 0; i < NUM_LEDS; i++)
  { 
  leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*3));
  }
}
//-----------------------------------------------------------------
void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 65);
  byte dothue = 0;
  for( int i = 0; i < 15; i++) 
  {
    leds[beatsin16( i+5, 0, NUM_LEDS-1 )] |= CHSV(dothue, 127, 255);
    dothue += 127;
  }
}
//----------------------------------------------------------------

#define COOLING  60
#define SPARKING 120

void Fire()
{

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

    for( int j = 0; j < NUM_LEDS; j++) 
    {
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
//---------------------------------------------------------------------

void pride() 
{
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
















//-----------------------------------------------------------------------
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


//-------------------------------------------------------------------------
void Staloktit()
{                       
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


//------------------------Flamish-----------------------------
int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN = ( i + TOP_INDEX ) % NUM_LEDS;
  }
  return iN;
}


//-----------------------------------
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
//---------------------------------------



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


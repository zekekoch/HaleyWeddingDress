//#include <FastSPI_LED.h>
#include "FastSPI_LED2.h"
#include "Animation.h"

#define NUM_LEDS 422
#define PIN 11
Animation::CRGB leds[NUM_LEDS];
Animation anims[5] = Animation(leds, NUM_LEDS);

LPD8806Controller<11, 13, 10> LED;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int lastInputLed = 0;

// array of animations 
byte animationCount = 5;

Animation animation1(leds, NUM_LEDS);
Animation animation2(leds, NUM_LEDS);
Animation animation3(leds, NUM_LEDS);
Animation animation4(leds, NUM_LEDS);
Animation animation5(leds, NUM_LEDS);

// top v - center 35, front left 50-70, front right 0-20
// bottom v - center 70, left 137-165, right 70-99
// top ring - front center 222, front left 199-222, front right 222-245
// middle ring - front center 307, front left 281-307, front right 307-331
// bottom ring - front center 396, front left 369-396, front right 396-421

void setup()
{
	Serial.begin(9600);
	LED.init();
		
	pinMode(A0, INPUT);
    anims[0] = animation1;
    anims[1] = animation2;
    anims[2] = animation3;
    anims[3] = animation4;
    anims[4] = animation5;
    
    
  	anims[0].fade(0,20,255);
  	anims[1].fade(369,421,255);
  	anims[2].fade(50,70,255);
  	anims[3].chase(0,19,255);
  	anims[4].chase(69,50,255);
    
}

void loop()
{
    Serial.println("Hello World");
    Serial.println(sizeof(leds));

	int delayTime = 50;
    anims[0].clear();
    for(int i = 0;i<animationCount;i++)
        anims[i].play();
    
/*	for(int i = 0;i<=20;i++)
	{
		leds[i].r = 0;
		leds[i].g = 0;
		leds[i].b = 255;
	}
*/
	
	LED.showRGB((byte*)leds, NUM_LEDS);
	
	delay(delayTime);
}

/*
void looped() {  
  if (Serial.available())
  {
    lastInputLed = getLedFromSerial();
  }

  int delayTime = 75;
  // upper v  
  clearLeds();
  race(0, 255, 50,70);
  race(0, 255, 0, 20);
  FastSPI_LED.show();
  delay(delayTime);

  clearLeds();
  //lower v
  setRange(0, 128, 137,167);
  setRange(0, 128, 70, 99);
  FastSPI_LED.show();

  delay(delayTime);
  clearLeds();
  FastSPI_LED.show();
  delay(delayTime);

  //bottom ring
  setRange(0, 255, 369,396);
  setRange(0, 255, 396, 421);
  FastSPI_LED.show();
  delay(delayTime);

  clearLeds();
  //middle ring
  setRange(0, 255, 281,307);
  setRange(0, 255, 307, 331);
  FastSPI_LED.show();
  delay(delayTime);

  clearLeds();
  //upper ring
  setRange(0, 255, 199,222);
  setRange(0, 128, 222, 245);
  FastSPI_LED.show();
  delay(delayTime);

//  leds[lastInputLed].r = 255;
//  leds[lastInputLed].g = 0;
//  leds[lastInputLed].b = 0;
  
  FastSPI_LED.show();
}

void playFrame()
{
  // check time
  // clear leds
  clearLeds();
  // loop over the list of animations
  for (int i = 0;i<animationCount;i++)
  {
	//    animations[i]
  }
  // show the leds
  // delay until the next frame
}



int getLedFromSerial() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int iLed = Serial.parseInt(); 
    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      iLed = constrain(iLed, 0, NUM_LEDS);
      Serial.print("led ");
      Serial.println(iLed);
      
      return iLed;
    }
  }
}

void colorFromAccelerormeter()
{
  byte x = analogRead(A0);

  clearLeds();
  for (int i = 0;i < NUM_LEDS;i++)
  {
    if (x > 128)
      leds[i].r = x;
    else
      leds[i].b = x;
  }
}

void race(byte color, byte intensity, int first, int last)
{
  for(int i = first;i< last;i++)
  {
    leds[i].r = intensity;
  } 
}

void setRange(byte color, byte intensity, int first, int last)
{
  for (int i = first; i < last;i++) 
  {
    switch(color)
    {
      case 0:
        leds[i].r = intensity;
        break;
      case 1:
        leds[i].g = intensity;
        break;
      case 2:
        leds[i].b = intensity;
        break;
    }
  }    
       
}


void progress() {
  for (int frame = 0;frame < NUM_LEDS;frame++)
  {
    clearLeds();
    for(int i = frame; i < NUM_LEDS; i++ ) 
    {
      leds[i].r = 255;
      leds[i].g = 0;
      leds[i].b = 0;
    }      
    FastSPI_LED.show();
    delay(5);  
  }
}
*/
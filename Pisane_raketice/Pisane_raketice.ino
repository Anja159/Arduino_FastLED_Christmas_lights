const int duration = 2000; //number of loops to run each animation for

#define NUMBEROFPIXELS 300 //Number of LEDs on the strip
#define PIXELPIN 7 //Pin where WS281X pixels are connected


#include "Arduino.h"
#include <FastLED.h>
#include <FastLEDPainter.h>

CRGB leds[NUMBEROFPIXELS];

//create one canvas and one brush with global scope
FastLEDPainterCanvas pixelcanvas = FastLEDPainterCanvas(NUMBEROFPIXELS); //create canvas, linked to the FastLED library (canvas must be created before the brush)
FastLEDPainterBrush pixelbrush = FastLEDPainterBrush(&pixelcanvas); //crete brush, linked to the canvas to paint to


void setup() {
  randomSeed(analogRead(0)); //new random seed

  //initilize FastLED library
  FastLED.addLeds<WS2812, PIXELPIN, GRB>(leds, NUMBEROFPIXELS);

  Serial.begin(115200);
  Serial.println(" ");
  Serial.println(F("FastLED Painter Demo Animations"));

  //check if ram allocation of brushes and canvases was successful (painting will not work if unsuccessful, program should still run though)
  //this check is optional but helps to check if something does not work, especially on low ram chips like the Arduino Uno
  if (pixelcanvas.isvalid() == false) Serial.println("canvas allocation problem");
  else  Serial.println("canvas allocation ok");


  if (pixelbrush.isvalid() == false) Serial.println("brush allocation problem");
  else  Serial.println("brush allocation ok");

}

unsigned long loopcounter; //count the loops, switch to next animation after a while
bool initialized = false; //initialize the canvas & brushes in each loop when zero

void loop() {

  //main program loops through different animations, allocating addidional canvas and brushes if needed

  //---------------------
  //RAINBOW PAINT (aka nyan cat)
  //---------------------

  //the brush moves along the strip, leaving a colorful rainbow trail
  for (loopcounter = 0; loopcounter < duration; loopcounter++)
  {
    static unsigned int hue = 0; //color hue to set to brush
    CHSV brushcolor; //HSV color definition


    if (initialized == false) //initialize the brushes
    {
      initialized = true;
      pixelbrush.setSpeed(8000); //brush moving speed
      pixelbrush.setFadeSpeed(450);
      pixelbrush.setFadein(false); //brightness will fade-in if set to true
      pixelbrush.setFadeout(true);
      pixelbrush.setBounce(false);
    }

    hue++;
    brushcolor.h = hue / 3; //divide by 3 to slow down color fading
    brushcolor.s = 255; //full saturation
    brushcolor.v = 255; //full brightness

    pixelbrush.setColor(brushcolor); //set new color to the bursh

    FastLED.clear();

    pixelbrush.paint(); //paint the brush to the canvas (and update the brush, i.e. move it a little)
    pixelcanvas.transfer(); //transfer (add) the canvas to the LEDs

    FastLED.show();
  }


  initialized = false; //reset the variable before moving to the next loop






  initialized = false; //reset the variable before moving to the next loop

}//end of loop()

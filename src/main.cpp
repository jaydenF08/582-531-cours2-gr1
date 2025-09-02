
#include <FastLED.h>
CRGB monPixel;

#include <Arduino.h>
#define MA_BROCHE_ANGLE 32

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<WS2812, 27, GRB>(&monPixel, 1);
  monPixel = CRGB(255, 188, 022);
  monPixel = CRGB(0, 0, 0);
  FastLED.show();
}

void loop()
{
  int maLectureAnalogique;
  maLectureAnalogique = analogRead(MA_BROCHE_ANGLE);
  Serial.print(maLectureAnalogique);
  Serial.println();
  delay(100);

  /*if (maLectureAnalogique < 2000)
  {
    monPixel = CRGB(0, 0, 0);
    FastLED.show();
  }

  else if (maLectureAnalogique > 2000)
  {
    monPixel = CRGB(255, 188, 022);
    FastLED.show();
  }*/
}

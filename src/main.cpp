
#include <FastLED.h>
CRGB monPixel;

#include <Arduino.h>
#define MA_BROCHE_ANGLE 32

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<WS2812, 27, GRB>(&monPixel, 1);
  monPixel = CRGB(255, 0, 0);
  FastLED.show();
}

void loop()
{
  int maLectureAnalogique;
  maLectureAnalogique = analogRead(MA_BROCHE_ANGLE);
  Serial.print(maLectureAnalogique);
  Serial.println();
  delay(100);

  monPixel = CRGB(255,0,0);
  monPixel = CRGB (maLectureAnalogique*255 / 4095,0,0);
  FastLED.show(); 
  
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
////////////////////////////////////////////////////////////////



#include <Arduino.h>               // bibliothèque d'Arduino avec les fonctions et définitions de base pour utiliser un Arduino.
#include <MicroOscSlip.h>          //permet de gérer la communication OSC (Open Sound Control).
#include <FastLED.h>               //permet de créer des effets lumineux.
#include <M5_PbHub.h>              //permet d'inclure PbHUB
MicroOscSlip<128> monOsc(&Serial); // Création d'un objet monOsc qui utilise la bibliothèque
// Le <128> spécifie la taille du tampon pour l'OSC (c'est la quantité de données qu'il peut gérer).
 
#define MA_BROCHE_BOUTON_KEY 32
#define MA_BROCHE_BOUTON_ATOM 39
 
#define CANAL_KEY_UNIT_LIGHT 2  // ca veut dire que le key LIGHT est branché sur la porte 2 du PbHub
#define CANAL_KEY_UNIT_ANGLE 1    // ca veut dire que le key ANGLE est branché sur la porte 1 du PbHub
#define CANAL_KEY_UNIT 0       // ca veut dire que le key unit est branché sur la porte 0 du PbHub
 
// CRGB monPixelBouton;
CRGB monPixelAtom;
M5_PbHub myPbHub; // POUR CHARGER ET CONFIGURER LE PbHub
 
 
bool etat = true;
 
void setup()
{
 
 
  delay(20);
 
  // pour la communication série
  Serial.begin(115200);
 
  // initialiser pour la communication idec
  Wire.begin();
  myPbHub.begin(); // demarre la bibliothèque mypBHUB
 
  // CONTROLLE LE LED ET LE RGB  ET LE 1 EST  LE NOMBRE DE LUMIÈRE QUE JE VEUX CONTRÔLLER CE QUI SIGNIFIE UNE LUMIÈRE
 
  myPbHub.setPixelCount(CANAL_KEY_UNIT, 1);
  myPbHub.setPixelCount(CANAL_KEY_UNIT_ANGLE, 1);
  myPbHub.setPixelCount(CANAL_KEY_UNIT_LIGHT, 1);
 
  FastLED.addLeds<WS2812, 27, GRB>(&monPixelAtom, 1); // Permet de configurer la bibliothèque FastLed et de lui envoyer le code du CRGB précedant à lumière du AtomE.
  pinMode(MA_BROCHE_BOUTON_ATOM, INPUT_PULLUP);                           // PERMET DE S'ASSURER QU'IL EST RENTRÉ .
}
 
void loop()
{
 
  int maLectureKey = myPbHub.digitalRead(CANAL_KEY_UNIT); // ca veut dire qu'on peut lire le key unit 0 qui a été au préalable démarrer au début et après donner le pouvoir de contrôller les pixels.
 
  int maLectureKeyAngle = myPbHub.analogRead(CANAL_KEY_UNIT_ANGLE); // ca veut dire qu'on peut lire LE KEY_UNIT_ANGLE  qui a été au préalable démarrer au début et après donner le pouvoir de contrôller les pixels.
 
  int malEctureKeyLight = myPbHub.analogRead(CANAL_KEY_UNIT_LIGHT); // ca veut dire qu'on peut lire LE KEY_UNIT_LIGHT  qui a été au préalable démarrer au début et après donner le pouvoir de contrôller les pixels.
 
  int maLectureBoutonAtome = digitalRead(MA_BROCHE_BOUTON_ATOM); // ca veut dire qu'ont peut lire le  bouton de l'atome
 
  monOsc.sendInt("/bouton", maLectureKey);               // ca permet d'envoyer les chiffres et l'identité de canal key_unit 0 avec tous ses set ups
  monOsc.sendInt("/angle", maLectureKeyAngle);           // ca permet d'envoyer les chiffres et l'identité de canal key_unit_angle 1 avec tous ses set ups
  monOsc.sendInt("/light", malEctureKeyLight);           // ca permet d'envoyer les chiffres et l'identité de canal key_Light 2 avec tous ses set ups
  monOsc.sendInt("/bouton_atome", maLectureBoutonAtome); // ca permet d'envoyer les chiffres et l'identité de canal du bouton de l'atome avec tous ses set ups.
 
  if (maLectureKey == 0)
  {
    // Ca veut dire que quand tu pèse sur le bouton rouge du keyUnit, ca active la couleur rouge et jaune d'une manière random et cette activation s'active à partir de la connection du key unit sur PbHUB
    //int rouge = random(0, 128);
   // int vert = random(0, 256);
   // myPbHub.setPixelColor(CANAL_KEY_UNIT, 0, rouge, vert, 0);
  }
 
  else
  {
    myPbHub.setPixelColor(CANAL_KEY_UNIT, 0, 0, 0, 0); // ca veut que qu'on je relache le bouton du key unit, ca revient à 0 et il n'y a plus aucune couleur ou de lumière
  };
 
if (etat == true)  // Si on appuie sur le bouton du M5 Atom
{
  // Rouge
  monPixelAtom = CRGB(255, 0, 0);
  FastLED.show();
  delay(1000);
 
  // Vert
  monPixelAtom = CRGB(0, 255, 0);
  FastLED.show();
  delay(1000);
 
  // Bleu
  monPixelAtom = CRGB(0, 0, 255);
  FastLED.show();
  delay(1000);
 
  // Éteindre à la fin
  monPixelAtom = CRGB(0, 0, 0);
  FastLED.show();
 
  etat = false;
}
else
{
  monPixelAtom = CRGB(0, 0, 0);
  FastLED.show();
}
}
 // 🔵 Quand on appuie sur le Key Unit → LED bleue

//if (maLectureKey == 0)

//{

  //myPbHub.setPixelColor(CANAL_KEY_UNIT, 0, 0, 0, 255); // (R,G,B) → Bleu

//}

//else

//{

  //myPbHub.setPixelColor(CANAL_KEY_UNIT, 0, 0, 0, 0);   // éteint la LED

//}







; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html
 
[env:m5stack-atom]
platform = espressif32
board = m5stack-atom
framework = arduino
lib_deps =
    https://github.com/thomasfredericks/MicroOsc.git
    FastLED
    M5_PbHub
    thomasfredericks/M5_PbHub@^0.1.4

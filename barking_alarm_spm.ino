// librairies
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// pins

#define plusPin 3
#define minusPin 4

/*
  Hardware SPI:
  MISO -> 12
  MOSI -> 11
  SCK -> 13
  CE -> 8
  CSN -> 7
*/

// variables
int playTime = 2000; // time of sound playback [exec]
int remainingTime;
boolean playing;

int received; //debugging

void setup()
{
  Serial.begin(9600); // Serial communication for debugging
  Serial.println("setup...");
  mirfSetup(); // setup of the antenna
  mp3Setup(); // setup of the mp3 player
  remainingTime = 0;
  Serial.println("setup complete");
}

void loop()
{
  // detection management: sets new stopTime every time a signal is received
  byte data;
  
  if(Mirf.dataReady())
  {
    Mirf.getData(&data);
    Serial.println("data received");
    
    if(data == B10011100)
    {
      Serial.println("correct byte received");
      remainingTime = playTime;
    }
  }
  
  
  // if millis is lower than the time to stop and dog hasn't started playing yet
  if(remainingTime > 0 && !playing)
  {
    playing = true;
    Serial.println("sound starting...");
    volumeUp(); // starts playing
    Serial.println("sound started");
  }
  
  if(remainingTime <=0 && playing)
  {
    playing = false;
    Serial.println("sound stopping...");
    volumeDown(); //stops playing
    Serial.println("sound stopped");
  }
  
  if(remainingTime > 0) remainingTime --;
  
  if(playing) Serial.println(remainingTime); //debug
}

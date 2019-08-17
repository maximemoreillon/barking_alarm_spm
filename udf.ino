void mirfSetup()
{
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"dog01"); // address of the antenna
  Mirf.payload = 1;
  // Mirf.channel = 10; // to change the channel if necessary
  Mirf.config();
}

void mp3Setup()
{
  pinMode(plusPin,OUTPUT);
  pinMode(minusPin,OUTPUT);

  delay(3000);
  volumeDown(); // turning dog off
}

void volumeUp()
{
  for(int i=0; i<50; i++)
  {
    digitalWrite(plusPin,HIGH);
    delay(40);
    digitalWrite(plusPin,LOW);
    delay(40);
  }
}

void volumeDown()
{
  for(int i=0; i<50; i++)
  {
    digitalWrite(minusPin,HIGH);
    delay(40);
    digitalWrite(minusPin,LOW);
    delay(40);
  }
}

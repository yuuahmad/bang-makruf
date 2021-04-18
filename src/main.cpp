#include <Arduino.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <Wire.h>

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

int nilai = 0;

SoftwareSerial Thermal(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first

void setup()
{
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  Thermal.begin(9600); // Initialize SoftwareSerial

  Thermal.println("data saya"); //Bitmap example
  Thermal.write(18);            //DC2
  Thermal.write(86);            //V
  Thermal.write(50);            //nL = 10
  for (int y = 0; y < 10; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 48; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }
  for (int y = 0; y < 10; y++) // ini untuk mengatur ketinggian
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 24; x++) //dan ini untuk mengatur panjang dari bar
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 24; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }

  for (int y = 0; y < 15; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 38; x++)
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 10; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }
  for (int y = 0; y < 10; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 24; x++)
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 24; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }

  for (int y = 0; y < 5; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 20; x++)
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 28; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }

  for (int y = 0; y < 20; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 30; x++)
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 18; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }
  for (int y = 0; y < 10; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 20; x++)
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 28; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }
  for (int y = 0; y < 25; y++)
  {
    //Now we need 48 bytes total
    for (int x = 0; x < 40; x++)
    {
      Thermal.write(0xFF); //0b.1111.1111
    }
    for (int x = 0; x < 8; x++)
    {
      Thermal.write(0x01); //0b.1111.1111
    }
  }
  Thermal.write((byte)0); //nH = 0
  Thermal.write(10);
  delay(3000); // Sleep for 3 seconds
}

void loop()
{
}

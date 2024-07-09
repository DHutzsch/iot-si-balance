/**
  * Copyright (c) 2024 Daniel Hutzschenreuter (ORCID: 0000-0002-9095-0063)
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy 
  * of this software and associated documentation files (the “Software”), to deal 
  * in the Software without restriction, including without limitation the rights to 
  * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
  * the Software, and to permit persons to whom the Software is furnished to do so, 
  * subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies 
  * or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
  * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
  * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
  * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
  * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
  **/
  
#include "DHT.h"
#include "HX711.h"

// General flags
#define DEBUG 1         // set to 0 if no debug messages
#define STATE_MEAS 0    // single measurement mode
#define STATE_TARE 1    // tare zero value
#define STATE_CALI 2    // calibrate with reference
int deviceState = STATE_MEAS;

// Setup DHT22 Temperature Sensor
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float h = 0.f;    // Reads the humidity in %
float t = 0.f;    // Reads the temperature in degrees Celsius

// Setup 1kg load cell
#define LOADCELL_DOUT_PIN 20
#define LOADCELL_SCK_PIN 21
HX711 loadcell;
const int Calibration_Weight = 126; // Rosmarin glass of 0.126 kg
float m = 0.f;    // Reads the mass value in kg

// Setup button and LED 1
#define button1Pin 10  // pi pico connected to button's pin
#define LED1Pin    11  // pi pico pin connected to LED's pin
int led1State = LOW;        // the current state of LED

// Setup button and LED 2
#define button2Pin 12  // pi pico connected to button's pin
#define LED2Pin    13  // pi pico pin connected to LED's pin
int led2State = LOW;        // the current state of LED



void setup() { 
  setupSerial();
  setupDHT();
  setupLoadCell();
  setupButton1();
  setupButton2();
  setupBuzzer();
}

void loop() {
  if (STATE_MEAS == deviceState)
  {
    checkButton1();
    checkButton2();
  }
   
}

void setupSerial()
{
  // Setup Serial
  Serial.begin(9600);
  delay(3000);
  Serial.println("Startup Raspi Pico  Hello World");
}

void setupDHT()
{
  // Setup Temperature Humidity Sensor
  dht.begin();
  delay(500);
  Serial.println(F("Startup DHT22"));
}

void setupLoadCell()
{
  // Setup Load Cell
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(1108);
  loadcell.set_offset(0);
  loadcell.tare();
  delay(500);
  Serial.println(F("Startup Load Cell"));
}

void setupButton1()
{
  //Setup Button and LED 1
  pinMode(button1Pin, INPUT_PULLUP); // set pi pico pin to input pull-up mode
  pinMode(LED1Pin, OUTPUT);          // set pi pico pin to output mode
  digitalWrite(LED1Pin, HIGH);
  delay(500);
  digitalWrite(LED1Pin, LOW);
  Serial.println(F("Startup Button and LED 1"));
}

void setupButton2()
{
  // Setup Button and LED 2
  pinMode(button2Pin, INPUT_PULLUP); // set pi pico pin to input pull-up mode
  pinMode(LED2Pin, OUTPUT);          // set pi pico pin to output mode
  digitalWrite(LED2Pin, HIGH);
  delay(500);
  digitalWrite(LED2Pin, LOW);
  Serial.println(F("Startup Button and LED 2"));
}




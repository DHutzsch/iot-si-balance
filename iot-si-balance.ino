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
  
  * Serial on baud 9600
  */

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "DHT.h"
#include "HX711.h"

// General flags
#define DEBUG 0         // set to 0 if no debug messages
#define STATE_MEAS 0    // single measurement mode
#define STATE_UNCT 1    // uncertainty display mode
#define STATE_ADJ1 2    // adjust with reference - set reference weight
#define STATE_ADJ2 3    // adjust with reference - put reference weight on scale
int state = 0;
unsigned long nextTimerEvent = 0; // timer for measurement value update
unsigned long timerStep = 2000;   // step of timer in milli seconds

// TFT display parameters
#define TFT_DSI  0xC000     // D-SI red colour
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
float x0s = 1.; // start x of lines
float y0s = 1.; // start y lines
float x0e = 1.; // end x lines
float y0e = 1.; // end y lines

// parameters DHT22 temperature Sensor
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// parameters 1kg load cell
#define LOADCELL_DOUT_PIN 8 
#define LOADCELL_SCK_PIN 9 
HX711 loadcell;
const int Calibration_Weight = 126; // Rosmarin glass of 0.126 kg

// Setup button and LED 1
#define button1Pin 10  // pi pico connected to button's pin
#define LED1Pin    11  // pi pico pin connected to LED's pin
int led1State = LOW;        // the current state of LED
int buttonCounter1 = 0; // count number loops button 1 was pushed

// Setup button and LED 2
#define button2Pin 12  // pi pico connected to button's pin
#define LED2Pin    13  // pi pico pin connected to LED's pin
int led2State = LOW;        // the current state of LED
int buttonCounter2 = 0; // count number loops button 2 was pushed

// Setup adjustment parameters
#define potiPIN 26 // analoge input for poti 
float setMass0 = 0;  // value 0, ..., 2 kg
float setMass1 = 0;  // value 0, ..., 2 kg
const int numberMeasurements = 5;
float adjustmentMeasures[numberMeasurements];
float adjValue = 0;

// Measurement data parameters
bool adjusted = false;              // true, if adjustment with reference weight was made
float massValue = 0.f;                   // mass measurement value in kg
float massUncertaintyValue = 0.15;  // expanded measurement uncertainty of mass (k=2, p=0.95, normal)
float tempValue = 0.f;              // temperature measurement value in degree Celsius
float tempUncertaintyValue = 0.50;  // expanded measurement uncertainty of ambient temperature (k=2, p=0.95, normal)
float humValue = 0.f;               // relative humidity vlue in percent
float reHuUncertaintyValue = 5.00;  // expanded measurement uncertainty of ambient relative humidity (k=2, p=0.95, normal)



void setup() 
{
  setupDisplay();
  setupSerial();
  setupDHT();
  setupLoadCell();
  setupButton1();
  setupButton2();
  setupPoti();

  startupWrite("done :-)");
  delay(1000);

  // init measurement frame
  state = STATE_MEAS;
  drawMainFrame();
  delay(1000);
  // init timer
  updateTimer();

}

void loop() {
  // evaluate measurement mode
  if (STATE_MEAS == state)
  {
    updateAtTimerEvent(); // update sensor values
    checkMeasureTare();   // check event on button 1
    checkUncertAdjust();  // check event on button 2
  }
  else if (STATE_UNCT == state)
  {
    checkCloseUncertainty();
  }
  else if (STATE_ADJ1 == state)
  {
    updateReference();  // read poti (ref weight set)
    checkSetWeight();   // check set button event
  }
  else if (STATE_ADJ2 == state)
  {
    // check run button event
    checkRunAdjustment();
  }
  delay(100);

}



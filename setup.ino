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
  */

void setupDisplay()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_DSI, TFT_BLACK);
  tft.drawString("D",37,20,4);
  
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("-VICE",57,20,4);
  tft.drawCentreString("SETUP",79,40,4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  delay(1000);
}

void setupSerial()
{
  // Setup Serial
  startupWrite("setup Serial (9600)");
  Serial.begin(9600);
  delay(1000);
  debugMessage("Startup Raspi Pico  Hello World done");
}

void setupDHT()
{
  // Setup Temperature Humidity Sensor
  startupWrite("setup DHT22");
  dht.begin();
  delay(1000);
  readTempHumi();
  debugTHData();
  debugMessage("Startup DHT22 done");
}

void setupLoadCell()
{
  // Setup Load Cell
  startupWrite("setup load cell");
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(1000);
  loadcell.set_scale(-1108);
  loadcell.set_offset(0);
  loadcell.tare();
  readLoadCell();
  debugLoadCellData();
  debugMessage("Startup Load Cell done");

  startupWrite("set Planck constant");
  delay(1000);
  startupWrite("define the kilogram");
  delay(1000);
}

void setupButton1()
{
  //Setup Button and LED 1
  startupWrite("setup button 1");
  pinMode(button1Pin, INPUT_PULLUP); // set pi pico pin to input pull-up mode
  pinMode(LED1Pin, OUTPUT);          // set pi pico pin to output mode
  digitalWrite(LED1Pin, HIGH);
  delay(500);
  digitalWrite(LED1Pin, LOW);
  debugMessage("Startup Button and LED 1 done");
  delay(500);
}

void setupButton2()
{
  // Setup Button and LED 2
  startupWrite("setup button 2");
  pinMode(button2Pin, INPUT_PULLUP); // set pi pico pin to input pull-up mode
  pinMode(LED2Pin, OUTPUT);          // set pi pico pin to output mode
  digitalWrite(LED2Pin, HIGH);
  delay(500);
  digitalWrite(LED2Pin, LOW);
  debugMessage("Startup Button and LED 2 done");
  delay(500);
}

void setupPoti()
{
  startupWrite("setup poti");
  pinMode(potiPIN, INPUT); // set analoge input
  setMass0 = convertToMass(analogRead(potiPIN));
  for (int i= 0; i < numberMeasurements; i++)
  {
    adjustmentMeasures[i] = 0.f;
  }
  debugMessage("Startup poti done");
  delay(500);
}


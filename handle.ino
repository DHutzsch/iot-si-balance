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

void sendDataSerial()
{
   // TODO send D-SI data
}




void checkMeasureTare()
{
  // Button pushed
  if (digitalRead(button1Pin) == LOW)
  {
    debugMessage("[Button 1 pushed]");
    // increament counter
    buttonCounter1 += 1;

    // activate tare mode (if button pushed one second)
    if (buttonCounter1 > 7)
    {
      mainWriteMode("TARE");
      blink1(3);
      delay(500);
      loadcell.tare();
      delay(500);
      blink1(3);
      mainResetMode();
      // reset counter
      buttonCounter1 = 0;
    }
  }
  else
  {
    // make a single measurement
     if (buttonCounter1 > 0)
     {
       mainWriteMode("MEAS.");
       digitalWrite(LED1Pin, HIGH);    // turn on button LED
       // read data
       readTempHumi();
       readLoadCell();
       // update display
       drawAmbient(tempValue,humValue);
       setGauge(massValue);
       // send D-SI serial
       sendDataSerial();
       // debug
       debugTHData();
       debugLoadCellData();
       delay(1000);
       digitalWrite(LED1Pin, LOW);     // done, turn off LED
       mainResetMode();
       debugMessage("measurement done");
       // reset button counter
       buttonCounter1 = 0;
     }
  }
}


void checkUncertAdjust()
{
  // Button pushed
  if (digitalRead(button2Pin) == LOW)
  {
    debugMessage("[Button 2 pushed]");
    // increament counter
    buttonCounter2 += 1;

    // activate adjustment mode (if button pushed one second)
    if (buttonCounter2 > 7)
    {
      // TODO
      blink2(3);
      // change to weight set state
      state = STATE_ADJ1;
      // draw weight set display frame
      drawAdjustmentSetFrame();
      updateReference();
      delay(500);
      // reset counter
      buttonCounter2 = 0;
    }
  }
  else
  {
    // open uncertainty tab
     if (buttonCounter2 > 0)
     {
       digitalWrite(LED2Pin, HIGH);    // turn on button LED
       //change state
       state = STATE_UNCT;
       // load uncertainty display frame
       drawUncertaintyFrame();
       delay(1500);
       // reset button counter
       buttonCounter2 = 0;
     }
  }  
}

void checkCloseUncertainty()
{
  if (digitalRead(button2Pin) == LOW)
  {
    // change state
    state = STATE_MEAS;
    // draw main frame
    drawMainFrame();
    delay(500);
    // turn off LED 2
    digitalWrite(LED2Pin, LOW); 
  }
}

void checkSetWeight()
{
  if (digitalRead(button2Pin) == LOW)
  {
    
    // blink LED 2
    blink2(3);
    // change state to step two of adjustment
    state = STATE_ADJ2;
    // tare balance
    loadcell.set_scale();
    loadcell.tare();
    // draw main frame
    drawAdjustmentWeightFrame();
    delay(500);
  }
}

void checkRunAdjustment()
{
  if (digitalRead(button2Pin) == LOW)
  {
    // turn on LED 2
    digitalWrite(LED2Pin, HIGH); 
    // draw run adjustment frame
    drawAdjustmentRunFrame();
    
    // make measurements
    adjustmentMeasureRun();
    // adjust scale
    evaluateAdjustment();

    // change state
    state = STATE_MEAS;
    // draw main frame
    drawMainFrame();
    // tunr off LED 2
    digitalWrite(LED2Pin, LOW); 
  }
}


void updateAtTimerEvent()
{
  if (millis() > nextTimerEvent)
  {
    // update DHT sensor
    readTempHumi();
    debugTHData();
    drawAmbient(tempValue, humValue);
    // update load cell
    readLoadCell();
    debugLoadCellData();
    setGauge(massValue);

    updateTimer();
  }
}

void updateTimer()
{
  nextTimerEvent = millis() + timerStep;
}

void blink1(int n)
{
  for (int i = 0; i < n; i++)
  {
    digitalWrite(LED1Pin, HIGH);     // done, turn off LED
    delay(150);
    digitalWrite(LED1Pin, LOW);     // done, turn off LED
    delay(150);
  }
}

void blink2(int n)
{
  for (int i = 0; i < n; i++)
  {
    digitalWrite(LED2Pin, HIGH);     // done, turn off LED
    delay(150);
    digitalWrite(LED2Pin, LOW);     // done, turn off LED
    delay(150);
  }
}

void updateReference()
{
  setMass1 = convertToMass(analogRead(potiPIN));
  if (setMass0 != setMass1)
  {
    setMass0 = setMass1;
    setGauge(setMass0);
  }
}
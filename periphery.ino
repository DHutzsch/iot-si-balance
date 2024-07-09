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

/**
 * Make one mass measurement
 */
void checkButton1()
{
  // Button gedrückt
  if (digitalRead(button1Pin) == LOW)
  {
    digitalWrite(LED1Pin, HIGH);
    Serial.print("[Button 1] "); 
    readLoadCell();
    readTempHumi();
    plotDataDebug();
    delay(1000);
    digitalWrite(LED1Pin, LOW);
  }
}

/**
 * Calibrate load cell
 */
void checkButton2()
{
  // Button gedrückt
  if (digitalRead(button2Pin) == LOW)
  {
    toogleLED2();
    Serial.print("[Button 2] ");

    loadcell.set_scale();
    loadcell.tare();
    Serial.println("Calibration");
    Serial.println("Put a known weight on the scale");
    
    for (int i = 0 ; i < 10 ; i++)
    {
      toogleLED2();
      delay(500);
    }
    
    float x = loadcell.get_units(10);
    x = x / Calibration_Weight;
    //Serial.print("Scale... ");  //Serial.println(x);    // -1108.57, -1108.27,  -1108.52, -1107.72, -1108.52
    loadcell.set_scale(x);
    Serial.println("Calibration finished...");
    delay(500);
  
    led2State = LOW;
    digitalWrite(LED2Pin, led2State);
  }
}

void toogleLED2()
{
  led2State = !led2State;
  digitalWrite(LED2Pin, led2State);
}



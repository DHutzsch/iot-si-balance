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

void adjustmentMeasureRun()
{
  for (int i= 0; i < numberMeasurements; i++)
  {
    blink2(2);
    adjustmentMeasures[i] = loadcell.get_units(10);
    //setGauge(adjustmentMeasures[i]/ 1000.f); 
    Serial.print("adj val 0..5: "); Serial.println(adjustmentMeasures[i]);
    delay(1000);
  }
}

void evaluateAdjustment()
{
  // arithmetic mean of measures
  adjValue = 0.f;
  for (int i= 0; i < numberMeasurements; i++)
  {
    adjValue += adjustmentMeasures[i];
  }
  adjValue = adjValue / numberMeasurements;
  Serial.print("adj val 1: "); Serial.println(adjValue);
  adjValue = adjValue / (setMass0 * 1000.f);
  Serial.print("adj val 2: "); Serial.println(adjValue);
  loadcell.set_scale(adjValue);
  loadcell.set_offset(0);
}





float convertToMass(int potiValue)
{
  // transform value [0,1023] to [0,2] kg
  if (potiValue < 0)
  {
    return 0.00f;
  }
  else if (potiValue > 1023)
  {
    return 2.00f;
  }
  else
  {
    return potiValue / 1023.f * 2.00;
  }
}
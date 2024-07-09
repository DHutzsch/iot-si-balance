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

void drawMainFrame()
{
  // outer frame
  tft.drawLine(0, 0, 0, 127, TFT_SKYBLUE);
  tft.drawLine(0, 127, 159, 127, TFT_SKYBLUE);
  tft.drawLine(159, 127, 159, 0, TFT_SKYBLUE);
  tft.drawLine(159, 0, 0, 0, TFT_SKYBLUE);
  tft.fillRect(1, 1, 158, 126, TFT_BLACK);
  // left button frame
  drawMenuLeft();
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawCentreString("M",10,108,2);
  tft.setTextColor(TFT_BLACK, TFT_SKYBLUE);
  tft.drawCentreString("TA",30,108,2);
  // right button frame
  drawMenuRight();
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawCentreString("U",117,108,2);
  tft.setTextColor(TFT_BLACK, TFT_SKYBLUE);
  tft.drawCentreString("ADJ",143,108,2);
  // draw gauge
  drawGauge();
  drawAmbient(tempValue,humValue);
  setGauge(massValue);
}

void drawAdjustmentSetFrame()
{
  // setup menu SET button
  tft.fillRect(1, 1, 158, 126, TFT_BLACK);
  drawMenuRight();
  tft.drawCentreString("SET",117,108,2);
  // draw title and instruction
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawString("Set Reference Weight",10,2,2);
  tft.drawString("Adjustment",10,108,2);
  // draw gauge
  drawGauge();
  setGauge(0.);

}

void drawAdjustmentWeightFrame()
{
  // setup menu OK button
  tft.fillRect(1, 1, 158, 126, TFT_BLACK);
  drawMenuRight();
  tft.drawCentreString("OK",117,108,2);
  // draw title and instruction
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawString("Put Weight on Balance",10,2,2);
  tft.drawString("Adjustment",10,108,2);
  // draw picture of load cell
  tft.drawLine(30, 90, 130, 90, TFT_WHITE);
  tft.drawLine(30, 70, 130, 70, TFT_WHITE);
  tft.drawLine(30, 90, 30, 70, TFT_WHITE);
  tft.drawLine(130, 70, 130, 90, TFT_WHITE);
  tft.drawArc(76, 80, 8, 8, 0, 210, TFT_WHITE, TFT_BLACK);
  tft.drawArc(76, 80, 8, 8, 330, 360, TFT_WHITE, TFT_BLACK);
  tft.drawArc(85, 80, 8, 8, 150, 360, TFT_WHITE, TFT_BLACK);
  tft.drawArc(85, 80, 8, 8, 0, 30, TFT_WHITE, TFT_BLACK);
  // draw picture of table
  tft.drawLine(30, 65, 60, 65, TFT_WHITE);
  tft.drawLine(30, 64, 60, 64, TFT_WHITE);
  tft.drawLine(30, 63, 60, 63, TFT_WHITE);
  // draw picture of weight
  tft. drawLine(37, 60, 53, 60, TFT_WHITE);
  tft. drawLine(37, 60, 37, 35, TFT_WHITE);
  tft. drawLine(53, 35, 53, 60, TFT_WHITE);
  tft. drawLine(37, 35, 40, 35, TFT_WHITE);
  tft. drawLine(53, 35, 50, 35, TFT_WHITE);
  tft.drawArc(40, 32, 3, 3, 180, 360, TFT_WHITE, TFT_BLACK);
  tft.drawArc(50, 32, 3, 3, 0, 180, TFT_WHITE, TFT_BLACK);
  tft. drawLine(39, 28, 51, 28, TFT_WHITE);
  // draw picture of arrow
  tft. drawLine(15, 40, 15, 80, TFT_WHITE);
  tft. drawLine(15, 80, 9, 74, TFT_WHITE);
  tft. drawLine(15, 80, 21, 74, TFT_WHITE);
}

void drawAdjustmentRunFrame()
{
  // setup menu (empty)
  tft.fillRect(1, 1, 158, 126, TFT_BLACK);
  drawMenuRight();
  // draw title and instruction
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawString("Run Adjustment",10,2,2);
  tft.drawString("Adjustment",10,108,2);
  // draw gauge
  drawGauge();
  setGauge(0.);
}

void drawUncertaintyFrame()
{
  // setup menu OK button
  tft.fillRect(1, 1, 158, 126, TFT_BLACK);
  drawMenuRight();
  tft.drawCentreString("EXT",117,108,2);
  // draw title
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawString("U(k=2,p=0.95,normal)",10,2,2);
  // draw calibration status
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  int16_t dist = tft.drawString("Adjusted:",10,30,2);
  if (adjusted)
  {
    tft.drawString("true", 15+dist, 30,2);
  }
  else
  {
    tft.drawString("false", 15+dist, 30,2);
  }
  // draw unsertainty mass
  dist = tft.drawString("U mass [kg]:",10,50,2);
  tft.drawFloat(massUncertaintyValue,2,15+dist,50,2);
  // draw unsertainty temperature
  dist = tft.drawString("U T[ C]:",10,70,2);
  tft.drawCircle(dist-9, 74, 2, TFT_WHITE);
  tft.drawFloat(tempUncertaintyValue,2,15+dist,70,2);
  // draw unsertainty relative humidity
  dist = tft.drawString("U rH [%]:",10,90,2);
  tft.drawFloat(reHuUncertaintyValue,2,15+dist,90,2);
  

}

void startupWrite(const char * string)
{
  tft.drawCentreString("                         ",79,100,2);
  tft.drawCentreString(string,79,100,2);
}

void mainWriteMode(const char * string)
{
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawCentreString(string,73,108,2); // ceter of [43, 104]
}

void mainResetMode()
{
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.drawCentreString("       ",73,108,2); // ceter of [43, 104]
}

void drawMenuLeft()
{
  tft.drawRoundRect(3, 107, 40, 18, 3, TFT_SKYBLUE);
  tft.fillRoundRect(17, 107, 26, 18, 3, TFT_SKYBLUE);
}

void drawMenuRight()
{
  tft.drawRoundRect(104, 107, 52, 18, 3, TFT_SKYBLUE);
  tft.fillRoundRect(130, 107, 26, 18, 3, TFT_SKYBLUE);
}

void drawGauge()
{
  // 120 - 240 deg
  // diameter 80 pixels
  tft.drawArc(79, 115, 81, 80, 120, 240, TFT_YELLOW, TFT_BLACK);
  // draw lines on arc: 0, 0.5, 1, 1.5 and 2 kg
  for(int i = 40; i<141; i+= 25) {
    float sx = cos(i*0.0174532925);
    float sy = sin(i*0.0174532925);
    float x0 = sx*80+79;
    float y0 = 115-sy*80;
    float x1 = sx*84+79;
    float y1 = 115-sy*84;
    tft.drawLine(x0, y0, x1, y1, TFT_YELLOW);
  }
  // draw relevant text
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawCentreString("1",80,20,1);
  tft.drawCentreString("0",8,52,1);
  tft.drawCentreString("2",151,52,1);
  tft.drawCentreString("mass",20,80,2);
  tft.drawCentreString("kg",148,80,2);
}

/* 
 * Call this method to update the mass value 
 * on display
 */
void setGauge(float massValue)
{
   // write value
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(TR_DATUM);
  tft.fillRect(48,85,10,3,TFT_BLACK);
  tft.drawFloat(massValue,2,108,75,4);
  tft.setTextDatum(TL_DATUM);

  // draw gauge indicator
  // calculate angle within allowed bounds
  float alpha = 140. - massValue * 50.;
        alpha = min(alpha,150.);
        alpha = max(alpha, 40.);
  // calculate position of bar
  float sx = cos(alpha*0.0174532925);
  float sy = sin(alpha*0.0174532925);
  float x1s = sx*71+79;
  float y1s = 115-sy*71;
  float x1e = sx*77+79;
  float y1e = 115-sy*77;
  // erase old bar
  tft.drawLine(x0s, y0s, x0e, y0e, TFT_BLACK);
  // draw new bar
  tft.drawLine(x1s, y1s, x1e, y1e, TFT_WHITE);
  // flip data
  x0s = x1s;
  y0s = y1s;
  x0e = x1e;
  y0e = y1e;
}

void drawAmbient(float vT, float vRH)
{
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  // write parameters temperature
  tft.drawCentreString("T|",10,2,2);
  tft.drawCentreString("C",68,2,2);
  tft.drawCircle(60, 7, 2, TFT_SKYBLUE);
  // write parameters relative humidity
  tft.drawCentreString("rH",150,2,2);
  tft.drawCentreString("|",139,2,2);
  tft.drawCentreString("%",131,2,2);
  // display first values
  writeTempAndHumi(vT, vRH);
}

void writeTempAndHumi(float vT, float vRH)
{
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  // write temepratur
  tft.fillRect(48,2,8,15,TFT_BLACK);
  tft.drawFloat(vT,2,19,2,2);
  // write relative humidity
  tft.fillRect(116,2,8,15,TFT_BLACK);
  tft.drawFloat(vRH,2,87,2,2);
}
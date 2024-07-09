## Basic Operation Instruction

The balance has a load-cell to measure the value of weight by putting the weights on the little tray on top of the load cell (HX711 load-cell). The measured values and current values of loads on the tray are shown on the gauge on a LCD display. Also the values of air temperature and humidity close to the load-cell are displayed (values from DHT 22 sensor). 

**Single measurement**

The left button on the device allows to execute one measurement. It is triggert by short press of the button. The LED on the button will be on when measuring and the display will say "Meas.". 

![Default Measure](figures/03-default.JPG){height=180px}![Default Measure](figures/05-display-default.JPG){height=180px}

**Tara of the balance**

This function is for setting the displayed mass value to zero which is called tara. This function is typically used to eliminate the weight of bowls or similar that are put on the balance to hold the actual substance that is measured. It also used to set the zero point when starting up the balance. To rund tara, hold the left button pressed for several seconds. The LED on the button will blink, when tara is activated and the display will show "tara".

**Display measurement uncertainty**

The balance provides metadata on the expanded measurement uncertainty associated to its sensors. Press the right button for a short time and the display will show this information. To close the uncertainty information, press the right button again.

![Uncertainty](figures/04-measurement-uncertainty.JPG){height=180px}!

**Run an adjustment of the measurement value**

A simple software based adjustment of the mass measurement values is implemented. This will adjust the mass values to a known reference weight. To use this function properly, you need a reference weight piece with knowl mass value. E.g., I uses littel solid objects that were measured with a kitchen balance to obtain a reference value. 
You can activate the adjustment function by holding the right button pressed for a few seconds. At this time, no weights should be put on the tray of the load-cell. The display will show a page that asks you to enter the reference mass value. The value is added by turning the poti between the buttons. The software supports a range between 0 and 2 kg (range of the load-cell). When you have set the right value, press the right button again. now you are asked to put the reference weight piece on the load-cell and confirm by pressing the right button again. After this step, the balance is making 5 measurements of the reference and it calculates the arithmetic mean of the values. Then, the mass value is adjusted to the mean value and the adjustment is completed. After the adjustment, you need to remove the reference weight piece and run the tara function to get correct measurements. 

![Adjsutment](figures/06-display-adjustment-set-weight.JPG){height=170px}![Adjsutment](figures/07-display-adjustment-put-weight-on-balance.JPG){height=170px}![Adjsutment](figures/08-display-rund-adjustment-measures.JPG){height=170px}

## Hardware

The balance has been build with the following IoT components:
- Raspberry PI Pico WH (RP20240, Cortex M0+)
- DEBO DHT 22 Temperature & Humidity Sensor
- DEBO HX711-01 1 Kg load cell sensor with AD converter
- DEBO LCD display 1.8 inch (128x160 picel, ST7735S chip)
- DEBO MP 1584EN DCDC step-down power converter (suitable for converting 5 V into 3.3 V)
- 2 LEDs, 2 Buttons, 5 kOhm poti, some prototyping board

The device is powered by 5 Volt Micro USB input of the Pico WH microcontroller. Through the VBUS pin, the input voltage is provided to the DCDC power converter reducing it to 3.2 Volt. This voltage drop is needed to operate alls sensors and buttons in the range of 3.3 Volt maximum input to the PICO WH GPIOs. In a more simple case, it would have been sufficient to use the 3.3 Volt output of the Pico WH directly, but as we have also installed a display and several LEDs, the dedicated step-down converter is a better solution.

The left button and LED are associated with button 1 and LED 1. The right button and LED respectively have number 2.

The display has a SPI based connection, the load cell has a kind of I2C like connection, and the DHT 22 sensor has a simple digital protocol on a digital GPIO pin.

**Pinout of the Pico WH and connection of components**

![figure of Pico WH pin layout](figures/12-pico-pin-layout.PNG){height=300px}

**Figure of the electronics setup**

![electronics setup](figures/09-detail-electronics.JPG){height=220px}

**Figure of the load cell**

![electronics setup](figures/10-detail-load-cell.JPG){height=105px}

**Figure of the DHT 22 sensor**

![electronics setup](figures/11-detail-sensors.JPG){height=150px}

**Figure of the display and control**

![electronics setup](figures/05-display-default.JPG){height=300px}


## software

The software was developped and uploaded with the Arduino IDE 2.3.2 by Arduino using the following libraries:

- Arduino Mbed OS RP2040 Boards version 4.1.4,
- DHT sensor library by Adafruit version 1.4.6,
- HX711 Arduino library by Bogdan Necula version 0.7.5.,
- TFT_eSPI by Bodmer version 2.5.43
- default SPI of Arduino BusIO by Adafruit version 1.16.1

The main code file is iot-si-balance.ino. The loop function implements a finite automate with different behaviour based on the function status (Measurement, Uncertainty, Adjustment 1&2). But basically, it is running updates of the display and checking inputs from the buttons. There is also a flag to set DEBUG mode that provide more data through the serial port. 

The serial port is running on 9600 baude.

All setup is outsourced in the setup.ino file.

Methods handling the events when pressing buttons are implemented in the handle.ino.

In sensors.ino, interfaces are implemented to read the data from the load cell and DHT 22.

The whole visual display of data on the LCD is provided by methods from display.ino.

Finally (implementation still a TODO), the serial.ino will provide methods for the serial exchane of data and medata with a computer and physics.ino will in future provide more suffisticated methods to evaluate the measurands and their measurement uncertainties.



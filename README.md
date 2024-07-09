# IoT SI Scale

## Name
IoT SI Balance

## Description
This projects describes the setup of a low-budget IoT balance for weighing. Its software is implemented on a Raspberry PI Pico 
microcontroller. The scope of available functions includes measurement, tara, adjustment and uncertainty display for mass measurements 
made using a load-cell. In addition, a serial interface allows data exchange with a computer enabling automation of the usage of the 
device, e.g., for a combination with a Digital Twin. Data exchange is based on the D-SI metadata model.

## Visuals

![Balance Device](figures/01-main-figure.JPG)

## Installation
Arduino IDE 2.3.2 by Arduino with libraries
- Arduino Mbed OS RP2040 Boards version 4.1.4, 
- DHT sensor library by Adafruit version 1.4.6, 
- HX711 Arduino library by Bogdan Necula version 0.7.5.,
- TFT_eSPI by Bodmer version 2.5.43
- default SPI of Arduino BusIO by Adafruit version 1.16.1

## Usage
Please, refer to the Wiki.

## Support
Documentation in this Git project and in the source code is the only available support.

## Roadmap
[x] Initial hardware and software prototype setup
[x] manufacturing table top device
[x] Git publication of first release
[ ] Serial interface: add measurement data exchange and external trigger functions for measurement, tara, adjustment, and uncertainties
[ ] Core software: add measurment model including air temperature and air humidity adjustment and calibration point adjustments 

## Contributing
You are welcome to make suggestions for improvements and additions. Please, also feel free to work with your own copy 
and modification of the original source code.

## License
Copyright (c) 2024 Daniel Hutzschenreuter (ORCID: 0000-0002-9095-0063)

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the “Software”), to deal 
in the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

## Project status
Non-regular updates.

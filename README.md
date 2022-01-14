# CompInfo
Output computer information in Russian of Windows system to Arduino.

---

Layout image from http://wiki.amperka.ru under license [CC BY-NC-SA 4.0](http://creativecommons.org/licenses/by-nc-sa/4.0/)

---

Tested so far on one environment:
- Windows 10 (21H2)
- Python 3.10.1
- Arduino Uno R3
- 16x2 Character LCD screen [MELT (МЭЛТ) МТ–16S2H v. 7](https://files.amperka.ru/datasheets/MT-16S2H.pdf)

With dependencies:

Python:
- psutil - 5.9.0
- pyserial - 3.5

Arduino:
- LiquidCrystal - 1.0.7

I will be very glad if you test it in practice on other environments :blush:


<br/>


### Quick deploy
1. Assemble layout like [here](http://wiki.amperka.ru/products:display-lcd-text-16x2#%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D1%8B_%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B_%D0%B4%D0%BB%D1%8F_arduino):

![Layout](http://wiki.amperka.ru/_media/products:display-lcd-text-16x2:display-lcd-text-16x2-arduino-wiring.png)

2. Connect your Arduino Uno via USB 2.0 A - USB 2.0 B to the computer from where we will output data to your Arduino
3. Download and install [Python](https://www.python.org/) and [Arduino IDE](https://www.arduino.cc/en/software)
4. Download (or make a "git clone") folder with sketch (*.ino*) and Python script from "master" branch or "tech" branch (all commits tested :wink:)
5. Upload sketch (*.ino*) to Arduino via Arduino IDE
6. Download [dependencies](https://pip.pypa.io/en/stable/cli/pip_install/#examples) from *requirements.txt* (**highly recommend** do it in a [virtual environment](https://docs.python.org/3/library/venv.html))
7. Launch Python script

Done!

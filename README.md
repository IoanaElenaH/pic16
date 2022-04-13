# pic16
This project aims to read temperature and humidity. It also has a RTC clock.

Components

PIC16F887
LCD LM044L 20x4
Analog Temperature Sensor [LM35]
Digital Temperature Sensor [DS18B20]
Digital Humidity Sensor [DHT11]
Analog Humidity Sensor [HR-202]
RTC DS1307
40-pin socket
2x 5p, 2x 2p, 1x 3p connectors
10k Resistant (x11)
3x button

Block Diagram

![image](https://user-images.githubusercontent.com/85832851/163269096-8037a01f-6a63-44d1-829f-f6d8c25f0840.png)

HR202 interpolating

It's important to remember that the sensor is analogue and requires AC power. It is not a particularly user-friendly Humidity sensor.
It's a resistive sensor, the RH value changes with temperature and you have to apply AC to it.
The precision with which you can measure its resistance will determine how precise your final humidity reading is.
From the [datasheet](https://www.elecrow.com/download/HR202%20Humidity%20Sensor.pdf), there is a table that lists the sensor's resistance at various Relative Humidity values at a specific temperature. 
The equation implemented determines humidity value using the current temperature and resistance value from the sensor as inputs. 

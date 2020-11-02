SVM40 on Arduino Platforms
==========================

This guide describes how to get the SVM40 module working on Arduino
platforms. It offers a step by step guide to get basic functionality working.

Preparation
-----------

To flash the Arduino Board you need to download and install the
Arduino IDE. You can find guides how to do that on the Arduino Webpage:
Windows: https://www.arduino.cc/en/Guide/Windows
Linux: https://www.arduino.cc/en/Guide/Linux
Mac OS: https://www.arduino.cc/en/Guide/MacOSX

Connecting the Sensor Module
----------------------------

Your module has the six different connectors: VCC, GND, SDA, SCL, SEL and NC.
Now you need to connect the module to the correct pins on your board. To find
out which pins are the correct ones consult the Arduino Website for the pinout
of your specific board. Look for SDA to connect the modules SDA pin, for SCL
to connect the SCL pin, GND for the GND pin and a 5V supply for the VCC pin.
To select the I2C interface you need to pull SEL to ground, so just connect
this wire to another GND pin. NC means 'No Connection' therefore the connector 
is not used, so don't worry about that one.

Flashing Arduino Board
----------------------

Start by downloading the ``svm40-arduino-VERSION.zip`` release form the
release page (https://github.com/Sensirion/embedded-svm40/releases).
Unpack the ``.zip`` file and navigate into the resulting directory. Click on
the ``.ino`` file, this should start the Arduino IDE and open the project. If
it doesn't work start the Arduino IDE, in the top bar click on File, Open... ,
navigate to the unziped folder and open the ``.ino`` file.

For some boards you need to install an additional package to be able to
flash them via the Arduino IDE. This is done selecting the Menu items `Tools
> Boards > Boards Manager`. Then you can type the name of your board in the
search bar and install the respective package.

Now you only need to upload the code to your board. Connect your Arduino board
with your computer using an USB cable. Then you'll need to select the entry in
the `Tools > Board` menu that corresponds to your Arduino board. Finally you
also need to select the right port where your Arduino is connected. For this
navigate to `Tools > Port` and select the one indicating that your board is
connected there (name of your board at the end in brackets). To now upload your
code to your board click the arrow icon in the top lefthand corner. This
process can take a while.

Checkout Sensor Data
--------------------

To look at the senor data open the serial monitor by navigating to `Tools >
Serial Monitor`. If everything worked fine and your Arduino is still connected
you now should see the measuring data of the Sensor.

::

    Measurement result
     VOC index: 102.00
     Relative Humidity: 39.05
     Temperature: 26.06
    Measurement result
     VOC index: 102.00
     Relative Humidity: 39.03
     Temperature: 26.08
    Measurement result
     VOC index: 102.10
     Relative Humidity: 39.04
     Temperature: 26.10
    Measurement result
     VOC index: 102.10
     Relative Humidity: 39.04
     Temperature: 26.10
    ...

Troubleshooting
---------------

Initialization failed
~~~~~~~~~~~~~~~~~~~~~

Check if you connected the module correctly, and all cables are fully
plugged in and connected to the correct header.

VOC Index is zero
~~~~~~~~~~~~~~~~~

During the initialization phase of the VOC Index algorithm, which is the first
100 iterations, the VOC Index will output zero.

.. |Arduino Pinout| image:: ./images/Pinout-NANOble_latest_marked.png

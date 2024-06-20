**Aquaponics System with SMS Alerts**

This project is an aquaponics system that monitors various parameters and sends SMS alerts to the user's phone number using a GSM SIM800C TTL module.

**Components**

Arduino Uno or compatible board,
pH sensor,
Water level sensor,
Temperature sensor,
GSM SIM800C TTL module,
Breadboard and jumper wires,
12V power supply,

**Features**

Measures and displays pH, water level, and temperature values on the serial monitor.
Sends SMS alerts to the user's phone number when any of the measured values go beyond the set thresholds.
Easy to configure and customize thresholds for alerts.

**Setup**

Connect the pH(A0), water level(A1), and temperature sensors(A5) to the appropriate analog pins on the Arduino board.
Connect the GSM SIM800C TTL module to the Arduino board using the required pins (RX, TX, and power).
Insert a working SIM card into the GSM module.
Upload the provided code to the Arduino board.
Configure the code by setting the user's phone number and desired thresholds for alerts.
Power the system using a 12V power supply.

**Usage**

Once the system is set up and powered on, it will continuously monitor the pH, water level, and temperature values with a delay of 10 sec. If any of these values go beyond the set thresholds, the system will send an SMS alert to the user's phone number, indicating which parameter has exceeded the threshold.
The current readings for all parameters are also displayed on the serial monitor for real-time monitoring.

**Customization**

The code can be easily customized to suit your specific needs. You can adjust the thresholds for alerts, modify the SMS message content, or add additional functionalities as per your requirements

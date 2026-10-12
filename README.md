# Task 02: Timers and Non-Blocking Code

## Project Overview
This project uses an Arduino Uno, an HC-SR04 ultrasonic sensor, and an LED. The sensor measures the distance to an object, and the LED responds to the measured distance.

## Components
- Arduino Uno
- HC-SR04 ultrasonic distance sensor
- LED
- 220-ohm resistor
- Jumper wires

## Pin Connections
- HC-SR04 VCC → Arduino 5V
- HC-SR04 GND → Arduino GND
- HC-SR04 TRIG → Digital Pin 3
- HC-SR04 ECHO → Digital Pin 2
- Arduino Digital Pin 8 → 220-ohm resistor → LED anode (+)
- LED cathode (-) → GND

## Timing
- Sensor measurement interval: 200 milliseconds
- Serial status interval: 1000 milliseconds
- `millis()` is used to schedule tasks without using `delay()` in the main loop.

## Expected Behaviour
- If a valid sensor reading is 20 cm or less, the LED turns ON.
- If the object is farther away, the LED turns OFF.
- Distance and status messages are printed to the Serial Monitor.

## Tools
- Arduino C++
- Wokwi Arduino Simulator
- GitHub

## Author
Mathavi E

## Note
The current implementation uses `pulseIn()` with a timeout for ultrasonic measurement. This function can block briefly. A fully non-blocking version should use a non-blocking echo measurement approach.

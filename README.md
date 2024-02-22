# Pawblo-Pro
Introducing Pawblo Pro: your versatile robotic pet companion, perfect for today's smart home. Pawblo transforms your space into a hub of positivity, bringing both playfulness and purpose.

## Inspiration

Home pets

## What it does

Can be toggled to move based on user-based joystick direction
Performs tricks (spinning around, wags tail) based on user's hand gestures
Serves as runaway alarm clock in the morning by backing away (wags tail after caught by user)
Displays daily schedule and reminders on LCD Display (in idle mode), and the distance from user to robot (while in motion)

## How we built it

Facilitated an effective wireless communication between ESP32 and ESP8266 to control the wheels/ wheel motors based on the user's hand gestures
Used Python OpenCV library to develop an algorithm capable of recognizing hand gestures (through the PC's camera)
Used Pyserial to communicate between the Python and Arduino code
Integrated communication between three microcontrollers (Arduino Uno, ESP32, ESP8266) using ESP NOW WiFi connection - between ESP32 and ESP8266, enabling the transmission of several variables, and between ESP 8266 and Arduino, enabling signals for motors and display
Used ultrasonic sensor to back the robot away from approaching user by powering motors to drive wheels
Employed LCD display to show approximate distance between user and robot from ultrasonic sensor (while in motion), and flash important reminders for the user
Used a touch sensor for user to turn the alarm off, and turn on/rotate the large servo motor to simulate a pet wagging its tail

## Challenges we ran into

Received components (hobby motors) without gears, causing disconnection with the gear box and inability to power the wheels
Integrating Pyserial due to the challenging nature of Windows development environment (managing Python packages and libraries)
Computer failure while attempting to detect driver for ESP 8266 connection

## Accomplishments that we're proud of

Employing multiple microcontrollers to communicate data (Arduino Uno, ESP32, ESP8266)
Successfully creating an algorithm to read hand gestures through a PC camera
Utilizing multiple sensors as inputs to analyze sets of data

## What we learned

How to develop a communication system from scratch, enabling usage of microcontrollers for a singular robot
How to plan out and design an organized circuit to integrate multiple sensors, microcontrollers and displays on a singular chassis
How to efficiently divide workload between team members, enabling each member to execute tasks related to personal skills and interests

## What's next for Pawblo Pro

Adding phone slot on the top of the chassis for user to place (as alarm clock)
Using additional sensors to detect objects and prevent collision (to run away more effectively)
Using a portable or phone camera to detect gestures instead of PC camera

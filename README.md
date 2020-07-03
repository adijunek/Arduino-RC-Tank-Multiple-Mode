# Arduino RC Tank with Multiple Mode

An arduino based RC Tank with multiple mode ie. Manual, Follow Me, Obstacle Avoidance. This is an upgraded version of my other [repository](https://github.com/adijunek/Aduino-RC-Tank-PWM-DC-motor); adding ultrasonic sensor for autonomous mode and add control to Front Led.

## Manual Mode:
The vehicle movement is fully controlled by RF Remote control (throttle and steer). 

## Follow Me: 
A simple object following mode, using ultrasonic sonar

## Obstacle Avoidance:
Instead of using a servo, I use the vehicle rotation (left/right) to 'look around' when ultrasonic sensor sees obstacle ahead. 

## Transmitter Setting
Set the transmitter mixer as follow:
- CH01: Throttle or Elevator Stick -> for controling Throttle
- CH02: Aileron or Rudder Stick -> for  Steering
- CH03: 3 Position switch -> for switching between modes
- CH04: 2 Position switch -> to control Front Led On/Off
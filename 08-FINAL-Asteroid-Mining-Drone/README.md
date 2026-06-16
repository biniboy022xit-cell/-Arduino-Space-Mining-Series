# Project 8: Asteroid Mining Drone Simulator (FINAL)

## Mission
A fully autonomous mining drone operating in the asteroid belt must navigate, scan for resources, monitor power, and handle emergencies — all without human intervention. This is the **culmination of all 7 previous projects** integrated into one complete system.

## System Overview
| Subsystem | Component | Function |
|-----------|-----------|----------|
| Navigation | Ultrasonic | Obstacle detection & avoidance |
| Steering | Servo | Direction control |
| Mineral Detection | Photoresistor | Resource scanning |
| Power Monitoring | Potentiometer | Battery simulation |
| Status | 3 LEDs | Visual feedback (Green/Yellow/Red) |
| Alerts | Buzzer | Audio warnings |
| Display | LCD | Telemetry & status |
| **State Machine** | **Arduino Logic** | **NAVIGATING → SCANNING → EMERGENCY** |


## Components Used
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| HC-SR04 Ultrasonic | 1 |
| SG90 Servo | 1 |
| Photoresistor | 1 |
| 10kΩ Resistor | 1 |
| Potentiometer | 1 |
| Push Button | 1 |
| Green LED | 1 |
| Yellow LED | 1 |
| Red LED | 1 |
| 220Ω Resistors | 3 |
| Passive Buzzer | 1 |
| LCD 1602 I2C | 1 |
| Breadboard | 1 |
| Jumper Wires | As needed |

## Status
✅ Complete

## Files
- [code.ino](./code.ino) - Full integrated sketch
- [wiring.md](./wiring.md) - Complete pin mapping
- [demo-video.mp4](./demo-video.mp4) - Demonstration video
- [photos/](./photos/)- wiring image

## Key Learnings (All Projects Combined)
- Full system integration
- Multi-sensor fusion (ultrasonic, photoresistor, potentiometer, button)
- State machine architecture (NAVIGATING/SCANNING/EMERGENCY)
- Non-blocking timing with `millis()`
- Real-time decision making
- Complete telemetry reporting
- Hardware/software co-design

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Servo jittering | Add 100µF capacitor across 5V/GND |
| Photoresistor not detecting minerals | Re-run calibration (hold black paper for baseline) |
| Button not working | Check wiring: GND to one leg, Pin 2 to opposite diagonal |
| LCD flickering | Reduce `delay()` in main loop |
| System resets | Servo may be stalled; keep movement free |

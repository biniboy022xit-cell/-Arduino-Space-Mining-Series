# Project 4: Autonomous Drone Controller

## Mission
A mining drone navigating an asteroid field must detect and avoid obstacles without human intervention. This system simulates autonomous navigation using ultrasonic sensing and servo-based steering.

## How It Works
- Ultrasonic sensor continuously measures forward distance
- 3-state finite state machine: **MOVING → STOPPED → TURNING**
- Servo motor simulates steering (straight/left/right)
- LED indicators: Green (moving), Yellow (turning), Red (stopped)
- Buzzer provides audio feedback for different events
- LCD shows distance and current state

## State Machine Diagram
┌─────────────┐
│ MOVING │
│ (Forward) │
└──────┬──────┘
│ Obstacle < 8cm
▼
┌─────────────┐
│ STOPPED │
│(Emergency) │
└──────┬──────┘
│ After 500ms
▼
┌─────────────┐
│ TURNING │
│(Avoiding) │
└──────┬──────┘
│ After 800ms
▼
┌─────────────┐
│ MOVING │
│ (Forward) │
└─────────────┘


## Components Used
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| SG90 Servo Motor | 1 |
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
- [code.ino](./code.ino) - Arduino sketch
- [wiring.md](./wiring.md) - Pin connections
- [demo-video.mp4](./demo-video.mp4) - Demonstration video

## Key Learnings
- Finite state machine (FSM) design
- Non-blocking timing with `millis()`
- Servo motor control with `Servo.h`
- Multi-sensor integration (ultrasonic + servo + LEDs + buzzer)
- Real-time decision making

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Servo jitters | Add 100µF capacitor across 5V/GND near servo |
| Arduino resets on servo movement | Servo may be stalled; keep movement free |
| Yellow LED never lights | Check state transition logic (fixed in code) |
| Red LED never lights | Verify STOPPED state is reached (code includes it) |

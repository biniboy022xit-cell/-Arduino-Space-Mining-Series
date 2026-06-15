# Project 1: Asteroid Proximity Scanner

## Mission
A mining drone approaching an asteroid needs real-time distance detection to avoid collision with the surface.

## How It Works
- Ultrasonic sensor (HC-SR04) measures distance from 2cm to 400cm
- 3 alert levels with visual and audio feedback:
  - **Green LED**: >100cm (safe approach)
  - **Yellow LED**: 50-100cm (caution zone)
  - **Red LED + Buzzer**: <20cm (collision imminent)
- LCD displays current distance and mission status
- Real-time response time under 100ms

## Components Used
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
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
- [photos/](./photos/) - Breadboard and demo images
- [demo1.mp4](./demo1.mp4)  and [demo2.mp4](./demo2.mp4) - 2 Video demonstrations

## Key Learnings
- Ultrasonic distance measurement using `pulseIn()`
- Threshold-based alert systems
- Real-time sensor feedback loops
- LCD display formatting with I2C
- Non-blocking code structure

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Sensor reads 0cm | Check TRIG/ECHO pins aren't swapped |
| LCD shows nothing | Verify I2C address (0x27 or 0x3F) |
| LEDs too dim | Confirm 220Ω resistors are used |

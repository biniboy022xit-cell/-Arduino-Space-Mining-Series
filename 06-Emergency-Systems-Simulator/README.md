# Project 6: Emergency Systems Simulator

## Mission
An asteroid mining base experiences a critical failure — oxygen leak, hull breach, or equipment malfunction. This system simulates emergency detection, alarm, and recovery protocols.

## How It Works
- Push button toggles between NORMAL and EMERGENCY states
- Red LED + buzzer activate during emergencies
- LCD shows evacuation instructions and elapsed time
- Event logging to Serial Monitor for post-mission review
- State machine: NORMAL ↔ EMERGENCY

## System States
| State | LED | Buzzer | LCD |
|-------|-----|--------|-----|
| NORMAL | Green | Silent | "ALL SYSTEMS NOMINAL" |
| EMERGENCY | Red | Siren pattern | "EVACUATE AREA" |

## Emergency Scenarios
This simulator can represent:
- Oxygen leak (life support failure)
- Hull breach (pressure loss)
- Fire (electrical or chemical)
- Toxic gas (propellant leak)

## Components Used
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| Push Button | 1 |
| RGB LED (or Green + Red LEDs) | 1 |
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
- [System-video.mp4](./System-video.mp4) - Demonstration video

## Key Learnings
- Push button with internal pull-up (`INPUT_PULLUP`)
- Button debouncing techniques
- State machine design (NORMAL/EMERGENCY)
- Non-blocking alarm patterns
- Event logging with timestamps
- System reset logic

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Button press not detected | Check wiring: GND to one leg, Pin 2 to opposite diagonal leg |
| Emergency triggers randomly | Add debounce delay (included in code) |
| Buzzer pattern wrong | Check polarity (+ to Pin 8, - to GND) |
| LCD shows "EMERGENCY" but no sound | Verify `updateEmergencyAlarm()` is called |

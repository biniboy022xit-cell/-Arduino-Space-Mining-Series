# Project 7: Power Management System

## Mission
A mining drone operates on battery power. Mission control needs real-time battery status and automatic warnings before power failure. This system simulates battery monitoring with escalating alerts.

## How It Works
- Potentiometer controls simulated battery level (0-100%)
- 3 LED indicators: Green (good), Yellow (low), Red (critical)
- Buzzer sounds when battery is critically low
- LCD shows battery percentage with visual bar
- Telemetry reports to Serial Monitor

## Battery Zones
| Battery % | LED | Status | Buzzer |
|-----------|-----|--------|--------|
| 70-100% | Green | NOMINAL | Silent |
| 30-69% | Yellow | LOW POWER | One short beep (entry) |
| 0-29% | Red | CRITICAL | Beeps every 5 sec |
| 0-14% | Red | CRITICAL URGENT | Beeps every 1 sec |

## What It Simulates
- Battery voltage monitoring (spacecraft power systems)
- Reserve power management
- Critical failure prevention
- Mission control energy awareness

## Components Used
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| Potentiometer (10kΩ) | 1 |
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
- [power-video.mp4](./power-video.mp4) - Demonstration video

## Key Learnings
- Analog signal mapping for percentage display
- Visual battery bar implementation
- Dynamic alert intervals (non-blocking timing)
- Threshold-based escalation
- Telemetry data formatting

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Battery % jumps erratically | Check potentiometer connections (GND, A1, 5V) |
| LCD bar doesn't match percentage | Verify `map()` function in `updateLCD()` |
| Buzzer beeps too fast/slow | Adjust `BEEP_INTERVAL_NORMAL` and `BEEP_INTERVAL_URGENT` |
| Entering emergency state | Expected behavior below 30% (critical zone) |

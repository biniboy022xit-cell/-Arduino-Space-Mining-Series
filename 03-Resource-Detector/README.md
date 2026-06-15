# Project 3: Asteroid Resource Detector

## Mission
A mining drone needs to identify valuable minerals on asteroid surfaces without bringing samples back to Earth. This system uses light reflection to detect different "minerals" (simulated by colored paper).

## How It Works
- Photoresistor measures light reflected from surface materials
- Different colors = different minerals (water ice, platinum, iron ore, basalt, silicates)
- RGB LED changes color to match detected mineral
- LCD shows mineral name and "VALUABLE" indicator
- Buzzer chirps when valuable resource (water ice or platinum) is found

## Components Used
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| Photoresistor | 1 |
| 10kΩ Resistor | 1 |
| RGB LED (Common Cathode) | 1 |
| 220Ω Resistors | 3 |
| Passive Buzzer | 1 |
| LCD 1602 I2C | 1 |
| Breadboard | 1 |
| Jumper Wires | As needed |

## Calibration Required
This system uses **relative difference** detection, not absolute values. It works in any lighting condition by:
1. Taking a baseline reading (black paper)
2. Measuring change from baseline (difference)
3. Mapping difference to mineral type

**Night mode included** — works with room lighting or bulb.

## Status
✅ Complete

## Files
- [code.ino](./code.ino) - Arduino sketch (night mode version)
- [wiring.md](./wiring.md) - Pin connections
- [demo-video.mp4](./demo-video.mp4) - Demonstration video
- [calibration-guide.md](./calibration-guide.md) - How to adjust thresholds

## Key Learnings
- Analog sensor reading with `analogRead()`
- Threshold-based classification
- Relative vs absolute measurements (adapts to environment)
- RGB color mixing with PWM
- Real-time user feedback design

## Troubleshooting
| Issue | Solution |
|-------|----------|
| All minerals read as "Unknown" | Re-run calibration (hold black paper first) |
| RGB LED wrong color | Check common cathode connected to GND |
| Buzzer too quiet | Check polarity (+ to pin 8, - to GND) |

# Project 5: Mission Control Data Relay

## Mission
A mining drone operating in deep space needs to transmit data back to Earth. Signal strength varies due to distance, solar interference, and asteroid obstruction. This system simulates a communication link with variable signal quality.

## How It Works
- Potentiometer controls signal strength (0-100%)
- 3 LED indicators: Green (good), Yellow (weak), Red (signal lost)
- Buzzer sounds when signal is lost
- LCD shows signal percentage and transmission status
- Serial Monitor logs data packets sent and lost

## Signal Zones
| Signal % | LED | Status | Data Reliability |
|----------|-----|--------|------------------|
| 70-100% | Green | TRANSMITTING | 100% success |
| 30-69% | Yellow | WEAK SIGNAL | 70% success (30% packet loss) |
| 0-29% | Red | LOST | 0% success |

## What It Simulates
- Deep space communication delay
- Packet loss in weak signal conditions
- Emergency alerts for signal failure
- Mission control telemetry

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
- [data-relay-video.mp4](./data-relay-video.mp4) - Demonstration video

## Key Learnings
- Analog input mapping (`map()` function)
- Signal-to-noise simulation
- Packet loss modeling with `random()`
- Real-time telemetry reporting
- Data integrity monitoring

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Signal stuck at 0% | Check potentiometer wiring (GND, A0, 5V) |
| LCD shows wrong percentage | Verify `map()` function range (0-1023 → 0-100) |
| No packet loss in yellow zone | Check `random()` logic (30% chance simulated) |

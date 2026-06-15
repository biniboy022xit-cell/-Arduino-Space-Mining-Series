# Project 2: Lunar Base Life Support

## Status: ⏸️ ON HOLD

**Reason:** DHT11 sensor was damaged during prototyping (overheating issue).

**Root cause:** Polarity issue during wiring (VCC/GND reversed briefly).

**Lesson learned:** 
- Always double-check wiring before powering on
- Touch sensors to check for abnormal heat
- Order spare sensors for development

**Replacement ordered:** DS18B20 waterproof temperature sensor (arriving 2-4 weeks)

**Expected completion:** When replacement sensor arrives

---

## Mission (When Completed)
A lunar mining base requires constant environmental monitoring. Temperature swings on the Moon range from -173°C to +127°C — life support must detect failures immediately.

## Planned Features
- Real-time temperature monitoring
- RGB LED status indicator (Green = normal, Yellow = warning, Red = critical)
- Audio alerts for out-of-range conditions
- LCD display with mission control telemetry

## Components (When Completed)
| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| DS18B20 Waterproof Sensor | 1 |
| RGB LED (Common Cathode) | 1 |
| 220Ω Resistors | 3 |
| Passive Buzzer | 1 |
| LCD 1602 I2C | 1 |

## What I Learned From This Failure
1. **Symptoms of a fried sensor:** Unusually hot to touch, always returns `nan` or 0 readings
2. **Diagnosis method:** Run minimal test code to isolate the problem
3. **Prevention:** Connect GND first, then VCC; use breadboard power switch
4. **Recovery:** Order replacements, continue with other projects while waiting

## Files (Partial - Awaiting Sensor)
- [planned-code.ino](./planned-code.ino) - Code structure (ready for sensor)
- [wiring.md](./wiring.md) - Pin mapping (ready)
- [demo-pending.mp4](./demo-pending.mp4) - Will record when sensor arrives

## Key Skills Demonstrated (Even Without Hardware)
- Problem diagnosis
- Root cause analysis
- Failure documentation
- Project management (pivot, don't stop)

## Resume Bullet Point
*"Debugged hardware failure in temperature sensing system — diagnosed fried DHT11 via thermal detection and isolation testing, ordered replacement, documented root cause."*

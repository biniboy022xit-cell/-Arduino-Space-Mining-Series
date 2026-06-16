# Wiring Diagram - Project 1

## Pin Mapping Table

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **Ultrasonic HC-SR04** | VCC | 5V |
| | TRIG | 6 |
| | ECHO | 7 |
| | GND | GND |
| **Green LED** | Anode (+) | 9 |
| | Cathode (-) | GND (via 220Ω) |
| **Yellow LED** | Anode (+) | 10 |
| | Cathode (-) | GND (via 220Ω) |
| **Red LED** | Anode (+) | 11 |
| | Cathode (-) | GND (via 220Ω) |
| **Buzzer** | Positive (+) | 8 |
| | Negative (-) | GND |
| **LCD 1602 I2C** | VCC | 5V |
| | GND | GND |
| | SDA | A4 |
| | SCL | A5 |

## Power Notes
- All LEDs require 220Ω current-limiting resistors
- LCD uses I2C protocol (only 4 wires)
- Ultrasonic sensor operates at 5V
- Total current draw: ~150mA (safe for USB power)

## Visual Reference
See `photos/` for wiring and monitoring photos

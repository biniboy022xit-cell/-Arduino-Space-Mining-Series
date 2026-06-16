# Wiring Diagram - Project 7

## Pin Mapping Table

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **Potentiometer** | Left | GND |
| | Middle | A1 |
| | Right | 5V |
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
- Total current draw: ~100mA
- Safe for USB power
- This system simulates a battery; the actual Arduino is still USB-powered

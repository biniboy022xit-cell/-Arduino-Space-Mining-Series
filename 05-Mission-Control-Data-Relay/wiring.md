# Wiring Diagram - Project 5

## Pin Mapping Table

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **Potentiometer** | Left | GND |
| | Middle | A0 |
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

## How the Potentiometer Works
- Left pin: Ground reference
- Right pin: 5V reference
- Middle pin: Voltage divider output (0V to 5V)
- Arduino reads analog voltage (0-1023)
- Mapped to 0-100% signal strength

## Power Notes
- Total current draw: ~100mA
- Safe for USB power

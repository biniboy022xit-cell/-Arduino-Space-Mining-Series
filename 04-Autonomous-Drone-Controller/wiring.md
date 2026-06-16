# Wiring Diagram - Project 4

## Pin Mapping Table

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **Ultrasonic HC-SR04** | VCC | 5V |
| | TRIG | 6 |
| | ECHO | 7 |
| | GND | GND |
| **Servo SG90** | Brown/Black (GND) | GND |
| | Red (VCC) | 5V |
| | Orange/Yellow (Signal) | 5 |
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
- Servo draws significant current (up to 160mA when moving)
- If Arduino resets, add 100µF capacitor across 5V/GND
- All LEDs use 220Ω current-limiting resistors
- Total current draw: ~250-350mA

## Visual Reference
See `photos/breadboard.jpg` for wiring photo

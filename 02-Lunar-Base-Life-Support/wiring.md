# Wiring Diagram - Project 2 (Planned)

## Pin Mapping Table (Ready for DS18B20)

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **DS18B20** | VCC | 5V |
| (Waterproof) | DATA | 2 |
| | GND | GND |
| | (Pull-up resistor) | 4.7kΩ between DATA and VCC |
| **RGB LED** | Red | 9 |
| (Common Cathode) | Green | 10 |
| | Blue | 11 |
| | Common (longest) | GND |
| **Buzzer** | Positive (+) | 8 |
| | Negative (-) | GND |
| **LCD 1602 I2C** | VCC | 5V |
| | GND | GND |
| | SDA | A4 |
| | SCL | A5 |

## Notes
- DS18B20 requires a 4.7kΩ pull-up resistor between DATA and VCC
- RGB LED uses 220Ω resistors on each color pin
- Total planned current: ~120mA

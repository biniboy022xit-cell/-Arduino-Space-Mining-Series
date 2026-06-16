# Wiring Diagram - Project 6

## Pin Mapping Table

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **Push Button** | One leg | GND |
| | Opposite leg (diagonal) | 2 |
| **Green LED** | Anode (+) | 10 |
| | Cathode (-) | GND (via 220Ω) |
| **Red LED** | Anode (+) | 9 |
| | Cathode (-) | GND (via 220Ω) |
| **RGB LED Alternative** | Red | 9 |
| (Common Cathode) | Green | 10 |
| | Blue | Not used |
| | Common (longest) | GND |
| **Buzzer** | Positive (+) | 8 |
| | Negative (-) | GND |
| **LCD 1602 I2C** | VCC | 5V |
| | GND | GND |
| | SDA | A4 |
| | SCL | A5 |


## Power Notes
- Total current draw: ~100mA
- Safe for USB power
- Button uses internal pull-up resistor (`INPUT_PULLUP`)

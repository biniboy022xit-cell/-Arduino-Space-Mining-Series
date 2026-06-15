# Wiring Diagram - Project 3

## Pin Mapping Table

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| **Photoresistor** | One leg | 5V |
| | Other leg | A0 AND 10kΩ to GND |
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

## Resistor Values
| Resistor | Value | Location |
|----------|-------|----------|
| R1 | 10kΩ | Between A0 and GND (voltage divider) |
| R2 | 220Ω | RGB LED Red pin to Arduino pin 9 |
| R3 | 220Ω | RGB LED Green pin to Arduino pin 10 |
| R4 | 220Ω | RGB LED Blue pin to Arduino pin 11 |

## How the Photoresistor Circuit Works
5V ──┬── Photoresistor ── A0
|
│
└── 10kΩ Resistor ── GND


This creates a voltage divider. As light increases, photoresistor resistance decreases, voltage at A0 increases.

## Power Notes
- Total current draw: ~80mA (all LEDs on white)
- Safe for USB power


# Calibration Guide

## How to Adjust Thresholds for Your Lighting

The code uses these ranges:

```cpp
if (difference < 20) return -1;      // No signal
else if (difference < 60) return 3;   // Basalt (grey)
else if (difference < 120) return 2;  // Iron Ore (red)
else if (difference < 200) return 1;  // Platinum (gold)
else return 4;                         // Silicates (white)

To Calibrate for Your Environment:
    Upload the code
    Open Serial Monitor (9600 baud)
    Hold black paper in front of sensor → note the DIFF value (should be near 0)
    Hold grey paper → note the DIFF value
    Hold red paper → note the DIFF value
    Hold yellow/gold paper → note the DIFF value
    Hold white paper → note the DIFF value

/*
 * NIGHT MODE - Resource Detector(optional)
 * Uses relative differences instead of absolute values
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PHOTORESISTOR_PIN A0
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11
#define BUZZER_PIN 8

LiquidCrystal_I2C lcd(0x27, 16, 2);

int baselineValue = 0;
int lightValue = 0;
int lastStableValue = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  // Quick intro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NIGHT MODE");
  lcd.setCursor(0, 1);
  lcd.print("RESOURCE SCANNER");
  delay(1500);
  
  // Set baseline (hold sensor against black paper first)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hold against");
  lcd.setCursor(0, 1);
  lcd.print("BLACK paper...");
  delay(3000);
  
  baselineValue = analogRead(PHOTORESISTOR_PIN);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Baseline set:");
  lcd.setCursor(0, 1);
  lcd.print(baselineValue);
  delay(1500);
  
  Serial.println("=== NIGHT MODE RESOURCE DETECTOR ===");
  Serial.print("Baseline: ");
  Serial.println(baselineValue);
}

void loop() {
  // Read current value
  lightValue = analogRead(PHOTORESISTOR_PIN);
  
  // Calculate difference from baseline
  int difference = lightValue - baselineValue;
  
  // Determine mineral based on difference
  String mineral = "";
  int red = 0, green = 0, blue = 0;
  bool valuable = false;
  
  if (difference < 10) {
    mineral = "No Signal";
    red = 80; green = 80; blue = 80;  // Grey
  }
  else if (difference >= 10 && difference < 50) {
    mineral = "Basalt";
    red = 80; green = 80; blue = 80;
    valuable = false;
  }
  else if (difference >= 50 && difference < 120) {
    mineral = "Iron Ore";
    red = 255; green = 0; blue = 0;
    valuable = false;
  }
  else if (difference >= 120 && difference < 250) {
    mineral = "Platinum";
    red = 255; green = 215; blue = 0;
    valuable = true;
  }
  else if (difference >= 250) {
    mineral = "Water Ice";
    red = 0; green = 0; blue = 255;
    valuable = true;
  }
  
  // Update display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SIG:");
  lcd.print(lightValue);
  lcd.print(" DIF:");
  lcd.print(difference);
  
  lcd.setCursor(0, 1);
  if (mineral == "No Signal") {
    lcd.print("SCANNING...");
  } else {
    lcd.print(mineral);
    if (valuable) lcd.print(" *VALUABLE*");
  }
  
  // Update RGB LED
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_BLUE, blue);
  
  // Alert if valuable
  if (valuable && difference != lastStableValue) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(80);
    digitalWrite(BUZZER_PIN, LOW);
    delay(80);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(80);
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  lastStableValue = difference;
  
  // Serial debug
  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print(" | Diff: ");
  Serial.print(difference);
  Serial.print(" | Mineral: ");
  Serial.println(mineral);
  
  delay(300);
}

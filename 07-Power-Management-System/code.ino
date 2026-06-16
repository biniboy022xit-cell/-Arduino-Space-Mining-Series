/*
 * POWER MANAGEMENT SYSTEM
 * Battery level monitor for asteroid mining drone
 * Engineer: Matibini Handiya
 * 
 * Potentiometer simulates battery voltage (0-100%)
 * Green = good (70-100%)
 * Yellow = low (30-69%)
 * Red = critical (0-29%) + alarm
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define POT_PIN A0
#define LED_GREEN 9
#define LED_YELLOW 10
#define LED_RED 11
#define BUZZER_PIN 8

// Battery thresholds (%)
const int CRITICAL_THRESHOLD = 30;   // Below 30% = critical
const int LOW_THRESHOLD = 70;         // Below 70% = low (yellow)
// 70-100% = good (green)

// Timing for beep pattern
unsigned long lastBeepTime = 0;
const int BEEP_INTERVAL_NORMAL = 5000;   // Beep every 5 seconds when critical
const int BEEP_INTERVAL_URGENT = 1000;   // Beep every 1 second when below 15%

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
int batteryPercent = 100;
int lastPercent = -1;

void setup() {
  Serial.begin(9600);
  
  // LED pins
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  
  // LCD
  lcd.init();
  lcd.backlight();
  
  // Mission start screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("POWER MANAGEMENT");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM ONLINE");
  delay(2000);
  
  Serial.println("=== POWER MANAGEMENT SYSTEM ===");
  Serial.println("Status: ONLINE");
  Serial.println("70-100%: Green | 30-69%: Yellow | 0-29%: Red + Alarm");
  Serial.println("=================================");
}

void loop() {
  // Read potentiometer (0-1023) and convert to percentage (0-100)
  int rawValue = analogRead(POT_PIN);
  batteryPercent = map(rawValue, 0, 1023, 0, 100);
  
  // Update LEDs based on battery level
  updateLEDs();
  
  // Update LCD display
  updateLCD();
  
  // Handle critical battery alarm
  handleCriticalAlarm();
  
  // Send telemetry to Serial Monitor
  sendTelemetry();
  
  delay(200);  // Update 5 times per second
}

void updateLEDs() {
  if (batteryPercent >= LOW_THRESHOLD) {
    // Good battery (70-100%) - Green only
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  }
  else if (batteryPercent >= CRITICAL_THRESHOLD) {
    // Low battery (30-69%) - Yellow only
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  else {
    // Critical battery (0-29%) - Red only
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  }
}

void updateLCD() {
  lcd.clear();
  
  // Row 1: Battery percentage
  lcd.setCursor(0, 0);
  lcd.print("BATTERY: ");
  lcd.print(batteryPercent);
  lcd.print("%");
  
  // Battery bar (visual)
  lcd.setCursor(11, 0);
  int bars = map(batteryPercent, 0, 100, 0, 5);
  for (int i = 0; i < bars; i++) {
    lcd.print("|");
  }
  for (int i = bars; i < 5; i++) {
    lcd.print(".");
  }
  
  // Row 2: Status message
  lcd.setCursor(0, 1);
  if (batteryPercent >= LOW_THRESHOLD) {
    lcd.print("NOMINAL       ");
  }
  else if (batteryPercent >= CRITICAL_THRESHOLD) {
    lcd.print("LOW POWER     ");
  }
  else {
    lcd.print("*** CRITICAL ***");
  }
}

void handleCriticalAlarm() {
  if (batteryPercent < CRITICAL_THRESHOLD) {
    // Critical battery alarm
    // Determine beep interval (more urgent as battery drops)
    int beepInterval;
    if (batteryPercent < 15) {
      beepInterval = BEEP_INTERVAL_URGENT;   // Fast beeps
    } else {
      beepInterval = BEEP_INTERVAL_NORMAL;   // Slow beeps
    }
    
    unsigned long currentTime = millis();
    if (currentTime - lastBeepTime >= beepInterval) {
      lastBeepTime = currentTime;
      
      // Beep pattern: two short beeps for critical
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      
      Serial.print("🔋 CRITICAL BATTERY: ");
      Serial.print(batteryPercent);
      Serial.println("% - RECHARGE IMMEDIATELY");
    }
  }
  else if (batteryPercent >= CRITICAL_THRESHOLD && batteryPercent < LOW_THRESHOLD) {
    // Low battery warning - single short beep once
    static bool lowBeepDone = false;
    if (!lowBeepDone) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(80);
      digitalWrite(BUZZER_PIN, LOW);
      lowBeepDone = true;
    }
  }
  else {
    // Normal battery - reset beep flag
    static bool lowBeepDone = false;
    lowBeepDone = false;
  }
}

void sendTelemetry() {
  if (batteryPercent != lastPercent) {
    Serial.print("📊 TELEMETRY | Battery: ");
    Serial.print(batteryPercent);
    Serial.print("% | Status: ");
    
    if (batteryPercent >= LOW_THRESHOLD) {
      Serial.println("NOMINAL");
    }
    else if (batteryPercent >= CRITICAL_THRESHOLD) {
      Serial.println("LOW POWER");
    }
    else {
      Serial.println("CRITICAL");
    }
    
    lastPercent = batteryPercent;
  }
}

/*
 * ASTEROID MINING DRONE SIMULATOR - FINAL PROJECT
 * Complete integration of all systems
 * Engineer: Matibini Handiya
 * 
 * Features:
 * - Autonomous navigation (obstacle avoidance)
 * - Mineral scanning & detection
 * - Battery monitoring
 * - Emergency system (button + low battery)
 * - Mission control telemetry
 * - LCD display
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ========== PIN DEFINITIONS ==========
// Ultrasonic
#define TRIG_PIN 6
#define ECHO_PIN 7

// Servo
#define SERVO_PIN 5

// Sensors
#define PHOTO_PIN A0
#define POT_PIN A1

// Button
#define BUTTON_PIN 2

// LEDs
#define LED_GREEN 9
#define LED_YELLOW 10
#define LED_RED 11

// Buzzer
#define BUZZER_PIN 8

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo scannerServo;

// ========== SYSTEM STATES ==========
enum DroneState { 
  NAVIGATING,      // Moving forward, avoiding obstacles
  SCANNING,        // Stopped, scanning for minerals
  EMERGENCY        // Critical failure
};
DroneState state = NAVIGATING;

// ========== THRESHOLDS ==========
const int OBSTACLE_DISTANCE = 15;     // cm - obstacle detection
const int MINERAL_THRESHOLD = 100;    // Photoresistor value for "valuable"
const int BATTERY_CRITICAL = 30;      // Percentage

// ========== VARIABLES ==========
int distance = 0;
int mineralValue = 0;
int batteryPercent = 100;
bool emergencyTriggered = false;
unsigned long scanStartTime = 0;
unsigned long lastBeepTime = 0;
int valuableCount = 0;

// Button debouncing variables
int lastButtonState = HIGH;     // Previous button state
int buttonState = HIGH;         // Current button state
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;

// ========== SETUP ==========
void setup() {
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Servo
  scannerServo.attach(SERVO_PIN);
  scannerServo.write(90);  // Center position
  
  // LCD
  lcd.init();
  lcd.backlight();
  
  // Mission start
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ASTEROID MINING");
  lcd.setCursor(0, 1);
  lcd.print("DRONE v4.0");
  delay(2000);
  
  Serial.println("=========================================");
  Serial.println("ASTEROID MINING DRONE SIMULATOR - ONLINE");
  Serial.println("Systems: NAV | SCAN | EMERG");
  Serial.println("=========================================");
  
  // Startup beep
  startupBeep();
}

// ========== MAIN LOOP ==========
void loop() {
  // Read all sensors
  readSensors();
  
  // Handle button press (emergency)
  handleButton();
  
  // Update based on current state
  switch(state) {
    case NAVIGATING:
      updateNavigating();
      break;
    case SCANNING:
      updateScanning();
      break;
    case EMERGENCY:
      updateEmergency();
      break;
  }
  
  // Update LEDs based on battery
  updateBatteryLEDs();
  
  // Update LCD display
  updateLCD();
  
  // Send telemetry
  sendTelemetry();
  
  delay(100);
}

// ========== SENSOR READINGS ==========
void readSensors() {
  // Ultrasonic distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration > 0) {
    distance = duration * 0.0343 / 2;
  } else {
    distance = 999;
  }
  
  // Mineral scanner (photoresistor)
  mineralValue = analogRead(PHOTO_PIN);
  
  // Battery level (potentiometer)
  int rawBattery = analogRead(POT_PIN);
  batteryPercent = map(rawBattery, 0, 1023, 0, 100);
}

// ========== NAVIGATING STATE ==========
void updateNavigating() {
  // Check battery first
  if (batteryPercent < BATTERY_CRITICAL) {
    state = EMERGENCY;
    emergencyTriggered = true;
    Serial.println("⚠️ BATTERY CRITICAL - Entering emergency mode");
    return;
  }
  
  // Check for obstacles
  if (distance < OBSTACLE_DISTANCE && distance > 0) {
    // Obstacle detected! Stop and scan for minerals
    state = SCANNING;
    scanStartTime = millis();
    
    // Scan left and right
    scannerServo.write(45);   // Turn to scan left
    delay(500);
    scannerServo.write(135);  // Turn to scan right
    delay(500);
    scannerServo.write(90);   // Return to center
    
    Serial.print("🪨 Obstacle at ");
    Serial.print(distance);
    Serial.println("cm - Scanning for minerals");
    
    // Obstacle beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    // No obstacle - normal navigation
    scannerServo.write(90);  // Center
  }
}

// ========== SCANNING STATE ==========
void updateScanning() {
  // Check for valuable minerals
  if (mineralValue > MINERAL_THRESHOLD) {
    valuableCount++;
    Serial.print("💰 VALUABLE MINERAL DETECTED! (Signal: ");
    Serial.print(mineralValue);
    Serial.println(")");
    
    // Celebration pattern
    for(int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  } else {
    // No valuable mineral - single beep
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  // Scan for 2 seconds then return to navigation
  if (millis() - scanStartTime > 2000) {
    state = NAVIGATING;
    Serial.println("Scan complete - Resuming navigation");
  }
}

// ========== EMERGENCY STATE ==========
void updateEmergency() {
  // Red LED + buzzer pattern
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);
  
  unsigned long currentTime = millis();
  if (currentTime - lastBeepTime > 500) {
    lastBeepTime = currentTime;
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  // Emergency message on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!!! EMERGENCY !!!");
  lcd.setCursor(0, 1);
  if (batteryPercent < BATTERY_CRITICAL) {
    lcd.print("LOW BATTERY");
  } else {
    lcd.print("SYSTEM FAILURE");
  }
}

// ========== BUTTON HANDLER ==========
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // Button pressed (LOW because INPUT_PULLUP)
      if (buttonState == LOW) {
        if (state == EMERGENCY) {
          // Reset from emergency
          state = NAVIGATING;
          emergencyTriggered = false;
          Serial.println("✅ Emergency reset - Systems nominal");
          
          // Reset beep
          digitalWrite(BUZZER_PIN, HIGH);
          delay(200);
          digitalWrite(BUZZER_PIN, LOW);
        } else {
          // Manual emergency trigger
          state = EMERGENCY;
          Serial.println("🚨 Manual emergency triggered");
        }
      }
    }
  }
  
  lastButtonState = reading;
}

// ========== BATTERY LEDS ==========
void updateBatteryLEDs() {
  // Don't override if in emergency
  if (state == EMERGENCY) return;
  
  if (batteryPercent > 70) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  } else if (batteryPercent > 30) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  }
}

// ========== LCD DISPLAY ==========
void updateLCD() {
  if (state == EMERGENCY) return;  // Emergency has its own display
  
  lcd.clear();
  
  // Row 1: Distance and Battery
  lcd.setCursor(0, 0);
  lcd.print("D:");
  if (distance > 99) lcd.print("99+");
  else lcd.print(distance);
  lcd.print("cm B:");
  lcd.print(batteryPercent);
  lcd.print("%");
  
  // Row 2: Status and Minerals
  lcd.setCursor(0, 1);
  if (state == SCANNING) {
    lcd.print("SCANNING...");
  } else {
    lcd.print("NAVIGATING");
  }
  
  lcd.setCursor(12, 1);
  lcd.print("M:");
  lcd.print(valuableCount);
}

// ========== TELEMETRY ==========
void sendTelemetry() {
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 3000) {
    Serial.print("📡 TELEM | Dist:");
    Serial.print(distance);
    Serial.print("cm | Bat:");
    Serial.print(batteryPercent);
    Serial.print("% | Minerals:");
    Serial.print(valuableCount);
    Serial.print(" | State:");
    if(state == NAVIGATING) Serial.print("NAV");
    else if(state == SCANNING) Serial.print("SCAN");
    else Serial.print("EMERG");
    Serial.println();
    lastSend = millis();
  }
}

// ========== STARTUP BEEP ==========
void startupBeep() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
}

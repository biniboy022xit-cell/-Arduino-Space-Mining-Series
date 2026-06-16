/*
 * EMERGENCY SYSTEMS SIMULATOR
 * Critical failure alarm for asteroid mining base
 * Engineer: Matibini Handiya
 * 
 * Press button → Emergency triggered (red light, alarm, evacuation LCD)
 * Press again → System reset (green light, all clear)
 * Emergency logs sent to Serial Monitor for mission review
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define BUTTON_PIN 2
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11
#define BUZZER_PIN 8

// System states
enum SystemState { NORMAL, EMERGENCY };
SystemState state = NORMAL;

// Debouncing variables
int lastButtonState = HIGH;     // HIGH = not pressed (pull-up)
int buttonState;
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;

// Emergency logging
int emergencyCount = 0;
unsigned long emergencyStartTime = 0;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  
  // Button pin (internal pull-up resistor)
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // LED pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  
  // LCD
  lcd.init();
  lcd.backlight();
  
  // Mission start screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EMERGENCY SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("v1.0 - ONLINE");
  delay(2000);
  
  // Set normal state
  setStateNormal();
  
  Serial.println("=== EMERGENCY SYSTEMS SIMULATOR ===");
  Serial.println("Status: ONLINE");
  Serial.println("Press button to trigger emergency");
  Serial.println("===================================");
}

void loop() {
  // Read button with debouncing
  int reading = digitalRead(BUTTON_PIN);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // Button pressed (LOW because INPUT_PULLUP)
      if (buttonState == LOW) {
        onButtonPress();
      }
    }
  }
  
  lastButtonState = reading;
  
  // Update emergency alarm (continuous beep in emergency mode)
  if (state == EMERGENCY) {
    updateEmergencyAlarm();
  }
  
  delay(10);  // Small delay for stability
}

void onButtonPress() {
  if (state == NORMAL) {
    // Trigger emergency
    setStateEmergency();
  } else {
    // Reset system (emergency cleared)
    setStateNormal();
  }
}

void setStateNormal() {
  state = NORMAL;
  
  // Green LED on, Red off
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  
  // Buzzer off
  digitalWrite(BUZZER_PIN, LOW);
  
  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALL SYSTEMS");
  lcd.setCursor(0, 1);
  lcd.print("NOMINAL");
  
  Serial.println("✅ EMERGENCY CLEARED - Systems normal");
  Serial.println("===================================");
}

void setStateEmergency() {
  state = EMERGENCY;
  emergencyCount++;
  emergencyStartTime = millis();
  
  // Red LED on, Green off
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  
  // Update LCD with critical message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!!! EMERGENCY !!!");
  lcd.setCursor(0, 1);
  lcd.print("EVACUATE AREA");
  
  // Log to Serial Monitor
  Serial.println("===================================");
  Serial.print("🚨 EMERGENCY #");
  Serial.print(emergencyCount);
  Serial.println(" TRIGGERED!");
  Serial.println("⚠️ Critical failure detected!");
  Serial.println("📢 EVACUATION PROTOCOL ACTIVATED");
  Serial.println("===================================");
}

void updateEmergencyAlarm() {
  // Calculate elapsed emergency duration
  unsigned long emergencyDuration = (millis() - emergencyStartTime) / 1000;
  
  // Siren pattern: fast beeps for first 10 seconds, then slower
  if (emergencyDuration < 10) {
    // Fast siren (200ms on, 200ms off)
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  } else {
    // Slower siren (500ms on, 500ms off)
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  }
  
  // Update LCD with elapsed time every 2 seconds
  static unsigned long lastLCDUpdate = 0;
  if (millis() - lastLCDUpdate > 2000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!!! EMERGENCY !!!");
    lcd.setCursor(0, 1);
    lcd.print("ELAPSED: ");
    lcd.print(emergencyDuration);
    lcd.print("s");
    lastLCDUpdate = millis();
    
    // Log to Serial every 5 seconds
    if (emergencyDuration % 5 == 0 && emergencyDuration > 0) {
      Serial.print("⚠️ Emergency active for ");
      Serial.print(emergencyDuration);
      Serial.println(" seconds");
    }
  }
}

// Optional: Flash red LED in emergency (already handled above)

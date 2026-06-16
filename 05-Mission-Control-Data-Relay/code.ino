/*
 * MISSION CONTROL DATA RELAY
 * Simulates deep-space communication with variable signal strength
 * Engineer: Matibini Handiya
 * 
 * The potentiometer controls signal strength (0-100%).
 * Green = good signal (data transmits)
 * Yellow = weak signal (data may be corrupted)
 * Red = signal lost (alarm sounds)
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define POT_PIN A0
#define LED_GREEN 9
#define LED_YELLOW 10
#define LED_RED 11
#define BUZZER_PIN 8

// Signal thresholds (%)
const int GOOD_SIGNAL = 70;      // ≥70% = reliable transmission
const int WEAK_SIGNAL = 30;      // 30-69% = weak, may lose data
// <30% = signal lost

// Data transmission simulation
int dataPacketsSent = 0;
int dataPacketsLost = 0;
int lastSignalStrength = 0;
bool wasLost = false;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  
  // LED pins
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // LCD
  lcd.init();
  lcd.backlight();
  
  // Mission start screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DEEP SPACE RELAY");
  lcd.setCursor(0, 1);
  lcd.print("SIGNAL MONITOR");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Turn knob to");
  lcd.setCursor(0, 1);
  lcd.print("set signal %");
  delay(2000);
  
  Serial.println("=== MISSION CONTROL DATA RELAY ===");
  Serial.println("Status: ONLINE");
  Serial.println("Good ≥70% | Weak 30-69% | Lost <30%");
  Serial.println("===================================");
}

void loop() {
  // Read potentiometer (0-1023) and convert to percentage (0-100)
  int rawValue = analogRead(POT_PIN);
  int signalPercent = map(rawValue, 0, 1023, 0, 100);
  
  // Update LEDs based on signal strength
  updateLEDs(signalPercent);
  
  // Update LCD display
  updateLCD(signalPercent);
  
  // Simulate data transmission
  simulateDataTransmission(signalPercent);
  
  // Alert if signal is lost
  checkSignalLost(signalPercent);
  
  // Send telemetry to Serial Monitor
  sendTelemetry(signalPercent);
  
  delay(500);  // Update twice per second
}

void updateLEDs(int signal) {
  if (signal >= GOOD_SIGNAL) {
    // Good signal: Green LED only
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  }
  else if (signal >= WEAK_SIGNAL) {
    // Weak signal: Yellow LED only
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  else {
    // Signal lost: Red LED only
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  }
}

void updateLCD(int signal) {
  lcd.clear();
  
  // Row 1: Signal strength
  lcd.setCursor(0, 0);
  lcd.print("SIGNAL: ");
  lcd.print(signal);
  lcd.print("%");
  
  // Signal strength bar (visual)
  lcd.setCursor(10, 0);
  int bars = map(signal, 0, 100, 0, 6);
  for (int i = 0; i < bars; i++) {
    lcd.print("|");
  }
  for (int i = bars; i < 6; i++) {
    lcd.print(".");
  }
  
  // Row 2: Status
  lcd.setCursor(0, 1);
  if (signal >= GOOD_SIGNAL) {
    lcd.print("TRANSMITTING...");
  }
  else if (signal >= WEAK_SIGNAL) {
    lcd.print("WEAK SIGNAL");
  }
  else {
    lcd.print("!!! LOST !!!");
  }
  
  // Show data stats on second row if space
  if (signal >= GOOD_SIGNAL) {
    lcd.setCursor(13, 1);
    lcd.print("TX");
  }
}

void simulateDataTransmission(int signal) {
  // Every time we have good signal, "send" a data packet
  if (signal >= GOOD_SIGNAL) {
    dataPacketsSent++;
    Serial.print("📡 Data packet #");
    Serial.print(dataPacketsSent);
    Serial.println(" transmitted successfully");
  }
  // If signal is weak, some packets get lost (random)
  else if (signal >= WEAK_SIGNAL) {
    // 30% chance of packet loss in weak signal zone
    int randomChance = random(0, 100);
    if (randomChance < 30) {
      dataPacketsLost++;
      Serial.print("⚠️ Data packet LOST! (Weak signal) Total lost: ");
      Serial.println(dataPacketsLost);
      
      // Quick beep to indicate data loss
      digitalWrite(BUZZER_PIN, HIGH);
      delay(50);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}

void checkSignalLost(int signal) {
  if (signal < WEAK_SIGNAL) {
    if (!wasLost) {
      // Signal just dropped
      wasLost = true;
      Serial.println("🚨 SIGNAL LOST! Emergency alarm!");
      
      // Emergency alarm pattern
      for (int i = 0; i < 3; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(BUZZER_PIN, LOW);
        delay(200);
      }
    }
  } else {
    wasLost = false;
  }
}

void sendTelemetry(int signal) {
  static int lastSent = 0;
  if (millis() - lastSent > 2000) {  // Send every 2 seconds
    Serial.print("📊 TELEMETRY | Signal: ");
    Serial.print(signal);
    Serial.print("% | Sent: ");
    Serial.print(dataPacketsSent);
    Serial.print(" | Lost: ");
    Serial.print(dataPacketsLost);
    
    if (dataPacketsSent > 0) {
      float successRate = (dataPacketsSent - dataPacketsLost) * 100.0 / dataPacketsSent;
      Serial.print(" | Success: ");
      Serial.print(successRate, 1);
      Serial.print("%");
    }
    Serial.println();
    lastSent = millis();
  }
}

/*
 * ASTEROID PROXIMITY SCANNER
 * Mission: Mining drone collision avoidance system
 * Engineer: Matibini Handiya
 * 
 * This system detects distance to asteroid surface and provides
 * escalating alerts as the drone approaches for landing/mining
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define TRIG_PIN 6
#define ECHO_PIN 7
#define BUZZER_PIN 8
#define LED_RED 9
#define LED_YELLOW 10
#define LED_GREEN 11

// Distance thresholds (in cm)
const float SAFE_DISTANCE = 100.0;      // >100cm = safe approach
const float CAUTION_DISTANCE = 50.0;    // 50-100cm = caution zone
const float CRITICAL_DISTANCE = 20.0;   // <20cm = abort! collision imminent

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
float distance;
long duration;

// Mission control display
String missionStatus = "APPROACHING";

void setup() {
  Serial.begin(9600);
  
  // Initialize ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize alert pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Mission start screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ASTEROID MINING");
  lcd.setCursor(0, 1);
  lcd.print("DRONE v1.0");
  delay(2000);
  
  // System test
  systemTest();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PROXIMITY SCAN");
  lcd.setCursor(0, 1);
  lcd.print("READY");
  delay(1000);
  
  Serial.println("=== ASTEROID PROXIMITY SCANNER ===");
  Serial.println("Mission: Mining drone approach system");
  Serial.println("Status: ONLINE");
  Serial.println("===================================");
}

void loop() {
  // Read distance from ultrasonic sensor
  distance = readDistance();
  
  // Update mission control display
  updateDisplay();
  
  // Determine alert level based on distance
  determineAlertLevel();
  
  // Send telemetry to mission control (Serial Monitor)
  sendTelemetry();
  
  delay(200);  // Fast updates for real-time scanning
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) {
    return 999;  // No object detected (deep space)
  }
  
  // Convert to cm: speed of sound = 343 m/s = 0.0343 cm/µs
  // Distance = (duration * speed) / 2 (round trip)
  float dist = duration * 0.0343 / 2;
  return dist;
}

void determineAlertLevel() {
  if (distance > SAFE_DISTANCE) {
    // SAFE ZONE - Normal approach
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    missionStatus = "SAFE APPROACH";
  }
  else if (distance > CRITICAL_DISTANCE && distance <= SAFE_DISTANCE) {
    // CAUTION ZONE - Prepare for mining deployment
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    
    // Slow beeps (500ms on, 500ms off)
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(400);
    
    missionStatus = "CAUTION";
  }
  else if (distance <= CRITICAL_DISTANCE && distance < 999) {
    // CRITICAL ZONE - Abort! Collision imminent
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    
    // Fast beeps (100ms on, 100ms off)
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
    
    missionStatus = "CRITICAL! ABORT!";
  }
  else if (distance >= 999) {
    // No object detected - deep space
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    missionStatus = "DEEP SPACE";
  }
}

void updateDisplay() {
  lcd.clear();
  
  // Row 1: Distance reading
  lcd.setCursor(0, 0);
  lcd.print("DIST: ");
  
  if (distance >= 999) {
    lcd.print(">4m");
  } else {
    lcd.print(distance, 0);
    lcd.print("cm");
  }
  
  // Row 2: Mission status
  lcd.setCursor(0, 1);
  
  if (missionStatus == "CRITICAL! ABORT!") {
    lcd.print("ABORT! ABORT!");
  } else if (missionStatus == "DEEP SPACE") {
    lcd.print("DEEP SPACE");
  } else if (missionStatus == "CAUTION") {
    lcd.print("CAUTION ZONE");
  } else {
    lcd.print(missionStatus);
  }
}

void sendTelemetry() {
  Serial.print("DISTANCE: ");
  if (distance >= 999) {
    Serial.print("DEEP SPACE");
  } else {
    Serial.print(distance, 0);
    Serial.print(" cm");
  }
  Serial.print(" | STATUS: ");
  Serial.println(missionStatus);
}

void systemTest() {
  Serial.println("Running proximity scanner test...");
  
  // Test all LEDs
  digitalWrite(LED_GREEN, HIGH);
  delay(200);
  digitalWrite(LED_YELLOW, HIGH);
  delay(200);
  digitalWrite(LED_RED, HIGH);
  delay(200);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  
  // Test buzzer
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("System test complete");
  Serial.println();
}

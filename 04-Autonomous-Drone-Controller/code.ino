/*
 * AUTONOMOUS DRONE CONTROLLER - Asteroid Navigation
 * Mission: Obstacle avoidance for mining drones
 * Engineer: Matibini Handiya
 * 
 * The drone scans forward. If an obstacle is too close,
 * it stops, beeps, and steers (servo turns) to find a clear path.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin definitions
#define TRIG_PIN 6
#define ECHO_PIN 7
#define BUZZER_PIN 8
#define LED_GREEN 9
#define LED_YELLOW 10
#define LED_RED 11

// Thresholds (distance in cm)
const int SAFE_DISTANCE = 30;     // >30cm → move freely
const int WARNING_DISTANCE = 15;   // 15-30cm → prepare to turn
const int DANGER_DISTANCE = 8;     // <8cm → emergency stop & turn

// Servo
Servo steeringServo;
int currentAngle = 90;              // 90° = straight ahead
const int TURN_STEP = 30;           // degrees to turn when avoiding

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Drone state
enum DroneState { MOVING, TURNING, STOPPED };
DroneState state = MOVING;

// Timing for non‑blocking turning
unsigned long turnStartTime = 0;
const int TURN_DURATION = 800;      // milliseconds to turn

void setup() {
  Serial.begin(9600);
  
  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // LEDs and buzzer
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Servo
  steeringServo.attach(5);
  steeringServo.write(currentAngle);   // start straight
  
  // LCD
  lcd.init();
  lcd.backlight();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ASTEROID DRONE");
  lcd.setCursor(0, 1);
  lcd.print("NAV SYSTEM v1.0");
  delay(2000);
  
  Serial.println("=== AUTONOMOUS DRONE CONTROLLER ===");
  Serial.println("Status: ONLINE");
  Serial.println("Safe distance >30cm | Danger <8cm");
  Serial.println("===================================");
  
  // quick test beep & LED flash
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Measure distance
  int distance = readDistance();
  
  // Decide drone behaviour based on distance
  updateDroneState(distance);
  
  // Update LEDs according to state
  updateLEDs();
  
  // Update LCD with telemetry
  updateLCD(distance);
  
  // Send data to Serial Monitor (mission control)
  sendTelemetry(distance);
  
  // Small delay to keep loop responsive
  delay(100);
}

/**
 * Read distance from ultrasonic sensor (cm)
 */
int readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) return 999;   // no object detected
  
  int distance = duration * 0.0343 / 2;
  return constrain(distance, 0, 400);
}

/**
 * Finite state machine for drone behaviour
 */
void updateDroneState(int distance) {
  switch (state) {
    case MOVING:
      steeringServo.write(90);           // straight ahead
      
      if (distance < DANGER_DISTANCE) {
        // Emergency stop! Enter STOPPED state first
        state = STOPPED;
        turnStartTime = millis();
        
        // Stop the servo (don't turn yet)
        steeringServo.write(90);  // keep straight but stopped
        
        // Emergency alarm pattern
        for (int i = 0; i < 3; i++) {
          digitalWrite(BUZZER_PIN, HIGH);
          delay(100);
          digitalWrite(BUZZER_PIN, LOW);
          delay(100);
        }
        
        Serial.println("EMERGENCY STOPPED! Obstacle too close!");
      } 
      else if (distance < WARNING_DISTANCE) {
        // Warning zone: single beep
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
      }
      break;
      
    case STOPPED:
      // Red LED should be ON during emergency stop
      // Wait 500ms, then decide turn direction
      if (millis() - turnStartTime >= 500) {
        state = TURNING;
        turnStartTime = millis();
        
        // Choose random turn direction
        int direction = random(0, 2);
        if (direction == 0) {
          currentAngle = 90 - TURN_STEP;   // turn left
          Serial.println("Turning LEFT to avoid");
        } else {
          currentAngle = 90 + TURN_STEP;   // turn right
          Serial.println("Turning RIGHT to avoid");
        }
        steeringServo.write(currentAngle);
        
        // Short beep for turning
        digitalWrite(BUZZER_PIN, HIGH);
        delay(80);
        digitalWrite(BUZZER_PIN, LOW);
      }
      break;
      
    case TURNING:
      // Yellow LED on during turning
      if (millis() - turnStartTime >= TURN_DURATION) {
        state = MOVING;
        currentAngle = 90;
        steeringServo.write(currentAngle);
        Serial.println("Turn complete - resuming forward");
        // Success beep
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
        delay(50);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
      }
      break;
  }
}
/**
 * Update LED indicators based on drone state & distance
 */
void updateLEDs() {
  if (state == STOPPED) {
    // Emergency stopped - RED LED on
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
  } 
  else if (state == TURNING) {
    // Turning - YELLOW LED on
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
  } 
  else { // MOVING
    // Moving forward - GREEN LED on
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }
}
/**
 * Show telemetry on LCD
 */
void updateLCD(int distance) {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("DIST:");
  if (distance >= 400) {
    lcd.print(" >4m ");
  } else {
    lcd.print(distance);
    lcd.print("cm ");
  }
  
  lcd.setCursor(0, 1);
  if (state == MOVING) {
    lcd.print(">> MOVING >>");
  } else if (state == STOPPED) {
    lcd.print("!! STOPPED !!");
  }
  
  // Show turn direction on second line if not straight
  if (currentAngle < 85) {
    lcd.setCursor(10, 1);
    lcd.print("LEFT");
  } else if (currentAngle > 95) {
    lcd.setCursor(10, 1);
    lcd.print("RIGHT");
  }
}

/**
 * Send data to Serial Monitor (simulated mission control downlink)
 */
void sendTelemetry(int distance) {
  Serial.print("DIST: ");
  if (distance >= 400) Serial.print(">400cm");
  else Serial.print(distance);
  Serial.print(" | STATE: ");
  
  if (state == MOVING) Serial.print("MOVING");
  else if (state == STOPPED) Serial.print("STOPPED/AVOID");
  
  if (currentAngle != 90) {
    Serial.print(" | STEERING: ");
    if (currentAngle < 90) Serial.print("LEFT");
    else Serial.print("RIGHT");
  }
  Serial.println();
}

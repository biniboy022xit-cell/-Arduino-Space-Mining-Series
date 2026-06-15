/*
 * Lunar Base Life Support (Planned)
 * Project 2 - Space Mining Series
 * 
 * STATUS: ON HOLD - Waiting for DS18B20 sensor
 * 
 * This code is ready to upload once the replacement sensor arrives.
 * The logic has been tested with simulation.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin definitions
#define ONE_WIRE_BUS 2
#define BUZZER_PIN 8
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11

// Temperature thresholds (Celsius)
const float TEMP_MIN_SAFE = 18.0;
const float TEMP_MAX_SAFE = 28.0;
const float TEMP_MIN_WARNING = 10.0;
const float TEMP_MAX_WARNING = 35.0;

// Initialize components
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature;
String lifeSupportStatus;

void setup() {
  Serial.begin(9600);
  
  sensors.begin();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LUNAR BASE");
  lcd.setCursor(0, 1);
  lcd.print("LIFE SUPPORT");
  delay(2000);
  
  Serial.println("Lunar Base Life Support Ready");
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  
  if (temperature == -127) {
    handleSensorError();
    return;
  }
  
  updateDisplay();
  updateRGBLED();
  checkAlerts();
  sendTelemetry();
  
  delay(2000);
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(temperature, 1);
  lcd.print(" C");
  
  lcd.setCursor(0, 1);
  if (temperature >= TEMP_MIN_SAFE && temperature <= TEMP_MAX_SAFE) {
    lcd.print("NOMINAL");
    lifeSupportStatus = "NOMINAL";
  } else if (temperature < TEMP_MIN_SAFE) {
    lcd.print("LOW TEMP");
    lifeSupportStatus = "LOW";
  } else if (temperature > TEMP_MAX_SAFE) {
    lcd.print("HIGH TEMP");
    lifeSupportStatus = "HIGH";
  }
}

void updateRGBLED() {
  if (temperature >= TEMP_MIN_SAFE && temperature <= TEMP_MAX_SAFE) {
    // Green
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
  else if (temperature >= TEMP_MIN_WARNING && temperature <= TEMP_MAX_WARNING) {
    // Yellow (Red + Green)
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
  else {
    // Red
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
}

void checkAlerts() {
  if (temperature < TEMP_MIN_WARNING || temperature > TEMP_MAX_WARNING) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  }
  else if (temperature < TEMP_MIN_SAFE || temperature > TEMP_MAX_SAFE) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void handleSensorError() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SENSOR ERROR");
  lcd.setCursor(0, 1);
  lcd.print("CHECK WIRING");
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_RED, HIGH);
    delay(200);
    digitalWrite(LED_RED, LOW);
    delay(200);
  }
}

void sendTelemetry() {
  Serial.print("TEMP: ");
  Serial.print(temperature, 1);
  Serial.print(" C | STATUS: ");
  Serial.println(lifeSupportStatus);
}

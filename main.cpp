#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define voltagePin A0
#define currentPin A1

// 🔧 Calibration Values
float voltageCalibration = 2.10;
float currentCalibration = 0.065;

// Noise Limits
float minVoltage = 15.0;
float minCurrent = 0.09;

float voltageOffset = 0;
float currentOffset = 0;

float voltage = 0;
float current = 0;
float power = 0;
float energy = 0;

unsigned long lastTime;


// =========================
// OFFSET CALIBRATION
// =========================
void calibrateSensors()
{
  long vSum = 0;
  long cSum = 0;

  for(int i = 0; i < 2000; i++)
  {
    vSum += analogRead(voltagePin);
    cSum += analogRead(currentPin);
    delay(1);
  }

  voltageOffset = vSum / 2000.0;
  currentOffset = cSum / 2000.0;
}


// =========================
// SETUP
// =========================
void setup()
{
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Energy Meter");

  lcd.setCursor(0,1);
  lcd.print("Calibrating");

  calibrateSensors();

  delay(2000);
  lcd.clear();

  lastTime = millis();
}


// =========================
// LOOP
// =========================
void loop()
{
  long vSqSum = 0;
  long cSqSum = 0;

  int samples = 1000;

  // RMS Sampling
  for(int i = 0; i < samples; i++)
  {
    float v = analogRead(voltagePin) - voltageOffset;
    float c = analogRead(currentPin) - currentOffset;

    vSqSum += v * v;
    cSqSum += c * c;

    delayMicroseconds(200);
  }

  // RMS Calculation
  voltage = sqrt(vSqSum / (float)samples) * voltageCalibration;
  current = sqrt(cSqSum / (float)samples) * currentCalibration;

  // =========================
  // NO INPUT => SHOW ZERO
  // =========================
  if(voltage < minVoltage)
    voltage = 0;

  if(current < minCurrent)
    current = 0;

  // Stable Power
  power = voltage * current;

  // Extra filtering
  if(power < 2)
    power = 0;

  // =========================
  // ENERGY CALCULATION
  // =========================
  unsigned long now = millis();

  float hours = (now - lastTime) / 3600000.0;

  energy += (power * hours) / 10.0; // kWh

  lastTime = now;

  // =========================
  // LCD DISPLAY
  // =========================
  lcd.setCursor(0,0);
  lcd.print("V:");
  lcd.print(voltage,0);

  lcd.print(" I:");
  lcd.print(current,2);

  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(power,0);

  lcd.print("W ");
  lcd.print("E:");

  lcd.print(energy,3);
  

  delay(500);
}
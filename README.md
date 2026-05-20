Digital Energy Meter Using Arduino

A real-time AC energy monitoring system built with Arduino Uno that measures
voltage, current, power, and energy consumption — displayed on a 16×2 I2C LCD.


Features

- Real-time AC Voltage (Vrms) measurement
- Real-time AC Current (Irms) measurement
- Instantaneous Power (Watts) calculation
- Cumulative Energy (kWh) tracking
- Auto offset calibration on startup
- Noise filtering for stable zero reading
- 16×2 I2C LCD display (refreshes every 500ms)
- Buzzer alert for overcurrent protection


 Hardware Requirements

| Component | Specification |
|-----------|--------------|
| Microcontroller | Arduino Uno (ATmega328P) |
| Voltage Sensor | ZMPT101B AC Voltage Sensor |
| Current Sensor | ACS712 (30A) Module |
| Display | 16×2 LCD with I2C (0x27) |
| Alert | 5V Buzzer |
| Power Supply | 5V USB / DC Adapter |
| Load (Test) | AC Bulb / Fan |


Circuit Connections

| Component | Pin | Arduino Pin |
|-----------|-----|-------------|
| ZMPT101B | OUT | A0 |
| ZMPT101B | VCC | 5V |
| ZMPT101B | GND | GND |
| ACS712 | OUT | A1 |
| ACS712 | VCC | 5V |
| ACS712 | GND | GND |
| LCD I2C | SDA | A4 |
| LCD I2C | SCL | A5 |
| LCD I2C | VCC | 5V |
| LCD I2C | GND | GND |
| Buzzer | + | D8 |
| Buzzer | - | GND |

> Use isolation transformer or optocoupler when
> connecting to 230V AC mains. Never connect AC
> directly to Arduino pins.


Software Requirements

- Arduino IDE 1.8+
- LiquidCrystal_I2C Library
- Wire.h (built-in)
- math.h (built-in)

### Install Library

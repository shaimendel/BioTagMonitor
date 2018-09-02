#include "utils.h"
#include "arch.h"
#include "arduino.h"

void addPulseToVector(vector* pulse_samples_vector, float current_voltage, float current_amper, unsigned long micros_from_start) {
  pulseData data = {0};
  data.voltage = current_voltage;
  data.current = current_amper;
  data.micros_from_start = micros_from_start;
  vector_add(pulse_samples_vector, &data);
}

void setDigitalVoltage(int pin, int value) {
//  Serial.print("Set digital voltage for pin ");
//  Serial.print(pin);
//  Serial.print(": ");
//  Serial.print(value);
  digitalWrite(pin, value);
//  Serial.println();
}

void setVoltageRaw(int pin, int value) {
//  Serial.print("Set analog voltage for pin ");
//  Serial.print(pin);
//  Serial.print(": ");
//  Serial.println(255* value/5);
  analogWrite(pin, value);
}

void setVoltage(int pin, float value) {
  Serial.print("Set analog voltage for pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.print(value);
  Serial.println("V");
  //pwnWrite(int(65535 * value / 3.3))
  analogWrite(pin, int(255 * value / 3.3));
}

void printVoltage(int pin) {
    float       vbatLSB        = 0.80566F;  // mV per LSB
    int   vbati = 0;    // Raw integer value
    vbati = analogRead(pin);
    Serial.print("Read voltage 2 for pin ");
    Serial.print(pin);
    Serial.print(": ");

  // Display the value in volts (based on 3.3V VRef)
    float vbatf = ((float)vbati * vbatLSB);
    Serial.print(vbatf/1000, 2);
    Serial.println("V");
}

float getVoltage(int pin) {
  float       vbatLSB        = 0.80566F;  // mV per LSB
  int   vbati = 0;    // Raw integer value
  vbati = analogReadFast(pin);
// Display the value in volts (based on 3.3V VRef)
  float vbatf = ((float)vbati * vbatLSB);
  //Serial.print(vbatf/1000, 2);
  //Serial.println("V");
  return vbatf/1000;
}

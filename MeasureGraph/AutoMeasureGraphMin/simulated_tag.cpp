#include "simulated_tag.h"
#include "arch.h"
#include "utils.h"

vector* simulated_pulse_samples;

void simulated_tag_setup(vector* v) {
    simulated_pulse_samples = v;
}

volatile long dac_voltage = 20;
volatile long pulse_length = 8;

void simulated_tag_loop() {
  float voltage_not_in_pulse = 0;
  while (Serial.available() <= 0) {
    float current_voltage = getVoltage(BATTERY_VOLTAGE);
    if (current_voltage > voltage_not_in_pulse) {
      voltage_not_in_pulse = current_voltage;
    }
  }

  String dac_voltage_string = Serial.readStringUntil('\n');
  dac_voltage = atoi(dac_voltage_string.c_str());
  
  if (dac_voltage == 0)
    return;
    
  String pulse_length_string = Serial.readStringUntil('\n');
  pulse_length = atoi(pulse_length_string.c_str());
  
  setDigitalVoltage(SHUTDOWN_PIN, LOW);
  setVoltageRaw(DAC_PIN, dac_voltage);

  unsigned long start_of_period = millis();
  unsigned long start_of_period_micros = micros();
  
  float voltage_in_pulse = getVoltage(BATTERY_VOLTAGE); //Battery Voltage
  float current_in_pulse = getVoltage(SIMULATED_LOAD_CURRENT); //Current

  vector_reset(simulated_pulse_samples);
  addPulseToVector(simulated_pulse_samples, voltage_in_pulse, current_in_pulse, micros() - start_of_period_micros);
  
  while (millis() - start_of_period < pulse_length) {
    float current_voltage = getVoltage(BATTERY_VOLTAGE);
    if (current_voltage < voltage_in_pulse) {
      voltage_in_pulse = current_voltage;
    }

    float current_amper = getVoltage(SIMULATED_LOAD_CURRENT);
    if (current_amper > current_in_pulse) {
      current_in_pulse = current_amper;
    }

    addPulseToVector(simulated_pulse_samples, current_voltage, current_amper, micros() - start_of_period_micros);
  }
  
  setDigitalVoltage(SHUTDOWN_PIN, HIGH);
  setVoltageRaw(DAC_PIN, 0);

  addPulseToVector(simulated_pulse_samples, getVoltage(BATTERY_VOLTAGE), getVoltage(SIMULATED_LOAD_CURRENT), micros() - start_of_period_micros);

  Serial.print(voltage_in_pulse, 5);
  Serial.print(",");
  Serial.print(current_in_pulse, 5);
  Serial.print(",");
  Serial.print(millis() - start_of_period);
  Serial.print(",");
  Serial.print(voltage_not_in_pulse, 5);
  Serial.print(",");
  vector_serialize(simulated_pulse_samples);

  Serial.println();
}

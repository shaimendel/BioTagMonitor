#include "real_tag.h"
#include "arch.h"
#include "utils.h"

vector* real_pulse_samples;

void real_tag_setup(vector* v) {
    real_pulse_samples = v;
}


float voltage_in_pulse = 0; 
float current_in_pulse = 0;
float voltage_not_in_pulse = 0; 

long num_of_relevant_samples = 0;
unsigned long start_of_period = 0;
unsigned long start_of_period_micros = 0;
bool in_pulse = false;

const long NUM_OF_RELEVANT_SAMPLE_LIMIT = 4;

void real_tag_loop() {
  unsigned long currentMillis = millis();
  float current_voltage = getVoltage(BATTERY_VOLTAGE); //Battery Voltage
  float current_amper = getVoltage(TAG_LOAD_CURRENT); //Current
  
  if (in_pulse) { 
    if (current_amper < 0.05){
      num_of_relevant_samples++;
    }
     else
      num_of_relevant_samples = 0;
  }
  else {
    if (current_amper >= 0.05) {
      num_of_relevant_samples++;
      addPulseToVector(real_pulse_samples, current_voltage, current_amper, micros() - start_of_period_micros);
    }
     else {
      num_of_relevant_samples = 0;
      vector_reset(real_pulse_samples);
     }
  }

  if (num_of_relevant_samples >= NUM_OF_RELEVANT_SAMPLE_LIMIT) {
    if (in_pulse) {
      Serial.print(voltage_in_pulse, 5);
      Serial.print(",");
      Serial.print(current_in_pulse, 5);
      Serial.print(",");
      Serial.print(currentMillis - start_of_period);
      Serial.print(",");
      Serial.print(voltage_not_in_pulse, 5);
      Serial.print(",");
      vector_serialize(real_pulse_samples);

      Serial.println();

      voltage_not_in_pulse = 0;
    }
    else {
      //Nothing to do
    }
    
    start_of_period = currentMillis;
    start_of_period_micros = micros();
    in_pulse = !in_pulse;
    num_of_relevant_samples = 0;
    voltage_in_pulse = 100;
    current_in_pulse = 0;
    vector_reset(real_pulse_samples);
  }
  
  if (in_pulse) {
    if (current_voltage < voltage_in_pulse) {
      voltage_in_pulse = current_voltage;
    }

    if (current_amper > current_in_pulse) {
      current_in_pulse = current_amper;
    }

    addPulseToVector(real_pulse_samples, current_voltage, current_amper, micros() - start_of_period_micros);
  }
  else {
    if (current_voltage > voltage_not_in_pulse) {
      voltage_not_in_pulse = current_voltage;
    }
  }
}


#include "real_tag.h"
#include "arch.h"
#include "utils.h"
#include "last_samples.h"

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
bool too_long_pulse = false;
int long_pulse_seconds = 0;
unsigned long last_samples_offset = 0;

enum PulseReason {
  NO_PULSE,
  CURRENT_PEAK,
  VOLTAGE_FALL
};
bool pulse_recognized_reason = NO_PULSE;

const long NUM_OF_RELEVANT_SAMPLE_LIMIT = 4;
const int TOO_LONG_PULSE_LIMIT_MS = 30;
const float CAPACITOR_VOLTAGE_LIMIT = 0.1;

void real_tag_loop() {
  unsigned long currentMillis = millis();
  float current_voltage = getVoltage(BATTERY_VOLTAGE); //Battery Voltage
  float current_amper = getVoltage(TAG_LOAD_CURRENT); //Current
  
  if (in_pulse) { 
    if ((pulse_recognized_reason == VOLTAGE_FALL && !vector_is_empty(real_pulse_samples) && vector_get_last_sample(real_pulse_samples)->voltage < current_voltage) ||
        (pulse_recognized_reason == CURRENT_PEAK && current_amper < 0.05)){
      num_of_relevant_samples++;
    }
     else {
      num_of_relevant_samples = 0;
     }
  }
  else {
    last_samples_add(current_voltage, current_amper, micros() - start_of_period_micros);
    if (!last_samples_is_empty() && last_samples_get_first_voltage() - current_voltage > CAPACITOR_VOLTAGE_LIMIT ) {
      num_of_relevant_samples = NUM_OF_RELEVANT_SAMPLE_LIMIT; //Declare a pulse
      pulse_recognized_reason = VOLTAGE_FALL;
    }
    else if (current_amper >= 0.06) {
      num_of_relevant_samples++;
      pulse_recognized_reason = CURRENT_PEAK;
    }
     else {
      pulse_recognized_reason = NO_PULSE;
      num_of_relevant_samples = 0;
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
      vector_reset(real_pulse_samples);
      pulse_recognized_reason = NO_PULSE;
    }
    else {
      last_samples_offset = last_sample_get_micros_offset();
      last_samples_fill_vector(real_pulse_samples);
      last_samples_reset();
    }
    
    start_of_period = currentMillis;
    start_of_period_micros = micros();
    in_pulse = !in_pulse;
    num_of_relevant_samples = 0;
    voltage_in_pulse = 100;
    current_in_pulse = 0;
    too_long_pulse = false;
    long_pulse_seconds = 0;
  }
  
  if (in_pulse) {
    if (current_voltage < voltage_in_pulse) {
      voltage_in_pulse = current_voltage;
    }

    if (current_amper > current_in_pulse) {
      current_in_pulse = current_amper;
    }

    if (!too_long_pulse) {
      addPulseToVector(real_pulse_samples, current_voltage, current_amper, micros() + last_samples_offset - start_of_period_micros);

      if (currentMillis - start_of_period > TOO_LONG_PULSE_LIMIT_MS) {
        too_long_pulse = true;
        long_pulse_seconds = (currentMillis - start_of_period) / 1000;
        vector_reset(real_pulse_samples);
      }
    }
  }
  else {
    if (current_voltage > voltage_not_in_pulse) {
      voltage_not_in_pulse = current_voltage;
    }
  }

  if (too_long_pulse && (currentMillis - start_of_period)/1000 > long_pulse_seconds){
      Serial.print(voltage_in_pulse, 5);
      Serial.print(",");
      Serial.print(current_in_pulse, 5);
      Serial.print(",");
      Serial.print(currentMillis - start_of_period);
      Serial.print(",");
      Serial.print(voltage_not_in_pulse, 5);
      Serial.print(",");
      Serial.print("*");

      Serial.println();
      long_pulse_seconds++;
  }
}

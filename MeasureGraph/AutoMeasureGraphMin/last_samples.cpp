#include "last_samples.h"
#include "pulse.h"

pulseData last_samples[LAST_SAMPLES_AMOUNT] = {0};
int first = -1;
int last = -1;

void last_samples_add(float voltage, float current, unsigned long micros_from_start) {
  int next = (last + 1) % LAST_SAMPLES_AMOUNT;
  if (next == first) 
    first = (first + 1) % LAST_SAMPLES_AMOUNT;
  last_samples[next].voltage = voltage; 
  last_samples[next].current = current;
  last_samples[next].micros_from_start = micros_from_start;
  last = next;
  if (first == -1)
    first = 0;
}
void last_samples_fill_vector(vector* real_pulse_samples) {
  if (last < 0)
    return;

  unsigned long offset = last_samples[first].micros_from_start;

  int count = 0;
  for (int i = first; true; i = (i+1) % LAST_SAMPLES_AMOUNT, count++) {
    last_samples[i].micros_from_start -= offset;
    vector_add(real_pulse_samples, &last_samples[i]);
    if (i == last)
      break;
  }
}

unsigned long last_sample_get_micros_offset() {
  int second = (first + 1) % LAST_SAMPLES_AMOUNT;
  return last_samples[last].micros_from_start - last_samples[first].micros_from_start + (last_samples[second].micros_from_start - last_samples[first].micros_from_start);
}

void last_samples_reset() {
  first = -1;
  last = -1;
}

bool last_samples_is_empty() {
  return (first == -1) && (last == -1);
}

float last_samples_get_first_voltage() {
  return last_samples[first].voltage;
}

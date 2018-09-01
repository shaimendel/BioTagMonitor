#include "last_samples.h"
#include "pulse.h"

pulseData last_samples[LAST_SAMPLES_AMOUNT] = {0};
int first = -1;
int last = -1;

void last_samples_add(float voltage, float current) {
  int next = (last + 1) % LAST_SAMPLES_AMOUNT;
  if (next == first) 
    first = (first + 1) % LAST_SAMPLES_AMOUNT;
  last_samples[next].voltage = voltage; 
  last_samples[next].current = current;
  last = next;
  if (first == -1)
    first = 0;
}
void last_samples_fill_vector(vector* real_pulse_samples) {
  if (last < 0)
    return;

  int count = 0;
  for (int i = first; true; i = (i+1) % LAST_SAMPLES_AMOUNT, count++) {
    last_samples[i].micros_from_start = count;
    vector_add(real_pulse_samples, &last_samples[i]);
    if (i == last)
      break;
  }
}

void last_samples_reset() {
  first = -1;
  last = -1;
}

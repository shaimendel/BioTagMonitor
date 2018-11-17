#pragma once
#include "vector.h"

#define LAST_SAMPLES_AMOUNT 15

void last_samples_add(float voltage, float current, unsigned long micros_from_start);
void last_samples_reset();
unsigned long last_sample_get_micros_offset();
void last_samples_fill_vector(vector* real_pulse_samples);
bool last_samples_is_empty();
float last_samples_get_first_voltage();

#pragma once
#include "vector.h"

#define LAST_SAMPLES_AMOUNT 10

void last_samples_add(float voltage, float current);
void last_samples_reset();
void last_samples_fill_vector(vector* real_pulse_samples);

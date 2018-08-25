#pragma once
#include "vector.h"

void addPulseToVector(vector* pulse_samples_vector, float current_voltage, float current_amper, unsigned long micros_from_start);
void setDigitalVoltage(int pin, int value);
void setVoltageRaw(int pin, int value);
void setVoltage(int pin, float value);
void printVoltage(int pin);
float getVoltage(int pin);

#include "vector.h"
#include "real_tag.h"
#include "arch.h"
#include "utils.h"

#define CALIBRATION_SAMPLES_AMOUNT 20
#define CURRENT_MULTIPLIER_THRESHOLD 1.5
#define RECORDING_SECONDS 4

vector pulse_samples_vector;
float rest_amper_avg = 0;
bool pulse_started = false;
unsigned long pulse_start = 0;
bool finished = false;

void setup() {
  pinMode(SHUTDOWN_PIN, OUTPUT);
  specific_board_init();

  pinMode(DAC_PIN, OUTPUT);
  setDigitalVoltage(SHUTDOWN_PIN, HIGH);
  vector_init(&pulse_samples_vector);

  // Open serial communications and wait for port to open:
  Serial.begin(14400);
  while (!Serial || Serial.available() <= 0) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  for (int i = 0; i < CALIBRATION_SAMPLES_AMOUNT; i++) {
    rest_amper_avg += getVoltage(TAG_LOAD_CURRENT); //Current
  }

  rest_amper_avg /= CALIBRATION_SAMPLES_AMOUNT;
}

bool has_pulse_started() {
  float current = getVoltage(TAG_LOAD_CURRENT);
  if (current > rest_amper_avg * CURRENT_MULTIPLIER_THRESHOLD) {
    return true;
  }

  return false;
}

unsigned long last_pulse = 0;

void loop() {
  if (finished) {
    return;
  }
  if (!pulse_started) {
    pulse_started = has_pulse_started();
    pulse_start = millis();
    last_pulse = pulse_start - 1;
    return;
  }

  unsigned long now = millis();

  if (now - last_pulse < 1){
    return;
  }

  float current_voltage = getVoltage(BATTERY_VOLTAGE); //Battery Voltage
  float current_amper = getVoltage(TAG_LOAD_CURRENT); //Current

  addPulseToVector(&pulse_samples_vector, current_voltage, current_amper, now - pulse_start);
  last_pulse = now;

  if (now - pulse_start > RECORDING_SECONDS*1000) {
    finished = true;
    Serial.print(0);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    vector_serialize(&pulse_samples_vector);
    Serial.println();
  }
}

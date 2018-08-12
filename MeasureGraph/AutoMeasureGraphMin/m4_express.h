const int SHUTDOWN_PIN = 5;
const int BATTERY_VOLTAGE = A3;
const int SIMULATED_LOAD_CURRENT = A2;
const int TAG_LOAD_CURRENT = A4;
const int analogPins[3] = { SIMULATED_LOAD_CURRENT, BATTERY_VOLTAGE, TAG_LOAD_CURRENT };
const int DAC_PIN = A0;
const int analogCount = sizeof(analogPins)/sizeof(analogPins[0]);

void specific_board_init() {
  analogReadResolution(12);
}

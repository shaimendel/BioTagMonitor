const int SHUTDOWN_PIN = PC3;
const int BATTERY_VOLTAGE = PA2;
const int SIMULATED_LOAD_CURRENT = PA1;
const int TAG_LOAD_CURRENT = PA1;
const int analogPins[2] = { SIMULATED_LOAD_CURRENT, BATTERY_VOLTAGE, TAG_LOAD_CURRENT };
const int DAC_PIN = PA4;
const int analogCount = sizeof(analogPins)/sizeof(analogPins[0]);

void specific_board_init() {
  for (int i = 0; i < analogCount; i++)
  {
    pinMode(analogPins[i], INPUT_ANALOG);
  }
}


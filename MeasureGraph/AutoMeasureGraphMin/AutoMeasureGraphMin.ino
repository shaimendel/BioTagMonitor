 #include "arch.h"
#include "vector.h"
#include "utils.h"
#include "real_tag.h"
#include "simulated_tag.h"

vector pulse_samples_vector;
bool isRealTag = true;

void setup() {
  pinMode(SHUTDOWN_PIN, OUTPUT);
  uint8_t i;
  specific_board_init();

  pinMode(DAC_PIN, OUTPUT);
  setDigitalVoltage(SHUTDOWN_PIN, HIGH);
  vector_init(&pulse_samples_vector);

  // Open serial communications and wait for port to open:
  Serial.begin(14400);

  while(true) {
    while (!Serial || Serial.available() <= 0) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  
    String isRealTagStr = Serial.readStringUntil('\n');
    if (!isRealTagStr.startsWith("yes") && !isRealTagStr.startsWith("no")) 
      continue;
    if (!isRealTagStr.startsWith("y")) {
      isRealTag = false;
    }
    break;
  }

  isRealTag ? real_tag_setup(&pulse_samples_vector) : simulated_tag_setup(&pulse_samples_vector);
}

void loop() {
  isRealTag ? real_tag_loop() : simulated_tag_loop();
}

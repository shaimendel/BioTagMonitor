#include <libmaple\dac.h>

const int digital_pin = PC3;
const int analogPins[2] = { PA1, PA2 };
const int analogCount = sizeof(analogPins)/sizeof(analogPins[0]);
  
void setup() {
  dac_enable_channel(DAC, 1);
  dac_init(DAC, DAC_CH1 | DAC_CH2);
  
  pinMode(digital_pin, OUTPUT);
  uint8_t i;
  for (i = 0; i < analogCount; i++)
  {
    pinMode(analogPins[i], INPUT_ANALOG);
  }

  dac_write_channel(DAC, DAC_CH1, 0);
  setDigitalVoltage(digital_pin, HIGH);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// the loop function runs over and over again forever
float voltage_in_pulse = 0;
float current_in_pulse = 0;
long num_of_relevant_samples = 0;
unsigned long start_of_period = 0;
bool in_pulse = false;

const long NUM_OF_RELEVANT_SAMPLE_LIMIT = 3;

void loop() {
  unsigned long currentMillis = millis();
  float current_voltage = getVoltage(PA2); //Battery Voltage
  float current_amper = getVoltage(PA1); //Current

  if (in_pulse) { 
    if (current_amper < 0.05){
      num_of_relevant_samples++;
    }
     else
      num_of_relevant_samples = 0;
  }
  else {
    if (current_amper >= 0.05) {
      num_of_relevant_samples++;
    }
     else
      num_of_relevant_samples = 0;
  }

  if (num_of_relevant_samples >= NUM_OF_RELEVANT_SAMPLE_LIMIT) {
    if (in_pulse) {
      Serial.print(voltage_in_pulse, 5);
      Serial.print(",");
      Serial.print(current_in_pulse, 5);
      Serial.print(",");
      Serial.println(currentMillis - start_of_period);
    }
    else {
      //Nothing to do
    }
    
    start_of_period = currentMillis;
    in_pulse = !in_pulse;
    num_of_relevant_samples = 0;
    voltage_in_pulse = 100;
    current_in_pulse = 0;
  }
  
  if (in_pulse) {
    if (current_voltage < voltage_in_pulse) {
      voltage_in_pulse = current_voltage;
    }

    //tmp = getVoltage(PA1);
    if (current_amper > current_in_pulse) {
      current_in_pulse = current_amper;
    }
  }
}

void setDigitalVoltage(int pin, int value) {
//  Serial.print("Set digital voltage for pin ");
//  Serial.print(pin);
//  Serial.print(": ");
//  Serial.print(value);
  digitalWrite(pin, value);
//  Serial.println();
}

void setVoltageRaw(int pin, int value) {
  Serial.print("Set analog voltage for pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.println(255* value/5);
  analogWrite(pin, 255* value/5);
}

void setVoltage(int pin, float value) {
  Serial.print("Set analog voltage for pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.print(value);
  Serial.println("V");
  //pwnWrite(int(65535 * value / 3.3))
  analogWrite(pin, int(255 * value / 3.3));
}

void printVoltage2(int pin) {
  Serial.print("Read voltage 1 for pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.println(analogRead(pin)*(5.0 / 1023.0));
}

void printVoltage(int pin) {
    float       vbatLSB        = 0.80566F;  // mV per LSB
    int   vbati = 0;    // Raw integer value
    vbati = analogRead(pin);
    Serial.print("Read voltage 2 for pin ");
    Serial.print(pin);
    Serial.print(": ");

  // Display the value in volts (based on 3.3V VRef)
    float vbatf = ((float)vbati * vbatLSB);
    Serial.print(vbatf/1000, 2);
    Serial.println("V");
}

float getVoltage(int pin) {
  float       vbatLSB        = 0.80566F;  // mV per LSB
    int   vbati = 0;    // Raw integer value
    vbati = analogRead(pin);
  // Display the value in volts (based on 3.3V VRef)
    float vbatf = ((float)vbati * vbatLSB);
    //Serial.print(vbatf/1000, 2);
    //Serial.println("V");
    return vbatf/1000;
}



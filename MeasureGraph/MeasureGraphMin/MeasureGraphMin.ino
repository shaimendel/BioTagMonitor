#include <libmaple/dac.h>

const int digital_pin = PC3;
const int analogPins[2] = { PA1, PA2 };
const int analogCount = sizeof(analogPins)/sizeof(analogPins[0]);
const int analog_output_pin = PA4;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(analog_output_pin, PWM);
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

  //Serial.println("\n\nBeginning test:");
}

// the loop function runs over and over again forever
volatile long dac_voltage = 372;
volatile long pulse_length = 8;

void loop() {
  if (Serial.available() <= 0)
    return;

  String dac_voltage_string = Serial.readStringUntil('\n');
  String pulse_length_string = Serial.readStringUntil('\n');
  dac_voltage = atoi(dac_voltage_string.c_str());
  pulse_length = atoi(pulse_length_string.c_str());
//  Serial.print("Got voltage: ");
//  Serial.print(dac_voltage_string.c_str());
//  Serial.print(", pulse: ");
//  Serial.println(pulse_length_string.c_str());
//  Serial.println("---------------------------");
  
  setDigitalVoltage(digital_pin, LOW);
  dac_write_channel(DAC, DAC_CH1, dac_voltage);

  unsigned long currentMillis = millis();
  float a2_in_pulse = getVoltage(PA2); //Battery Voltage
  float a1_in_pulse = getVoltage(PA1); //Current

  while (millis() - currentMillis < pulse_length) {
    float tmp = getVoltage(PA2);
    if (tmp < a2_in_pulse) {
      a2_in_pulse = tmp;
    }

    tmp = getVoltage(PA1);
    if (tmp > a1_in_pulse) {
      a1_in_pulse = tmp;
    }
  }
  
  setDigitalVoltage(digital_pin, HIGH);
  dac_write_channel(DAC, DAC_CH1, 0);
  
  Serial.print(a2_in_pulse, 5);
  Serial.print(",");
  Serial.println(a1_in_pulse/10, 5);
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



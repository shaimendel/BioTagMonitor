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
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("\n\nBeginning test:");
  setDigitalVoltage(digital_pin, HIGH);
}

// the loop function runs over and over again forever
float analog_output = 0;

void loop() {
  //Serial.println("---------------------------");
  setDigitalVoltage(digital_pin, LOW);
  dac_write_channel(DAC, DAC_CH1, 372);

  delay(4);
  float a1_in_pulse = getVoltage(PA1);
  float a2_in_pulse = getVoltage(PA2);
  delay(4);

  setDigitalVoltage(digital_pin, HIGH);
  dac_write_channel(DAC, DAC_CH1, 0);

  delay(500);
  float a1_after_pulse = getVoltage(PA1);
  float a2_after_pulse = getVoltage(PA2);

  Serial.print("Battery voltage in pulse: ");
  Serial.print(a2_in_pulse, 2);
  Serial.println("V");  
  Serial.print("Battery amper in pulse: ");
  Serial.print(a1_in_pulse/10, 2);
  Serial.println("A");  

  Serial.print("Battery voltage after pulse: ");
  Serial.print(a2_after_pulse, 2);
  Serial.println("V");  
  Serial.print("Battery amper after pulse: ");
  Serial.print(a1_after_pulse/10, 2);
  Serial.println("A");
  
  delay(500);
//  uint32_t i;
//  for (i = 0; i < analogCount; i++)
//  {
//    printVoltage(analogPins[i]);
//    //printVoltage2(analogPins[i]);
//  }

  //setVoltage(analog_output_pin, analog_output);
  /*i =0;
  for (i=0; i<37; i++)
  {
    dac_write_channel(DAC, DAC_CH1, i);
    //pwmwrite(analog_output_pin, 16*i);
  }
  for (i=4095; i>0; i--)
  {
    dac_write_channel(DAC, DAC_CH1, i);
    //pwmwrite(analog_output_pin, 16*i);
  }*/

// if (digital_value) {
//    dac_write_channel(DAC, DAC_CH1, 372);
// }
// else {
//    dac_write_channel(DAC, DAC_CH1, 0);
// }
//  
//  
//  analog_output += 0.1;
//  if (analog_output > 3.3)
//    analog_output = 0;
//  delay(1000);
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



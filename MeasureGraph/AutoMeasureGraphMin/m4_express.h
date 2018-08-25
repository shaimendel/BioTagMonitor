#pragma once

const int SHUTDOWN_PIN = 5;
const int BATTERY_VOLTAGE = A3;
const int SIMULATED_LOAD_CURRENT = A2;
const int TAG_LOAD_CURRENT = A4;
const int analogPins[3] = { SIMULATED_LOAD_CURRENT, BATTERY_VOLTAGE, TAG_LOAD_CURRENT };
const int DAC_PIN = A0;
const int analogCount = sizeof(analogPins)/sizeof(analogPins[0]);

void inline specific_board_init() {
  analogReadResolution(12);
}

#define ADC ADC0
#define   ADC_CTRLB_PRESCALER_DIV64_Val   0x4u   /**< \brief (ADC_CTRLB) Peripheral clock divided by 64 */
#define ADC_CTRLB_PRESCALER_Pos     8            /**< \brief (ADC_CTRLB) Prescaler Configuration */
#define ADC_CTRLB_PRESCALER_DIV64   (ADC_CTRLB_PRESCALER_DIV64_Val << ADC_CTRLB_PRESCALER_Pos)

void inline waitForSync() {
#if defined (__SAMD51__)
  while(ADC->SYNCBUSY.bit.OFFSETCORR || ADC->SYNCBUSY.bit.GAINCORR); // wait for synchronization
#else
  while(ADC->STATUS.bit.SYNCBUSY); // wait for synchronization
#endif 
}

int inline analogReadFast(byte ADCpin)    // inline library functions must be in header
{ ADC->CTRLA.bit.ENABLE = 0;              // disable ADC
  waitForSync();

  int CTRLBoriginal = ADC->CTRLB.reg;
  int AVGCTRLoriginal = ADC->AVGCTRL.reg;
  int SAMPCTRLoriginal = ADC->SAMPCTRL.reg;
  
  ADC->CTRLB.reg &= 0b1111100011111111;          // mask PRESCALER bits
  ADC->CTRLB.reg |= ADC_CTRLB_PRESCALER_DIV64;   // divide Clock by 64
  ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 |   // take 1 sample 
                     ADC_AVGCTRL_ADJRES(0x00ul); // adjusting result by 0
  ADC->SAMPCTRL.reg = 0x00;                      // sampling Time Length = 0

  ADC->CTRLA.bit.ENABLE = 1;                     // enable ADC
  waitForSync();
  int adc = analogRead(ADCpin); 
  
  ADC->CTRLB.reg = CTRLBoriginal;
  ADC->AVGCTRL.reg = AVGCTRLoriginal;
  ADC->SAMPCTRL.reg = SAMPCTRLoriginal;
   
  return adc;
}

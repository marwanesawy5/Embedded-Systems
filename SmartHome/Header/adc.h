#ifndef ADC_H_
#define ADC_H_

/* ADC channel definitions */
#define ADC_LDR_CHANNEL    0   /* PA0 - LDR sensor  */
#define ADC_TEMP_CHANNEL   7   /* PA7 - LM35 sensor */

/* LDR calibration - adjust LDR_MAX to your circuit's max ADC reading */
/* to find your LDR_MAX: shine brightest light on LDR, read ADC value */
#define LDR_MIN   0     /* ADC value in complete darkness */
#define LDR_MAX   660/* ADC value at maximum brightness (66% of 1023) */

/* ADC function prototypes */
void ADC_init(void);
unsigned int ADC_read(unsigned char ch);

#endif /* ADC_H_ */

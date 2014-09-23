/*
 * current_sense_conf.h
 *
 *  Created on: Sep 22, 2014
 *      Author: ghrtdhbdystveut
 */

#ifndef CURRENT_SENSE_CONF_H_
#define CURRENT_SENSE_CONF_H_
/* Include files */

#include "stm32f10x_conf.h"

/* ADC Pins */
#define CURRENT1_PORT GPIOA
#define CURRENT1_PIN  GPIO_Pin_4
#define CURRENT2_PORT GPIOA
#define CURRENT2_PIN  GPIO_Pin_5

/* ADC channels */
#define CURRENT1_CH 4
#define CURRENT2_CH 5

/* ADC functions */
extern void ADC1_Init(void);
extern int16_t Analog_Read(int16_t pin);

#endif /* CURRENT_SENSE_CONF_H_ */

/*
 * stm32f10x_it.h
 *
 *  Created on: Sep 19, 2014
 *      Author: ghrtdhbdystveut
 */

#ifndef STM32F10X_IT_H_
#define STM32F10X_IT_H_
/*Includes ----*/
#include "stm32f10x_conf.h"

/*Handlers */
void EXTI15_10_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

#endif /* STM32F10X_IT_H_ */

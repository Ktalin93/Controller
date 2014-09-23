/*
 * pwm_motor_conf.h
 *
 *  Created on: Sep 19, 2014
 *      Author: ghrtdhbdystveut
 */

#ifndef PWM_MOTOR_CONF_H_
#define PWM_MOTOR_CONF_H_
/*Include files */

#include "stm32f10x_conf.h"

/* PWM CONSTANTS */
#define MIN_DUTY_VAL_H -2395
#define MAX_DUTY_VAL_H 2395
#define MIN_DUTY_VAL_F -1195
#define MAX_DUTY_VAL_F 1195

/*Running Modes */

#define FULL_BRIDGE 0
#define HALF_BRIDGE 1
int Mode;

/*Port,Pins configuration FOR DRIVER 1 */

#define MOTOR1_IN1_PORT GPIOA
#define MOTOR1_IN1_PIN GPIO_Pin_8
#define MOTOR1_IN2_PORT GPIOB
#define MOTOR1_IN2_PIN GPIO_Pin_13
#define MOTOR1_ENABLE_PORT GPIOB
#define MOTOR1_ENABLE_PIN GPIO_Pin_15

/*Port,Pins configuration FOR DRIVER 2 */

#define MOTOR2_IN1_PORT GPIOA
#define MOTOR2_IN1_PIN GPIO_Pin_9
#define MOTOR2_IN2_PORT GPIOB
#define MOTOR2_IN2_PIN GPIO_Pin_14
#define MOTOR2_ENABLE_PORT GPIOB
#define MOTOR2_ENABLE_PIN GPIO_Pin_12

/*Motor 1 functions */

extern void Motor1_Init(int8_t mode);
extern void Motor1_SetDutyCycle(volatile int16_t duty);
#endif /* PWM_MOTOR_CONF_H_ */

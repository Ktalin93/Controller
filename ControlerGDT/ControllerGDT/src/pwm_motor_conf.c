/*
 * pwm_motor_conf.c
 *
 *  Created on: Sep 19, 2014
 *      Author: ghrtdhbdystveut
 */
#include "pwm_motor_conf.h"

/* Peripheral structures */
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

/************ TIM1_TimeBase_Config************/
/**
 * Description: Initializes Timer, PWM frequency 30Hz
 * Params: none
 * Retval: none
 */
void TIM1_TimeBase_Config()
{
  /*Start clock for TIM1*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  /*Configure TIM1 *?
    *Clock is 72Mhz
    *PWM Frequency 30KHz*/
   TIM_TimeBaseStructure.TIM_Prescaler = 0;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseStructure.TIM_Period = 2399;
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
   TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
}

/************ TIM1F_Config************/
/**
 * Description: Configure PWM pins of TIM1 for FULL_BRIDGE mode
 * Params: none
 * Retval: none
 */
void TIM1MF_Config(){
   /* CH1 & CH1N Configuration in PWM mode */
  TIM_DeInit(TIM1); //reset TIM1 to default values
  TIM1_TimeBase_Config();
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  /* TIM1 counter enable */
   TIM_Cmd(TIM1, ENABLE);
   /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

}

/************ TIM1H_Config************/
/**
 * Description: Description: Configure TIM1 for HALF_BRIDGE mode
 * Params: none
 * Retval: none

 */
void TIM1MH_Config(){
   /* CH3 Configuration in PWM mode*/
  TIM_DeInit(TIM1);
  TIM1_TimeBase_Config();
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  /* TIM1 counter enable */
   TIM_Cmd(TIM1, ENABLE);
   /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

}

/************ GPIOMF_Config************/
/**
 * Description: Description: Configure pins FOR FULL_BRIDGE mode
 * Params: none
 * Retval: none

 */
void GPIO1MF_Config(){
  /*Configuration in PWM mode in PWM INPUT Mode */
  /*Start the clock for periph*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                          RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
  //MOTOR 1 INPUT 1
  GPIO_InitStructure.GPIO_Pin = MOTOR1_IN1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR1_IN1_PORT, &GPIO_InitStructure);
  //MOTOR 2 INPUT 2
  GPIO_InitStructure.GPIO_Pin = MOTOR1_IN2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(MOTOR1_IN2_PORT, &GPIO_InitStructure);
  //MOTOR ENABLE
  GPIO_InitStructure.GPIO_Pin = MOTOR1_ENABLE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR1_ENABLE_PORT, &GPIO_InitStructure);

}

/************ GPIOMH_Config************/
/**
 * Description: Description: Configure pins FOR HALF_BRIDGE mode
 * Params: none
 * Retval: none
 */
void GPIO1MH_Config(){

  /*Start the clock for periph*/
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
  //MOTOR 1 INPUT 1
  GPIO_InitStructure.GPIO_Pin = MOTOR1_IN1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR1_IN1_PORT, &GPIO_InitStructure);
  //MOTOR 2 INPUT 2
  GPIO_InitStructure.GPIO_Pin = MOTOR1_IN2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MOTOR1_IN2_PORT, &GPIO_InitStructure);
  //MOTOR ENABLE
  GPIO_InitStructure.GPIO_Pin = MOTOR1_ENABLE_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(MOTOR1_ENABLE_PORT, &GPIO_InitStructure);

}

/************ Motor1_Init************/
/**
 * Description: Initializes the peripherals for the Motor1 driver
 ** Two modes: Half bridge and Full Bridge
 * Params: mode -values (FULL_BRIDGE or HALF_BRIDGE)
 * Retval: none
 */
void Motor1_Init(int8_t mode){

  if(mode == FULL_BRIDGE)
    Mode=FULL_BRIDGE;
  else
    Mode=HALF_BRIDGE;
  if(Mode==FULL_BRIDGE)
    {
      TIM1MF_Config();
      GPIO1MF_Config();
    }
  else
    {
      TIM1MH_Config();
      GPIO1MH_Config();
    }
}

/************ Motor1_SetDutyCycle************/
/**
 * Description: Sets the Duty Cycle for the Motor 1
 ** Two modes: Half bridge and Full Bridge
 * Params: duty
 ** In FULL_BRIDGE : duty in range [-1195,1195]
 ** In HALF BRIDGE: duty in range [-2395 ,2395]
 * Retval: none
 */
void Motor1_SetDutyCycle(volatile int16_t duty){
  if(Mode==FULL_BRIDGE)
  {
      //Enable the bridge
      GPIO_SetBits(MOTOR1_ENABLE_PORT,MOTOR1_ENABLE_PIN);
      if(duty==0)
	 GPIO_ResetBits(MOTOR1_ENABLE_PORT,MOTOR1_ENABLE_PIN);
      if(duty > MAX_DUTY_VAL_F)
          duty=1195;
      if(duty<MIN_DUTY_VAL_F)
          duty=-1195;
      TIM1->CCR1=1200+duty;
  }
  else
    if(Mode==HALF_BRIDGE)
  {
      if(duty > MAX_DUTY_VAL_H)
             duty=2395;
      if(duty<-MIN_DUTY_VAL_H)
             duty=-2395;
      if(duty<0)
	{
	  GPIO_SetBits(MOTOR1_IN1_PORT,MOTOR1_IN1_PIN);
	  GPIO_ResetBits(MOTOR1_IN2_PORT,MOTOR1_IN2_PIN);
	}
      else
	if(duty>=0)
	  {
	    GPIO_ResetBits(MOTOR1_IN1_PORT,MOTOR1_IN1_PIN);
	    GPIO_SetBits(MOTOR1_IN2_PORT,MOTOR1_IN2_PIN);
	  }
      TIM1->CCR3=abs(duty);
  }
}


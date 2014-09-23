//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "BlinkLed.h"

// ----------------------------------------------------------------------------

void
blink_led_init()
{
  // Enable GPIO Peripheral clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  // Start with led turned off
  blink_led_off();
}

// ----------------------------------------------------------------------------

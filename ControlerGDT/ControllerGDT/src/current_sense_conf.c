/*
 * current_sense_conf.c
 *
 *  Created on: Sep 22, 2014
 *      Author: ghrtdhbdystveut
 */
/* Inlcude files */
#include "current_sense_conf.h"

ADC_InitTypeDef ADC_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

/************ GPIO_ADC1_Conf ************/
/**
 * Description: Initializes ADC1 pins
 * Params: none
 * Retval: none
 */
void GPIO_ADC1_Conf(void){
    // Set CURRENT1_PIN as analog input
    GPIO_InitStructure.GPIO_Pin = CURRENT1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CURRENT1_PORT, &GPIO_InitStructure);

    // Set CURRENT1_PIN as analog input
    GPIO_InitStructure.GPIO_Pin = CURRENT2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CURRENT2_PORT, &GPIO_InitStructure);
}

/************ ADC1_Init ************/
/**
 * Description: Initializes ADC1
 * Params: none
 * Retval: none
 */
void ADC1_Init(){

    GPIO_ADC1_Conf();
    /*PCLK2 is the APB2 clock */
    /*ADLCK =PCLK2/6=72/6=12MHz*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    /*Enable ADC1 clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

    ADC_DeInit(ADC1);

    /*Adc1 and adc2 operate independently*/
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
    /*disable scan conversion */
    ADC_InitStructure.ADC_ScanConvMode=DISABLE;
    /*NO CONTINOUS CONVERSION*/
    ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
    /*start con by software*/
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
    /* adc are 12 bit put them in the lower 12 bit*/
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
    /*no of channel used*/
    ADC_InitStructure.ADC_NbrOfChannel=2;

    /*Setup*/
    ADC_Init(ADC1,&ADC_InitStructure);
    /*Enable ADC1*/
    ADC_Cmd(ADC1,ENABLE);
    /*ENABLE ADC1 reset calibration */
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    //Calibrte ADC1
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

/************ GPIO_ADC1_Conf ************/
/**
 * Description: Initializes ADC1 pins
 * Params: channel - number of channel
 **ChanneL Values: - CURRRENT1_CH and CURRENT2_CH
 * Retval: one integer representing the analog value read from the selected channel
 */
uint16_t analogRead(uint16_t channel){
    ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_1Cycles5);
    /*Start software conversion on channel */
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    /* Wait for conversion completed flag */
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
    return ADC_GetConversionValue(ADC1);
}

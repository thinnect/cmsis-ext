/**
 * Extensions to CMSIS OS2.
 *
 * Copyright Thinnect Inc. 2020
 * @license MIT
 */
#include "cmsis_os2_ext.h"

#include "ARMCM0.h" // NVIC

uint32_t osCounterGetMilli ()
{
	return (uint32_t)osKernelGetTickCount();
}

uint32_t osCounterGetSecond ()
{
	return osCounterGetMilli()/1000;
}

void osKernelReboot ()
{
	NVIC_SystemReset();
}
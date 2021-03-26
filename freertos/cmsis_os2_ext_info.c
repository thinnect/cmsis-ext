/**
 * Info extensions to CMSIS OS2 on FreeRTOS.
 *
 * Copyright Thinnect Inc. 2021
 * @license MIT
 */
#include "cmsis_os2_ext.h"

#include "FreeRTOS.h"

size_t osThreadControlBlockSize ()
{
	return sizeof(StaticTask_t);
}

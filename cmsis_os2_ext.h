/**
 * Extensions to CMSIS OS2.
 *
 * Copyright Thinnect Inc. 2020
 * @license MIT
 */
#ifndef CMSIS_OS2_EXT_H_
#define CMSIS_OS2_EXT_H_

#include "cmsis_os2.h"

/**
 * Get milliseconds since kernel start.
 *
 * The function may NOT be called from an ISR!
 */
uint32_t osCounterGetMilli();

/**
 * Get seconds since kernel start.
 *
 * The function may NOT be called from an ISR!
 */
uint32_t osCounterGetSecond();

/**
 * Reboot the device.
 */
void osKernelReboot();

#endif//CMSIS_OS2_EXT_H_

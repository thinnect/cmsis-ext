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
uint32_t osCounterGetMilli (void);

/**
 * Get milliseconds since kernel start.
 *
 * The function may NOT be called from an ISR!
 */
uint64_t osCounterGetMilli64 (void);

/**
 * Get seconds since kernel start.
 *
 * The function may NOT be called from an ISR!
 */
uint32_t osCounterGetSecond (void);

/**
 * Reboot the device.
 */
void osKernelReboot (void);

/**
 * Get the space needed for the thread control block of static threads.
 */
size_t osThreadControlBlockSize (void);

#endif//CMSIS_OS2_EXT_H_

/**
 * Extensions to CMSIS OS2.
 *
 * Copyright Thinnect Inc. 2020
 * @license MIT
 */
#ifndef CMSIS_OS2_EXT_H_
#define CMSIS_OS2_EXT_H_

#include "cmsis_os2.h"

uint32_t osCounterGetMilli(void);
uint32_t osCounterGetSecond(void);

void osKernelReboot(void);

#endif//CMSIS_OS2_EXT_H_

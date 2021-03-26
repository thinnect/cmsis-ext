/**
 * Extensions to CMSIS OS2.
 *
 * Copyright Thinnect Inc. 2020
 * @license MIT
 */
#include "cmsis_os2_ext.h"

#include "device.h" // NVIC

static uint32_t m_millis_h = 0;
static uint32_t m_millis_l = 0;

/**
 * While osKernelGetTickCount is now 64 bits, it is unfortunately not 64 bits
 * under the hood in most RTOS's and most CMSIS adapter layers also do not
 * handle this themselves and still overflow after UIN32_MAX ticks.
 * Therefore the millisecond extension is only 32-bits for now!
 */
uint32_t osCounterGetMilli ()
{
	uint32_t freq = osKernelGetTickFreq();
	if(1000 == freq) // Avoid doing calculations if freq is 1000 Hz
	{
		return (uint32_t)osKernelGetTickCount();
	}
	return (uint32_t)(1000*osKernelGetTickCount()/freq);
}

/**
 * osCounterGetMilli will overflow every 49.7 days.
 * This 64-bit version counter, as long as it is called at least once between
 * each overflow, will be able to handle the overflow.
 *
 * The function may be called from several threads in parallel, so it is
 * necessary to synchronize these accesses - kernel locking is used for this.
 *
 * The function may not be called from an ISR.
 */
uint64_t osCounterGetMilli64 ()
{
	int32_t lock = osKernelLock();
	uint32_t millis32 = osCounterGetMilli();
	uint64_t millis64;

	if (millis32 < m_millis_l)
	{
		m_millis_h++;
	}
	m_millis_l = millis32;

	millis64 = (((uint64_t)m_millis_h << 32) | m_millis_l);

	osKernelRestoreLock(lock);

	return millis64;
}

uint32_t osCounterGetSecond ()
{
	return osCounterGetMilli64() / 1000;
}

void osKernelReboot ()
{
	NVIC_SystemReset();
}

size_t osThreadControlBlockSize ()
{
	return sizeof(StaticTask_t);
}

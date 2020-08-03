/**
 * Second counter overflow test application.
 *
 * Copyright Thinnect Inc. 2020
 * @license MIT
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "cmsis_os2_ext.h"

#include "retargetserial.h"

#include "platform.h"

#include "sleep.h" // emdrv

#include "loggers_ext.h"
#include "logger_fwrite.h"

#include "loglevels.h"
#define __MODUUL__ "main"
#define __LOG_LEVEL__ (LOG_LEVEL_main & BASE_LOG_LEVEL)
#include "log.h"

// Add the headeredit block
#include "incbin.h"
INCBIN(Header, "header.bin");

void app_loop (void * arg)
{
	debug1("app_loop"); // Still log with boot logger

	// Switch to a thread-safe logger
	logger_fwrite_init();
	log_init(BASE_LOG_LEVEL, &logger_fwrite, NULL);

	PLATFORM_LedsSet(1);



	uint32_t lms = osCounterGetMilli();
	uint32_t ls = osCounterGetSecond();
	debug1("ms=%"PRIu32" s=%"PRIu32, lms, ls);

	osDelay(1000);

	for(;;) // Blink leds
	{
		uint32_t nms = osCounterGetMilli();
		uint32_t ns = osCounterGetSecond();
		debug1("ms=%"PRIu32" s=%"PRIu32, nms, ns);

		if (nms < lms)
		{
			if (ns < ls)
			{
				err1("OVERFLOW");
			}
			else
			{
				info1("oveflow ok");
			}
			while(1);
		}
		lms = nms;
		ls = ns;

		PLATFORM_LedsSet(PLATFORM_LedsGet()+1);
		osDelay(1000);
	}
}

// Basic logger before kernel boot
int logger_fwrite_boot (const char *ptr, int len)
{
	fwrite(ptr, len, 1, stdout);
	fflush(stdout);
	return len;
}

int main ()
{
	PLATFORM_Init();

	// LEDs
	PLATFORM_LedsInit();
	PLATFORM_LedsSet(0);

	RETARGET_SerialInit();
	log_init(BASE_LOG_LEVEL, &logger_fwrite_boot, NULL);

	info1("secovrf "VERSION_STR" (%d.%d.%d)", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

    // Initialize sleep management
    SLEEP_Init(NULL, NULL);

	osKernelInitialize();

	const osThreadAttr_t app_thread_attr = { .name = "app" };
	osThreadNew(app_loop, NULL, &app_thread_attr);

	if (osKernelReady == osKernelGetState())
	{
		osKernelStart();
	}
	else
	{
		err1("!osKernelReady");
	}

	while(true);
}

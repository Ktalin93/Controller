//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"
#include "pwm_motor_conf.h"

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 2 / 3)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
int main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");
  trace_printf("System clock: %uHz\n", SystemCoreClock);
  
  while (1)
    {
      timer_sleep(BLINK_ON_TICKS);
      blink_led_off();
      timer_sleep(BLINK_OFF_TICKS);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "tests.h"

void test_nanosleep(void)
{
  struct timespec now, then, duration = { 1, 0 };
  time_t diff;
  int result;

  test_begin("Get current real time before nanosleep()");
  result = clock_gettime(CLOCK_REALTIME, &then);
  if (result) test_failure(); else test_success();
  
  test_begin("Call nanosleep() for 1 second");
  result = nanosleep(&duration, NULL);
  if (result) test_failure(); else test_success();

  test_begin("Get current real time after nanosleep()");
  result = clock_gettime(CLOCK_REALTIME, &now);
  if (result) test_failure(); else test_success();

  test_begin("Check that nanosleep() lasted about 1 second");
  diff = now.tv_sec-then.tv_sec;
  diff *= 1000000000;
  diff += now.tv_nsec-then.tv_nsec;
  diff = abs(diff - 1000000000); /* how far from 1 second? */
  if (diff > 100000000) test_failure(); else test_success();
}

/*
Provided by Ashok Srinivasan to calculate 
 function run time
*/
#include <sys/time.h>
#include "cputime.h"
#include <stdio.h>

double cputime(void)
{
  double current_time;

  struct timeval temp;
 
  gettimeofday(&temp, NULL);

  current_time = temp.tv_sec + 1.0e-6*temp.tv_usec;

  return current_time;
}


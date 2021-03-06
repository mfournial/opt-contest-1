/* -*- mode: c -*-
 * $Id$
 * http://www.bagley.org/~doug/shootout/
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 17000
#else
#define LENGTH 170000
#endif
  int NUM = ((argc == 2) ? atoi(argv[1]) : LENGTH);
  static char flags[8192 + 1];
  long i, k;
  int count = 0;

  while (NUM--) {
    count = 0;
    for (i = 2; i <= 8192; i++) {
      flags[i] = 1;
    }
    for (i = 2; i <= 8192; i++) {
      bool res = !(flags[i]);
      /* remove all multiples of prime: i */
      for (k = i + i; k <= 8192; k += i) {
        flags[k] = flags[k] & res;
      }
      count = count + (!res);
    }
  }
  printf("Count: %d\n", count);
  return (0);
}

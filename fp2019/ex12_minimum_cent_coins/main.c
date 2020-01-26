#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "dp.h"
#include "greedy.h"

#define N_MAX 100000

int compare_dp_and_greedy(int total, unsigned char *dp_selection, unsigned long *dp_memo) {
  unsigned long cnt_by_dp = minimum_cent_coins_dp(total, dp_selection, dp_memo);
  unsigned long cnt_by_greedy = minimum_cent_coins_greedy(total);
  if (cnt_by_dp != cnt_by_greedy) {
    printf("DP version returns %5d coins, but greedy version returns %5d coins.", cnt_by_dp, cnt_by_greedy);
    return 1;
  }
  return 0;
}

int nsscan(char *command, unsigned long *n) {
  if (command[1] == '\0') {
    printf("Invalid argument: number argument required. eg: m5\n");
    return 1;
  }
  if (sscanf(command, "%*c%lu", n) < 0) {
    return 1;
  };
  if (*n < N_MAX) {
    return 0;
  }
  printf("N (%lu) over N_MAX (%lu)\n", *n, N_MAX);
  return 1;
}

int main() {
  unsigned long *dp_memo = malloc(N_MAX * sizeof(unsigned long));
  unsigned char *dp_selection = malloc(N_MAX);
  for (unsigned long i=0; i<N_MAX; i++) {
    dp_memo[i] = 0;
    dp_selection[i] = 0;
  }

  char command[100];
  unsigned long n;
  while(1) {
    printf("> ");
    if (scanf("%s", &command) < 0) {
      printf("scanf error");
      continue;
    };

    clock_t begin = clock();
    switch (command[0]) {
      case 'q':
        free(dp_memo);
        free(dp_selection);
        return 0;
      case 'm':
        if (nsscan(command, &n) == 0) {
          minimum_cent_coins_dp(n, dp_selection, dp_memo);
          printf("%lu coins, [", dp_memo[n-1]);
          while (n > 0) {
            int coin = dp_selection[n-1];
            printf(" %d", coin);
            n = n - coin;
          }
          printf(" ]\n");
        }
        break;
      case 'c':
        if (nsscan(command, &n) == 0) {
          for (int i = 1; i <= n;  i++) {
            printf("%7d c => ", i);
            if (compare_dp_and_greedy(i, dp_selection, dp_memo) == 0) {
              printf("OK");
            }
            printf("\n");
          }
        }
        break;
      case 'l':
        printf("%zu\n", N_MAX);
        break;
      default:
        printf("Unknown command '%s'.\n", command);
        break;
    }
    printf("%f seconds elapsed.\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
  }
}

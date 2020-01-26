#include <stdio.h>
#include <time.h>

#include "dp.h"
#include "greedy.h"

#define N_MAX 100000

int compare_dp_and_greedy(int total, int *dp_memo, int *dp_selection) {
  int cnt_by_dp = minimum_cent_coins_dp(total, dp_memo, dp_selection);
  int cnt_by_greedy = minimum_cent_coins_greedy(total);
  if (cnt_by_dp != cnt_by_greedy) {
    printf("DP version returns %5d coins, but greedy version returns %5d coins.", cnt_by_dp, cnt_by_greedy);
    return 1;
  }
  return 0;
}

int nsscan(char *command, int *n) {
  if (command[1] == '\0') {
    printf("Invalid argument: number argument required. eg: m5\n");
    return 1;
  }
  sscanf(command, "%*c%d", n);
  if (*n > N_MAX) {
    printf("N (%d) over N_MAX (%d)\n", *n, N_MAX);
    return 1;
  }
  return 0;
}

int main() {
  int dp_memo[N_MAX];
  int dp_selection[N_MAX];
  for (int i=0; i<N_MAX; i++) {
    dp_memo[i] = 0;
    dp_selection[i] = 0;
  }

  while(1) {
    char command[100];
    printf("> ");
    scanf("%s", &command);

    int n;
    clock_t begin = clock();
    switch (command[0]) {
      case 'q':
        return 0;
      case 'm':
        if (nsscan(command, &n) == 0) {
          minimum_cent_coins_dp(n, dp_memo, dp_selection);
          printf("%d coins, [", dp_memo[n-1]);
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
            printf("%7dc => ", i);
            if (compare_dp_and_greedy(i, dp_memo, dp_selection) == 0) {
              printf("OK");
            }
            printf("\n");
          }
        }
        break;
      default:
        printf("Unknown command '%s'.\n", command);
        break;
    }
    printf("%f seconds elapsed.\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
  }
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "dp.h"
#include "greedy.h"

// ~ 20MB 程度 malloc する
#define N_MAX (1000 * 1000 * 20 / (sizeof(unsigned long) + sizeof(unsigned char)))

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
    printf("Invalid argument: sscanf returns error.\n");
    return 1;
  };
  if (*n > N_MAX) {
    printf("N (%lu) over N_MAX (%lu)\n", *n, N_MAX);
    return 1;
  }
  return 0;
}

int main() {
  unsigned long *dp_memo = malloc(N_MAX * sizeof(unsigned long));
  unsigned char *dp_selection = malloc(N_MAX);
  for (unsigned long i = 0; i < N_MAX; i++) {
    dp_memo[i] = 0;
    dp_selection[i] = 0;
  }

  char command[100];
  unsigned long n;
  while(1) {
    printf("> ");
    if (scanf("%s", &command) < 0) {
      printf("scanf error.\n");
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
          printf("%lu coins, ", dp_memo[n-1]);
          char formula[100];
          dp_selection_to_formula(n, dp_selection, formula);
          printf("[ %s ]\n", formula);
        }
        break;
      case 'c':
        if (nsscan(command, &n) == 0) {
          for (unsigned long i = 1; i <= n; i++) {
            printf("\r%7lu c => ", i);
            if (compare_dp_and_greedy(i, dp_selection, dp_memo) == 1) {
              break;
            } else {
              printf("OK");
            }
          }
          printf("\n");
        }
        break;
      case 'l':
        printf("N_MAX: %zu\n", N_MAX);
        break;
      case 'h':
        printf("mcc\n");
        printf("\tq: 終了\n");
        printf("\th: ヘルプ\n");
        printf("\tl: 受けつける数値の最大値を表示\n");
        printf("\tm%%d: 動的計画法アルゴリズムによって N [c] に対して枚数とトレースバックを表示\n");
        printf("\tc%%d: N [c] までの枚数を貪欲法でもDPと同様に解けるか検証\n");
        break;
      default:
        printf("Unknown command '%c'.\n", command[0]);
        break;
    }
    printf("%f seconds elapsed.\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
  }
}

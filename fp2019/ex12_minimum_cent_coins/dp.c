#include <stdio.h>

unsigned long get_i(unsigned long i, unsigned long *memo_minimum_count_of_coin) {
  if (i == 0) {
    return 0;
  }
  return memo_minimum_count_of_coin[i-1];
}

unsigned long minimum_cent_coins_dp(unsigned long n, unsigned char *minimum_coin_selection, unsigned long *memo_minimum_count_of_coin) {
  if (n == 0) {
    return 0;
  }

  for (unsigned long i = 1; i <= n; i++) {
    if (minimum_coin_selection[i-1] != 0) {
      continue;
    }
    char coin = 1;
    unsigned long min = 0;
    if (i <= 1) {
      // memo_minimum_count_of_coin[-1] はないため
      min = 1;
    } else {
      unsigned long by_01 = get_i(i-1, memo_minimum_count_of_coin);
      unsigned long by_05 = i >= 5 ? get_i(i-5, memo_minimum_count_of_coin) : by_01;
      unsigned long by_10 = i >= 10 ? get_i(i-10, memo_minimum_count_of_coin) : by_05;
      unsigned long by_25 = i >= 25 ? get_i(i-25, memo_minimum_count_of_coin) : by_10;

      min = by_01;
      if (min > by_05) min = by_05, coin = 5;
      if (min > by_10) min = by_10, coin = 10;
      if (min > by_25) min = by_25, coin = 25;
      min++;
    }
    minimum_coin_selection[i-1] = coin;
    memo_minimum_count_of_coin[i-1] = min;
  }
  return memo_minimum_count_of_coin[n-1];
}

void dp_selection_to_formula(unsigned long n, char *minimum_coin_selection, char *formula) {
  unsigned long one = 0;
  unsigned long five = 0;
  unsigned long ten = 0;
  unsigned long twenty_five = 0;
  while (n > 0) {
    int coin = minimum_coin_selection[n-1];
    switch (coin) {
      case 1:
        one++;
        break;
      case 5:
        five++;
        break;
      case 10:
        ten++;
        break;
      case 25:
        twenty_five++;
        break;
    }
    n = n - coin;
  }
  sprintf(formula, "1*%lu + 5*%lu + 10*%lu + 25*%lu", one, five, ten, twenty_five);
}

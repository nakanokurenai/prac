unsigned long minimum_cent_coins_dp(unsigned long n, unsigned char *minimum_coin_selection, unsigned long *memo_minimum_count_of_coin) {
  if (n == 0) {
    return 0;
  }
  for (unsigned long i = 1; i <= n; i++) {
    char coin = 1;
    unsigned long min = 0;
    if (i <= 1) {
      // memo_minimum_count_of_coin[-1] はないため
      min = 1;
    } else {
      unsigned long by_01 = memo_minimum_count_of_coin[i-1-1];
      unsigned long by_05 = i >= 5 ? memo_minimum_count_of_coin[i-5-1] : by_01;
      unsigned long by_10 = i >= 10 ? memo_minimum_count_of_coin[i-10-1] : by_05;
      unsigned long by_25 = i >= 25 ? memo_minimum_count_of_coin[i-25-1] : by_10;

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

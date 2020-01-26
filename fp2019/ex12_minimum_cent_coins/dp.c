#include <stdio.h>

int minimum_cent_coins_dp(int n, int *memo_minimum_count_of_coin, int *memo_minimum_coin_selection) {
	if (n == 0) {
		return 0;
	}
	if (memo_minimum_count_of_coin[n-1] != 0) {
		return memo_minimum_count_of_coin[n-1];
	}

	int by_01 = minimum_cent_coins_dp(n-1, memo_minimum_count_of_coin, memo_minimum_coin_selection);
	int by_05 = n >= 5 ? minimum_cent_coins_dp(n-5, memo_minimum_count_of_coin, memo_minimum_coin_selection) : by_01;
	int by_10 = n >= 10 ? minimum_cent_coins_dp(n-10, memo_minimum_count_of_coin, memo_minimum_coin_selection) : by_05;
	int by_25 = n >= 25 ? minimum_cent_coins_dp(n-25, memo_minimum_count_of_coin, memo_minimum_coin_selection) : by_10;

	int min = by_01, coin = 1;
	if (min > by_05) min = by_05, coin = 5;
	if (min > by_10) min = by_10, coin = 10;
	if (min > by_25) min = by_25, coin = 25;

  memo_minimum_coin_selection[n-1] = coin;
	memo_minimum_count_of_coin[n-1] = min + 1;
	return memo_minimum_count_of_coin[n-1];
}

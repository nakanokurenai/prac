int minimum_cent_coins_greedy(int n) {
  int remainder = n, coins = 0;
  coins += remainder / 25;
  remainder = remainder % 25;
  if (remainder == 0) return coins;
  coins += remainder / 10;
  remainder = remainder % 10;
  if (remainder == 0) return coins;
  coins += remainder / 5;
  remainder = remainder % 5;
  if (remainder == 0) return coins;
  coins += remainder / 1;
  remainder = remainder % 1;
  return coins;
}

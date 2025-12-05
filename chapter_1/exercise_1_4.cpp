#include <cstdio>

int sum(int x, int y) {
  return x + y;
}

int main() {
  int my_num_x = -10;
  int my_num_y = 10;
  printf("The sum of %d and %d is %d.\n", my_num_x, my_num_y, sum(my_num_x, my_num_y));
}


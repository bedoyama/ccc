#include <cstdio>

int absolute_value(int x) {
  auto result = x;

  if (result < 0) {
    result = -result;
  }

  return result;
}

int main() {
  int my_num = -10;
  printf("The absolute value of %d is %d.\n", my_num, absolute_value(my_num));
}

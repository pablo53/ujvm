
#include "stdio.h"

union
{
  int value;
  char tab[sizeof(int)];
} test;

int main(int args, char * argv[])
{
  test.value = -2;
  printf("%s", (test.tab[0] == '\xFE') ? "LITTLE_ENDIAN" : "BIG_ENDIAN");
  return 0;
}

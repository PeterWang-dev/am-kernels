#include "klibtest.h"

void test_string(void) {
  test_memcpy();
  test_memove();
  test_memset();
  test_memcmp();
  test_strlen();
  test_strcat();
  test_strcpy();
  test_strncpy();
  test_strcmp();
  test_strncmp();
}

int main() {
  test_string();
  return 0;
}
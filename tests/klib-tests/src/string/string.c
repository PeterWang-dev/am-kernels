#include <klibtest.h>

extern void test_mem(void);
extern void test_str(void);

void test_string(void) {
  test_mem();
  test_str();
}


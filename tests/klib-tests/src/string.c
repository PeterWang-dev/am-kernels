#include <klib.h>

#define N 100
uint8_t bdata[N];

static void reset_data(void) {
  for (int i = 0; i < N; i++) {
    bdata[i] = i + 1; // bdata initialized to 1, 2, 3, ..., N
  }
}

static void check_seq(int l, int r, uint8_t val) {
  for (int i = l; i < r; i++) {
    assert(bdata[i] == val);
    val++;
  }
}

static void check_eq(int l, int r, uint8_t val) {
  for (int i = l; i < r; i++) {
    assert(bdata[i] == val);
  }
}

void test_memcpy(void) {}

void test_memove(void) {}

void test_memset(void) {
  int l, r;
  for (l = 0; l < N; l++) { // enumerate all possible l and r
    for (r = l + 1; r < N; r++) {
      reset_data();
      uint8_t val = (l + r) / 2;
      memset(bdata + l, val, r - l);
      check_seq(0, l, 1);     // left side of the changed area is not modified
      check_eq(l, r, val);    // check the changed area if modified
      check_seq(r, N, r + 1); // right side of the changed area is not modified
    }
  }
}

void test_memcmp(void) {}

void test_strlen(void) {}

void test_strcat(void) {}

void test_strcpy(void) {}

void test_strncpy(void) {}

void test_strcmp(void) {}

void test_strncmp(void) {}
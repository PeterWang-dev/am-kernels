#include <klib.h>

#define MAX_SIZE 128

static void reset_con(unsigned char *data) {
  int i;
  for (i = 0; i < MAX_SIZE; i++) {
    data[i] = MAX_SIZE / 2; // data initialized to MAX_SIZE / 2
  }
}

static void reset_seq(unsigned char *data) {
  int i;
  for (i = 0; i < MAX_SIZE; i++) {
    data[i] = i + 1; // data initialized to 1, 2, 3, ..., MAX_SIZE
  }
}

static void check_seq(unsigned char *data, int l, int r, int init_val) {
  for (int i = l; i < r; i++) {
    if (data[i] != init_val) {
      printf("data[%d] = %d, expected %d\n", i, data[i], init_val - 1);
      for (int j = 0; j < MAX_SIZE; j++) {
        printf("%d ", data[j]);
      }
    }
    assert(data[i] == init_val++);
  }
}

static void check_eq(unsigned char *data, int l, int r, int init_val) {
  for (int i = l; i < r; i++) {
    if (data[i] != init_val) {
      printf("data[%d] = %d, expected %d\n", i, data[i], init_val);
      for (int j = 0; j < MAX_SIZE; j++) {
        printf("%d ", data[j]);
      }
    }
    assert(data[i] == init_val);
  }
}

static void test_memcpy(void) {
  int i, j;
  for (i = 0; i < MAX_SIZE; i++) {
    for (j = i + 1; j < MAX_SIZE; j++) {
      unsigned char src_data[MAX_SIZE];
      unsigned char dst_data[MAX_SIZE];
      reset_seq(src_data);
      reset_con(dst_data);

      memcpy(dst_data + i, src_data + i, j - i);

      check_eq(dst_data, 0, i, MAX_SIZE / 2);
      check_seq(dst_data, i, j, src_data[i]);
      check_eq(dst_data, j, MAX_SIZE, MAX_SIZE / 2);
    }
  }
}

static void test_memove(void) {
  int i, j;
  for (i = 0; i < MAX_SIZE; i++) {
    for (j = i + 1; j < MAX_SIZE; j++) {
      unsigned char data[MAX_SIZE];
      unsigned char val_j, val_mid;
      reset_seq(data);

      val_j = data[j];
      val_mid = data[i + MAX_SIZE - j];
      memmove(data + i, data + j, MAX_SIZE - j);

      check_seq(data, 0, i, 1);
      check_seq(data, i, i + MAX_SIZE - j, val_j);
      check_seq(data, i + MAX_SIZE - j, MAX_SIZE, val_mid);
    }
  }
}

static void test_memset(void) {
  int l, r;
  for (l = 0; l < MAX_SIZE; l++) { // enumerate all possible l and r
    for (r = l + 1; r < MAX_SIZE; r++) {
      unsigned char data[MAX_SIZE];
      char val = (l + r) / 2;
      reset_seq(data);

      memset(data + l, val, r - l);

      check_seq(data, 0, l, 1); // left side of the changed area is not modified
      check_eq(data, l, r, val); // check the changed area if modified
      check_seq(data, r, MAX_SIZE,
                r + 1); // right side of the changed area is not modified
    }
  }
}

static void test_memcmp(void) {
  unsigned char data[MAX_SIZE];
  reset_seq(data);
  assert(memcmp(data, data, 0) == 0);
  assert(memcmp(data, data, MAX_SIZE) == 0);

  int i;
  for (i = 0; i < MAX_SIZE; i++) {
    assert(memcmp(data, data + i, MAX_SIZE - i) <= 0);
    assert(memcmp(data + i, data, MAX_SIZE - i) >= 0);
  }

  unsigned char data1[] = {1, 2, 3, 4, 5, 6};
  unsigned char data2[] = {1, 2, 3, 4, 6};
  assert(memcmp(data1, data2, 5) == data1[4] - data2[4]);
}

void test_mem(void) {
  test_memcpy();
  test_memove();
  test_memset();
  test_memcmp();
}
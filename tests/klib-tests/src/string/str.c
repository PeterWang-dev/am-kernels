#include <klib.h>
#define ABC_SIZE 26

static void reset_str(char *str, char init_char) {
  for (int i = 0; i < ABC_SIZE; i++) {
    str[i] = init_char + i;
  }
  str[ABC_SIZE] = '\0';
}

static void check_seq(char *str, int l, int r, char init_char) {
  for (int i = 0; i < r - l; i++) {
    assert(str[l + i] == init_char + i);
  }
}

static void test_strlen(void) {
  int i;
  for (i = 0; i < ABC_SIZE; i++) {
    char str[ABC_SIZE + 1]; // +1 for '\0'
    reset_str(str, 'a');
    str[i] = '\0';
    assert(strlen(str) == i);
  }
}

static void test_strcat(void) {
  int i, j;
  for (i = 0; i < ABC_SIZE; i++) {
    for (j = 0; j < ABC_SIZE; j++) {
      char str[ABC_SIZE + 1];
      char str_cap[ABC_SIZE + 1];
      char str_cat[ABC_SIZE * 2 + 1];
      reset_str(str, 'a');
      reset_str(str_cap, 'A');
      str_cat[0] = '\0';

      str[i] = '\0';
      str_cap[j] = '\0';
      strcat(str_cat, str);
      check_seq(str_cat, 0, i, 'a');
      strcat(str_cat, str_cap);
      check_seq(str_cat, i, j, 'A');
    }
  }
}

static void test_strcpy(void) {
  int i;
  for (i = 0; i < ABC_SIZE; i++) {
    char str[ABC_SIZE + 1];
    char str_cpy[ABC_SIZE + 1];
    reset_str(str, 'a');
    str[i] = '\0';

    strcpy(str_cpy, str);
    check_seq(str_cpy, 0, i, 'a');
  }
}

static void test_strncpy(void) {
  int i, j;
  for (i = 0; i < ABC_SIZE; i++) {
    for (j = 0; j < i; j++) {
      char str[ABC_SIZE + 1];
      char str_cpy[ABC_SIZE + 1];
      reset_str(str, 'a');
      str[i] = '\0';

      strncpy(str_cpy, str, j);
      check_seq(str_cpy, 0, j, 'a');
    }
  }
}

static void test_strcmp(void) {
  char str_cap[ABC_SIZE + 1];
  reset_str(str_cap, 'A');
  assert(strcmp(str_cap, str_cap) == 0);

  char str[ABC_SIZE + 1];
  reset_str(str, 'a');
  assert(strcmp(str_cap, str) < 0);
  assert(strcmp(str, str_cap) > 0);

  char *str_part = "ABC";
  assert(strcmp(str_cap, str_part) > 0);

  char *str_part_neq = "ABCDA";
  assert(strcmp(str_cap, str_part_neq) > 0);
}

static void test_strncmp(void) {
  char str[ABC_SIZE + 1];
  reset_str(str, 'a');
  int i;
  for (i = 0; i < ABC_SIZE; i++) {
    assert(strncmp(str, str, i) >= 0);
  }
}

void test_str(void) {
  test_strncpy(); // BUG: Segmentation fault occurs here.
  return;
  test_strlen();
  test_strcat();
  test_strcpy();
  test_strncpy();
  test_strcmp();
  test_strncmp();
}
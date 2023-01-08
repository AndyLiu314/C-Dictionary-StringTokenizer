// WRITE YOUR OWN
// Build  gcc -I ./include/ unit_test_strcmp.c str_cmp.c -o unit_test_str_cmp.bin
#include <acutest.h>
#include <stdint.h>
#include <str_cmp.h>

struct TestVector {
  const index;
  const char *s1;
  const char *s2;
  int expected;
};

struct TestVector test_vectors[] = {
    // Inorder,Preorder,Postorder(Expected)
    {0, "a*&", "b", 1},
    {1, "ap    e", "appl@", 1},
    {2, "apple   and oranges $", "apple   and oranges $", 0},
    {3, "123456   ", "123456", 1},
    {4, "     ", "     ", 0},
    {5, "andyliao", "andyliao", 0}};
    

void test(void) {
  for (int i = 0; i < 6; i++) {
    int result = my_str_cmp(test_vectors[i].s1, test_vectors[i].s2);

    TEST_CHECK(result == test_vectors[i].expected);
    TEST_MSG("String s1: %s", test_vectors[i].s1);
    TEST_MSG("String s2: %s", test_vectors[i].s2);
  }
}

TEST_LIST = {{"Test", test}, {NULL, NULL}};

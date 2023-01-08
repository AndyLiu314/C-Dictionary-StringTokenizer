#include "str_cmp.h"

/**
 * @brief Compare two strings
 *
 * @param s1
 * @param s2
 * @return int
 */
int my_str_cmp(const char *s1, const char *s2) {
  // TODO: Compare two character arrays. return 0 if they match, 1 otherwise
  // You can assume that s1 and s2 are null terminated strings.
  // WARNING: strings could potentially be of different lengths
  // e.g., "apple" does not match "apple " (which includes the extra space).
  // Value to be returned will be 1.
  // You cannot use any of the string helper functions including strlen and
  // strncmp, strcmp.

  int i = 0;
  while (s1[i] == s2[i]) {
    if(s1[i]=='\0' && s2[i]=='\0') {
      return 0;
    }
    i++;
  }
  return 1;
}

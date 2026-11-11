#include "security.h"
#include <stdio.h>

int main(void) {
  Security_Check("99998");
  Security_Check("12345");
  printf("Test sai: %d\n", Security_Check("99998"));  // Mong đợi in ra 0
  printf("Test dung: %d\n", Security_Check("12345")); // Mong đợi in ra 1
}

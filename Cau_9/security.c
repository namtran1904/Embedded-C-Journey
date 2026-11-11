#include "security.h"
#include <string.h>
static char security_password[] = "12345";
uint8_t Security_Check(const char *password) {
  uint8_t compare = strcmp(security_password, password);
  if (!compare) {
    return 1;
  }
  return 0;
}

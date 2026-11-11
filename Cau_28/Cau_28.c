#include <stdint.h>
#include <stdio.h>

void Scramble_Buffer(uint8_t *buffer, uint32_t length, uint8_t key) {
  if (buffer == NULL || length == 0) {
    return;
  } else {
    for (uint32_t i = 0; i < length; i++) {
      uint8_t vise_key = (uint8_t)(i & 0xFF);
      buffer[i] = buffer[i] ^ key ^ vise_key;
    }
  }
}

void main(void) {
  uint8_t data[] = "19042004Vominhvy#*#*";
  uint32_t length = sizeof(data);
  printf("Chuoi ban dau: %s\n", data);
  uint8_t key = 0x3E;
  Scramble_Buffer(data, length, key);
  printf("Ma hoa chuoi ban dau (Hex Dump): ");
  for (uint32_t i = 0; i < length; i++) {
    printf("%02X ", data[i]);
  }
  printf("\n");
  Scramble_Buffer(data, length, key);
  printf("Giai ma chuoi: %s\n", data);
}

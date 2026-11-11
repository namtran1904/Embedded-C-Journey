#include <stdint.h>
#include <stdio.h>
#define MAX_ARRAY_SOURCE 100

uint16_t *Get_Sub_Array(uint16_t *Source, uint8_t start_idx, uint8_t length) {
  if (Source == NULL) {
    return NULL;
  } else {
    uint16_t total_length = start_idx + length;
    if (total_length > MAX_ARRAY_SOURCE) {
      return NULL;
    }
    return start_idx + Source;
  }
}

void main(void) {
  uint16_t Source_Array[100];
  uint8_t i = 0;
  for (; i < MAX_ARRAY_SOURCE; i++) {
    Source_Array[i] = i;
  }
  uint16_t *sub = Get_Sub_Array(Source_Array, 20, 5);
  if (sub != NULL) {
    for (uint8_t i = 0; i < 5; i++) {
      printf("Phan tu thu %d cua mang con %d\n", i, *(sub + i));
    }
  }
  uint16_t *sub_2 = Get_Sub_Array(Source_Array, 95, 10);
  if (sub_2 == NULL) {
    printf("Test 2: Vuot bien thanh cong, da chan lai bang NULL!\n");
  }
}

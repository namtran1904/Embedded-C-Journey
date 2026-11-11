#include <stdint.h>
#include <stdio.h>

typedef enum { STATE_WAIT_55, STATE_WAIT_AA, STATE_WAIT_01 } State_t;

uint8_t Detect_Pattern(uint8_t mot) {
  static State_t current_state = STATE_WAIT_55;
  switch (current_state) {
  case STATE_WAIT_55:
    if (mot == 0x55) {
      current_state = STATE_WAIT_AA;
    } else {
      current_state = STATE_WAIT_55;
    }
    break;

  case STATE_WAIT_AA:
    if (mot == 0xAA) {
      current_state = STATE_WAIT_01;
    } else if (mot == 0x55) {
      current_state = STATE_WAIT_AA;
    } else {
      current_state = STATE_WAIT_55;
    }
    break;

  case STATE_WAIT_01:
    if (mot == 0x01) {
      current_state = STATE_WAIT_55;
      return 1;
    } else {
      current_state = STATE_WAIT_55;
    }
    break;
  }
  return 0;
}

int main(void) {
  uint8_t uart_stream[] = {0x10, 0x20, 0x55, 0x30, 0x55, 0xAA, 0x99, 0x55,
                           0xAA, 0x01, 0x00, 0x11, 0x55, 0x55, 0xAA, 0x01};

  for (uint8_t i = 0; i < sizeof(uart_stream); i++) {
    uint8_t pattern = Detect_Pattern(uart_stream[i]);
    if (pattern) {
      printf("PHAT HIEN PATTERN TAI VI TRI BYTE: %d\n", i);
    }
  }
  return 0;
}

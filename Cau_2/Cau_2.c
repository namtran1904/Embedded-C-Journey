#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BIT_EN 0
#define SET_BIT_ON 1U

#define BIT_RES_START 4
#define RES_0_ON 0U << 4
#define RES_1_ON 1U << 4
#define RES_2_ON 2U << 4
#define RES_3_ON 3U << 4

#define BIT_ERR 15
#define BIT_ERR_ON 1U

volatile uint32_t DISP_CR = 0x00000000;

void Display_Enable(void) { DISP_CR |= SET_BIT_ON << BIT_EN; }

void Display_Resolution(uint8_t res_val) {
  DISP_CR &= ~(RES_3_ON);
  uint32_t res_set = ((res_val & 0x03U) << BIT_RES_START);
  DISP_CR = res_set;
}

bool Display_CheckError() {
  uint32_t error_check = DISP_CR & (BIT_ERR_ON << BIT_ERR);
  if (error_check) {
    return true;
  }
  return false;
}

int main(void) {
  printf("Ban dau: %08X\n", DISP_CR);

  Display_Enable();

  Display_Resolution(2);
  printf("Set do phan giai: %08X\n", DISP_CR);

  if (Display_CheckError()) {
    printf("Trang thai: CO LOI!\n");
  } else {
    printf("Trang thai: BINH THUONG.\n");
  }

  return 0;
}

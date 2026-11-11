#include <stdint.h>
#include <stdio.h>

typedef struct __attribute__((packed)) {
  uint8_t start_byte;
  uint8_t cmd_id;
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
  uint8_t status;
  uint8_t stop_byte;
} Goi_tin_t;

void Giai_ma_goi_tin(const uint8_t *raw_data) {
  const Goi_tin_t *temp = (const Goi_tin_t *)raw_data;
  if (temp->start_byte != 0xAA || temp->stop_byte != 0x55) {
    printf("Goi tin loi!");
    return;
  }
  printf("Ma lenh(HEX Dump): ");
  printf("%02X", temp->cmd_id);
  printf("\n");

  printf("Goc nghieng X: %d\n", temp->gyro_x);

  printf("Goc nghieng Y: %d\n", temp->gyro_y);

  printf("Goc nghieng Z: %d\n", temp->gyro_z);

  printf("Trang thai(HEX Dump): ");
  printf("%02X", temp->status);
  printf("\n");

  printf("Kich thuoc con tro temp: %zu byte\n", sizeof(temp));
  printf("Kich thuoc struct ma temp tro toi: %zu byte\n", sizeof(*temp));
}
int main(void) {
  uint8_t raw_data[] = {0xAA, 0x01, 0x2C, 0x01, 0xF4,
                        0x00, 0x1F, 0X30, 0x00, 0x55};
  printf("Size cua struct: %zu byte\n", sizeof(Goi_tin_t));

  Giai_ma_goi_tin(raw_data);

  return 0;
}

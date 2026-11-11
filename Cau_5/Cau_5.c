// Critical section(vùng làm việc nguy hiểm) bọc hàm vào giữa enter và exit để
// không bị ngắt hàm thay đổi giá trị chỉ bọc hàm ghi/đọc các biến dùng chung
// Nesting count
#include <stdint.h>
#include <stdio.h>

static uint8_t g_interupt_enabled = 1;
static uint8_t g_nesting_count = 0;

void Enter_Critical(void) {
  if (g_nesting_count == 0) {
    g_interupt_enabled = 0;
  }
  g_nesting_count++;
}

void Exit_Critical(void) {
  if (g_nesting_count > 0) {
    g_nesting_count--;
    if (g_nesting_count == 0) {
      g_interupt_enabled = 1;
    }
  }
}

typedef struct {
  volatile uint8_t Pos_x;
  volatile uint8_t Pos_y;
} RobotPos_t;

RobotPos_t Pos = {20, 10};

void Mock_ISR_Update_Pos(uint32_t new_val_x, uint32_t new_val_y) {
  if (g_interupt_enabled) {
    Pos.Pos_x = new_val_x;
    Pos.Pos_y = new_val_y;
    printf("[ISR]: Da cap nhat toa do thanh cong!!\n");
  } else {
    printf("[ISR Blovked]: Ngat da bi chan lai!!\n");
  }
}

void Sub_Task(void) {
  printf("[Sub_Task]: Goi Enter_Critical\n");
  Enter_Critical();
  printf("[Sub_Task]: Nesting = %d, Ngat = %d\n", g_nesting_count,
         g_interupt_enabled);

  Mock_ISR_Update_Pos(50, 50);

  printf("[Sub_Task]: Goi Exit_Critical\n");
  Exit_Critical();
  printf("[Sub_Task]: Nesting = %d, Ngat = %d\n", g_nesting_count,
         g_interupt_enabled);
}

int main(void) {
  uint8_t temp_x, temp_y;

  // Case1:
  temp_x = Pos.Pos_x;
  Mock_ISR_Update_Pos(12, 15);
  temp_y = Pos.Pos_y;
  printf("[x,y] = [%d,%d]\r\n", temp_x, temp_y);
  printf("\n");

  // Case2:
  printf("[Task]: Goi Enter_Critical\n");
  Enter_Critical();
  printf("[Task]: Nesting = %d, Ngat = %d\n", g_nesting_count,
         g_interupt_enabled);
  temp_x = Pos.Pos_x;
  Mock_ISR_Update_Pos(12, 15);
  temp_y = Pos.Pos_y;
  printf("[x,y] = [%d,%d]\n", temp_x, temp_y);

  printf("[Task]: Goi Exit_Critical\n");
  Exit_Critical();
  printf("[Task]: Nesting = %d, Ngat = %d\n", g_nesting_count,
         g_interupt_enabled);
  printf("[x,y] = [%d,%d]\n", temp_x, temp_y);
  printf("\n");

  // Case3:
  printf("[Task]: Goi Enter_Critical\n");
  Enter_Critical();
  printf("[Main]: Da khoa tang 1\n");
  printf("Nesting = %d, Ngat = %d\n", g_nesting_count, g_interupt_enabled);

  Sub_Task();
  printf("[Main]: Sub_Task da thoat ra!\n");
  printf("[Main]: Nesting = %d, Ngat = %d\n", g_nesting_count,
         g_interupt_enabled);

  Mock_ISR_Update_Pos(99, 99);

  printf("[Task]: Goi Exit_Critical\n");
  Exit_Critical();
  printf("[Main]: Da mo khoa hoan toan\n");
  printf("Nesting = %d, Ngat = %d\n", g_nesting_count, g_interupt_enabled);

  return 0;
}

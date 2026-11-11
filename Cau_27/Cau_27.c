#include <stdint.h>
#include <stdio.h>

typedef void (*ButtonCallBack_t)(void);

typedef struct {
  volatile uint8_t pin;
  volatile uint8_t last_state;
  ButtonCallBack_t on_press_cb;
} Button_t;

void Button_Init(Button_t *button, uint8_t pin) {
  button->pin = pin;
  button->last_state = 0;
  button->on_press_cb = NULL;
}

void Button_Register_CallBack(Button_t *button, ButtonCallBack_t cb) {
  button->on_press_cb = cb;
}

void Button_Update(Button_t *button, uint8_t current_state) {
  if (button->last_state == 0 && current_state == 1) {
    if (button->on_press_cb != NULL) {
      button->on_press_cb();
    }
  }
  button->last_state = current_state;
}

void Emergency_Stop(void) { printf("Da dung khan cap robot!!"); }

void Toggle_Sensor(void) { printf("Da bat/tat cam bien sensor!!"); }

void main(void) {
  Button_t btn1;
  Button_Init(&btn1, 3);
  Button_Register_CallBack(&btn1, Emergency_Stop);

  Button_Update(&btn1, 0);
  printf("\n--- Test bam lan 1 ---\n");
  Button_Update(&btn1, 1);

  Button_Update(&btn1, 1);
  Button_Update(&btn1, 0);

  printf("\n--- Test bam lan 2 ---\n");
  Button_Update(&btn1, 1);

  printf("\n--- Doi tinh nang nut sang Toggle Sensor ---\n");
  Button_Register_CallBack(&btn1, Toggle_Sensor);

  Button_Update(&btn1, 0);
  Button_Update(&btn1, 1);
}

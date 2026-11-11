#include <stdint.h>
#include <stdio.h>

typedef enum {
  EVENT_KEY_DOWN,
  EVENT_KEY_UP,
  EVENT_KEY_ENTER,
  EVENT_KEY_MAX
} Event_t;

void On_Key_Up(void) { printf("DA NHAN PHIM: UP!!\n"); }

void On_Key_Down(void) { printf("DA NHAN PHIM: DOWN!!\n"); }

void On_Key_Enter(void) { printf("DA NHAN PHIM: ENTER!!\n"); }

typedef void (*EventHandler_t)(void);
EventHandler_t event_table[EVENT_KEY_MAX] = {
    On_Key_Up,
    On_Key_Down,
    On_Key_Enter,
};

void Event_Dispatcher(Event_t evt) {
  if (evt < 0 || evt >= EVENT_KEY_MAX) {
    return;
  } else {
    event_table[evt]();
  }
}

int main(void) {
  Event_Dispatcher(EVENT_KEY_UP);
  Event_Dispatcher(EVENT_KEY_DOWN);
  Event_Dispatcher(EVENT_KEY_ENTER);
  Event_Dispatcher((Event_t)99);
  return 0;
}

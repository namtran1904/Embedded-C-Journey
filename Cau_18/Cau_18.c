#include <stdint.h>
#include <stdio.h>

typedef struct {
  volatile uint8_t *buffer;
  volatile uint32_t head;
  volatile uint32_t tail;
  volatile uint32_t capacity;
  volatile uint32_t count;
} Ring_Buffer_t;

void Ring_Buffer_Init(Ring_Buffer_t *rb, uint8_t *storage, uint32_t capacity) {
  rb->buffer = storage;
  rb->capacity = capacity;
  rb->head = 0;
  rb->tail = 0;
  rb->count = 0;
}

uint8_t Buffer_Push(Ring_Buffer_t *rb, uint8_t data) {
  if (rb->count == rb->capacity) {
    return 0;
  } else {
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count += 1;
  }
  return 1;
}

uint8_t Buffer_Pop(Ring_Buffer_t *rb, uint8_t *data) {
  if (rb->count == 0) {
    return 0;
  } else {
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count -= 1;
  }
  return 1;
}

int main(void) {
  uint8_t raw_ram[5] = {0};
  Ring_Buffer_t rb;
  Ring_Buffer_Init(&rb, raw_ram, 5);

  uint8_t data[5] = {0x10, 0x20, 0x30, 0x40, 0x50};

  // Case1:
  printf("Test day 5 byte vao buffer\n");
  for (uint8_t i = 0; i < 5; i++) {
    Buffer_Push(&rb, data[i]);
    printf("Day thanh cong byte thu %d\n", (i + 1));
  }
  printf("\n");

  // Case2:
  printf("Test do tran buffer\n");
  if (Buffer_Push(&rb, 0x99) == 0) {
    printf("Buffer da day, tu choi byte tiep theo!\n");
  }
  printf("\n");

  // Case3:
  printf("Rut 2 byte ra khoi buffer\n");
  uint8_t read_val;
  for (uint8_t i = 0; i < 2; i++) {
    if (Buffer_Pop(&rb, &read_val)) {
      printf("Rut thanh cong: 0x%02X (Con lai = %d)\n", read_val, rb.count);
    }
  }
  printf("\n");

  // Case4:
  printf("Day them 2 byte de kiem tra xoay vong (Wrap-around) \n");
  Buffer_Push(&rb, 0xAA);
  Buffer_Push(&rb, 0xBB);
  printf("Head hien tai dang o vi tri: %d\n", rb.head);
  printf("\n");

  // Case5
  printf("Rut can sach du lieu\n");
  while (Buffer_Pop(&rb, &read_val)) {
    printf("Doc duoc: 0x%02X\n", read_val);
  }
  printf("Buffer da rong hoan toan (Count = %d)!\n", rb.count);

  return 0;
}

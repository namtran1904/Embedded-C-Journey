#include <stdint.h>
#include <stdio.h>

#define INPUT 0
#define OUTPUT 1
#define ALTERNATE 2
#define ANALOG 3

typedef struct {
  volatile uint32_t MODER;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
} GPIO_TypeDef_t;

uint32_t MOCK_GPIOA_RAM[10] = {0};

#define GPIOA ((GPIO_TypeDef_t *)MOCK_GPIOA_RAM)

void Set_Pin_Mode(GPIO_TypeDef_t *GPIOx, uint8_t pin, uint8_t mode) {
  GPIOx->MODER &= ~(0b11 << pin * 2);
  GPIOx->MODER |= (mode << pin * 2);
}

void GPIO_Write_Pin(GPIO_TypeDef_t *GPIOx, uint8_t pin, uint8_t state) {
  if (state == 1) {
    GPIOx->ODR |= (1 << pin);
  } else {
    GPIOx->ODR &= ~(1 << pin);
  }
}

uint8_t GPIO_Read_Pin(GPIO_TypeDef_t *GPIOx, uint8_t pin) {
  if (GPIOA->IDR & (1 << pin)) {
    return 1;
  }
  return 0;
}

int main(void) {
  Set_Pin_Mode(GPIOA, 5, OUTPUT);
  printf("MODER sau khi set pin 5 thanh Output: 0x%08X\n", GPIOA->MODER);

  GPIO_Write_Pin(GPIOA, 5, 1);
  printf("ODR sau khi bat pin 5: 0x%08X\n", GPIOA->ODR);
  GPIO_Write_Pin(GPIOA, 5, 0);
  printf("ODR sau khi tat pin 5: 0x%08X\n", GPIOA->ODR);

  GPIOA->IDR |= (1 << 3);
  uint8_t val = GPIO_Read_Pin(GPIOA, 3);
  printf("Doc pin 3: %d\n", val);

  return 0;
}

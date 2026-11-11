#include <stdint.h>
#include <stdio.h>
#define NUM_CONVERT 32768.0f

int16_t Q15_Mult(int16_t a, int16_t b) {
  int32_t temp_mul = (int32_t)a * b;
  temp_mul = temp_mul >> 15;
  int16_t res = temp_mul;
  return res;
}

int16_t Float_to_Q15(float float_in) {
  int16_t res;
  if (float_in >= 1.0f) {
    res = NUM_CONVERT - 1;
  } else {
    res = float_in * NUM_CONVERT;
  }
  return res;
}

float Q15_to_Float(int16_t q_in) {
  float res = q_in / NUM_CONVERT;
  return res;
}

void Test_Case(float f_a, float f_b) {
  int16_t q_a = Float_to_Q15(f_a);
  int16_t q_b = Float_to_Q15(f_b);
  int16_t res = Q15_Mult(q_a, q_b);
  float res_in_float = Q15_to_Float(res);
  printf("[THANH GHI DAU VAO]: ");
  printf("av= 0x%04X, b = 0x%04X", (uint16_t)q_a, (uint16_t)q_b);
  printf("\n");

  printf("[THANH GHI KET QUA]: ");
  printf("res = 0x%04X", (uint16_t)res);
  printf("\n");

  printf("[GIAI MA KET QUA]: ");
  printf("res = %f", res_in_float);
  printf("\n");
}

int main() {
  Test_Case(0.5, 0.5);
  printf("\n");
  Test_Case(0.75, -0.5);
  printf("\n");
  Test_Case(0.125, 0.25);
  return 0;
}

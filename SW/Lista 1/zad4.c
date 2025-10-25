#include <stdio.h>
#include <stdint.h>

int main() {
    int8_t a, b;
    int16_t c, d;
    int32_t e, f;
    int64_t g, h;
    float i, j;

    scanf("%hhd %hhd", &a, &b);
    int8_t res_add_8 = a + b;
    int8_t res_mul_8 = a * b;
    int8_t res_div_8 = a / b;
    printf("int8: %hhd %hhd %hhd\n", res_add_8, res_mul_8, res_div_8);

    scanf("%hd %hd", &c, &d);
    int16_t res_add_16 = c + d;
    int16_t res_mul_16 = c * d;
    int16_t res_div_16 = c / d;
    printf("int16: %hd %hd %hd\n", res_add_16, res_mul_16, res_div_16);

    scanf("%d %d", &e, &f);
    int32_t res_add_32 = e + f;
    int32_t res_mul_32 = e * f;
    int32_t res_div_32 = e / f;
    printf("int32: %d %d %d\n", res_add_32, res_mul_32, res_div_32);

    scanf("%ld %ld", &g, &h);
    int64_t res_add_64 = g + h;
    int64_t res_mul_64 = g * h;
    int64_t res_div_64 = g / h;
    printf("int64: %ld %ld %ld\n", res_add_64, res_mul_64, res_div_64);

    scanf("%f %f", &i, &j);
    float res_add_f = i + j;
    float res_mul_f = i * j;
    float res_div_f = i / j;
    printf("float: %f %f %f\n", res_add_f, res_mul_f, res_div_f);

    return 0;
}

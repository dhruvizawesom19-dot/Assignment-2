#ifndef CONVERT_H
#define CONVERT_H

#include <stdint.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

#endif // CONVERT_H
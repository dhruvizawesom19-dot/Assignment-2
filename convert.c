#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "convert.h"


void oct_to_bin(const char *oct, char *out) {
    out[0] = '\0';
    for (size_t i = 0; i < strlen(oct); i++) {
        int digit = oct[i] - '0';
        char buf[4];
        snprintf(buf, sizeof(buf), "%03d",
                 ((digit & 4) ? 1 : 0) * 100 +
                 ((digit & 2) ? 1 : 0) * 10 +
                 ((digit & 1) ? 1 : 0));
        strcat(out, buf);
    }
}


void oct_to_hex(const char *oct, char *out) {
    char bin[512] = {0};
    oct_to_bin(oct, bin);


    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[520] = {0};
    for (int i = 0; i < pad; i++) {
        padded[i] = '0';
    }
    strcpy(padded + pad, bin);

    out[0] = '\0';
    for (int i = 0; i < strlen(padded); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = (val << 1) | (padded[i + j] - '0');
        }
        char hexchar[2];
        snprintf(hexchar, sizeof(hexchar), "%X", val);
        strcat(out, hexchar);
    }


    int idx = 0;
    while (out[idx] == '0' && out[idx + 1] != '\0') idx++;
    if (idx > 0) memmove(out, out + idx, strlen(out) - idx + 1);
}


void hex_to_bin(const char *hex, char *out) {
    out[0] = '\0';
    for (size_t i = 0; i < strlen(hex); i++) {
        char c = toupper((unsigned char)hex[i]);
        int digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else digit = 10 + (c - 'A');

        char buf[5];
        snprintf(buf, sizeof(buf), "%04d",
                 ((digit & 8) ? 1 : 0) * 1000 +
                 ((digit & 4) ? 1 : 0) * 100 +
                 ((digit & 2) ? 1 : 0) * 10 +
                 ((digit & 1) ? 1 : 0));
        strcat(out, buf);
    }
}


void to_sign_magnitude(int32_t n, char *out) {
    uint32_t bits;
    if (n < 0) {
        uint32_t mag = (uint32_t)(-n);
        bits = mag | 0x80000000;
    } else {
        bits = (uint32_t)n;
    }

    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (bits & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}


void to_ones_complement(int32_t n, char *out) {
    uint32_t bits;
    if (n >= 0) {
        bits = (uint32_t)n;
    } else {
        bits = ~((uint32_t)(-n));
    }

    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (bits & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}


void to_twos_complement(int32_t n, char *out) {
    uint32_t bits = (uint32_t)n;
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (bits & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}

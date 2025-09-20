#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "convert.h"

void oct_to_bin(const char *oct, char *out){
    if (!oct || !out) return;
    size_t len = strlen(oct);
    size_t pos = 0;

    for (size_t i = 0; i < len; i++) {
        char c = oct[i];
        if (c < '0' || c > '7') { out[0] = '\0'; return; }
        int digit = c - '0';

        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out){

}

void hex_to_bin(const char *hex, char *out){

}

void to_sign_magnitude(int32_t n, char *out) {

}

void to_ones_complement(int32_t n, char *out) {

}

void to_twos_complement(int32_t n, char *out) {

}
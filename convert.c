#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

void oct_to_bin(const char *oct, char *out){
    if(!oct || !out){
        return;
    } 
    size_t len = strlen(oct);
    size_t pos = 0;

    for(size_t i = 0; i < len; i++) {
        char c = oct[i];
        if (c < '0' || c > '7') {
            out[0] = '\0'; return; 
        }
        int digit = c - '0';

        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out){
    if(!oct || !out){
        return;
    }
    size_t octlen = strlen(oct);
    if(octlen == 0){
        out[0] = '\0';
        return;
    }
    size_t bin_capacity = 3 * octlen + 1;
    char *bin = malloc(bin_capacity);
    if(!bin){
        out[0] = '\0'; return;
    }
    oct_to_bin(oct, bin);
    if(bin[0] == '\0'){
        free(bin); out[0] = '\0';
        return;
    }

    size_t binlen = strlen(bin);

    
    int pad = (4 - (binlen % 4)) % 4;
    size_t padded_len = binlen + pad;
    char *padded = malloc(padded_len + 1);
    if(!padded){ 
        free(bin); out[0] = '\0'; return; 
    }
    for(int i = 0; i < pad; i++){
        padded[i] = '0';
    }
    memcpy(padded + pad, bin, binlen);
    padded[padded_len] = '\0';

    
    size_t hex_pos = 0;
    for(size_t i = 0; i < padded_len; i += 4){
        int value = 0;
        for(int b = 0; b < 4; b++){
            value = (value << 1) + (padded[i + b] == '1');
        }
        out[hex_pos++] = (value < 10) ? ('0' + value) : ('A' + (value - 10));
    }
    out[hex_pos] = '\0';

    
    size_t first_nonzero = 0;
    while (first_nonzero < hex_pos && out[first_nonzero] == '0') first_nonzero++;
    if(first_nonzero == hex_pos){
        out[0] = '0'; out[1] = '\0';
    }else if(first_nonzero > 0){
        memmove(out, out + first_nonzero, hex_pos - first_nonzero + 1);
    }

    free(bin);
    free(padded);
}

void hex_to_bin(const char *hex, char *out){
    if(!hex || !out){
        return;
    }
    size_t len = strlen(hex);
    size_t pos = 0;

    for(size_t i = 0; i < len; i++){
        char c = hex[i];
        int value = 0;
        if(c >= '0' && c <= '9'){
            value = c - '0';
        }else if(c >= 'A' && c <= 'F'){
            value = (c - 'A') + 10;
        }else if(c >= 'a' && c <= 'f'){
            value = (c - 'a') + 10;
        }else{
            out[0] = '\0';
            return;
        }
        out[pos++] = (value & 8) ? '1' : '0';
        out[pos++] = (value & 4) ? '1' : '0';
        out[pos++] = (value & 2) ? '1' : '0';
        out[pos++] = (value & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void to_sign_magnitude(int32_t n, char *out) {
    if(!out){
        return;
    }
    uint32_t bits;
    if(n >= 0){
        bits = (uint32_t)n;
    } else {
        int64_t mag = -(int64_t)n;
        uint32_t magnitude = (uint32_t)(mag & 0x7FFFFFFF);
        bits = magnitude | 0x80000000;
    }
    for(int i = 31; i >= 0; i--){
        out[31 - i] = (bits >> i & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_ones_complement(int32_t n, char *out) {
    if(!out){
        return;
    }
    uint32_t bits;
    if (n >= 0) {
        bits = (uint32_t)n;
    } else {
        int64_t mag = -(int64_t)n;
        uint32_t mag32 = (uint32_t)mag;
        bits = ~mag32;
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (bits >> i & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_twos_complement(int32_t n, char *out) {
    if(!out){
        return;
    }
    uint32_t bits = (uint32_t)n;
    for(int i = 31; i >= 0; i--){
        out[31 - i] = (bits >> i & 1) ? '1' : '0';
    }
    out[32] = '\0';
}
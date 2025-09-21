#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

int main(void) {
    FILE *in = fopen("a2_test.txt", "r");
    FILE *out = fopen("output.txt", "w");


    char line[512];

    while (fgets(line, sizeof(line), in)) {
        if (line[0] == '#' || strlen(line) < 2) continue; 

        char func[64], in1[128], in2[128], expected[256], got[256];
        int count = sscanf(line, "%s %s %s %s", func, in1, in2, expected);

        if (count == 3) {
        
            strcpy(expected, in2);
        } else if (count != 4) {
            continue; 
        }

 
        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(in1, got);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(in1, got);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(in1, got);
        } else if (strcmp(func, "twos") == 0) {
            to_twos_complement(atoi(in1), got);
        } else if (strcmp(func, "ones") == 0) {
            to_ones_complement(atoi(in1), got);
        } else if (strcmp(func, "signmag") == 0) {
            to_sign_magnitude(atoi(in1), got);
        } else {
            continue; 
        }

        fprintf(out, "%s %s %s %s\n",
                func, in1, expected,
                strcmp(expected, got) == 0 ? "PASS" : "FAIL");
    }

    fclose(in);
    fclose(out);
    return 0;
}

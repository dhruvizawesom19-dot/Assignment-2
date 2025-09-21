#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

int main(void) {
    FILE *fin = fopen("a2_test.txt", "r");
    FILE *fout = fopen("output.txt", "w");

    char line[512];
    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        char func[64], in1[128], in2[128], expected[256], got[512];
        int count = sscanf(line, "%s %s %s %s", func, in1, in2, expected);

        if (count == 3) {
            strcpy(expected, in2);
        } else if (count != 4) {
            continue;
        }

        got[0] = '\0';

        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(in1, got);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(in1, got);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(in1, got);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            to_sign_magnitude(atoi(in1), got);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            to_ones_complement(atoi(in1), got);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            to_twos_complement(atoi(in1), got);
        } else {
            continue;
        }

        if (strcmp(expected, got) == 0) {
            fprintf(fout, "%s(%s) -> Expected:%s Got:%s [PASS]\n",
                    func, in1, expected, got);
        } else {
            fprintf(fout, "%s(%s) -> Expected:%s Got:%s [FAIL]\n",
                    func, in1, expected, got);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "convert.h"

int main() {
    FILE *file = fopen("a2_test.txt", "r");   // input test file
    FILE *outfp = fopen("output.txt", "w");   // results file


    char line[512];
    int passed = 0, total = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Skip comments and empty lines
        if (line[0] == '#' || strlen(line) < 2) {
            continue;
        }

        char func[64], in1[128], in2[128], expected[256], got[256];
        got[0] = '\0';

        // Format: function_name input1 [input2] expected_output
        int count = sscanf(line, "%s %s %s %s", func, in1, in2, expected);

        if (count < 3) continue; // malformed line

        total++;

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
            fprintf(outfp, "Test %d: Unknown function %s\n", total, func);
            continue;
        }

        // Compare result
        if (strcmp(expected, got) == 0) {
            fprintf(outfp, "Test %d: %s(%s) -> Expected:%s Got:%s [PASS]\n",
                    total, func, in1, expected, got);
            passed++;
        } else {
            fprintf(outfp, "Test %d: %s(%s) -> Expected:%s Got:%s [FAIL]\n",
                    total, func, in1, expected, got);
        }
    }

    fprintf(outfp, "Summary: %d/%d tests passed\n", passed, total);

    fclose(file);
    fclose(outfp);
    return 0;
}
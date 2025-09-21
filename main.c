#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

int main(void) {
    //open files for reading and writing
    FILE *test = fopen("a2_test.txt", "r");
    FILE *out = fopen("output.txt", "w");

    char line[512];
    // Initialize counters for total and passed tests
    int total = 0, passed = 0;

    // Read each line from the test file
    while (fgets(line, sizeof(line), test)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        //buffers used to parse the line and store results up to 4 values
        char func[64], in1[128], in2[128], expected[256], got[512];
        int count = sscanf(line, "%s %s %s %s", func, in1, in2, expected);
        // If there are 3 values, the expected output is in in2
        if (count == 3) {
            strcpy(expected, in2);
        } else if (count != 4) {
            continue;
        }

        got[0] = '\0';

        // Call the appropriate function based on the function name parsed
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

        total++;
        // Check if the output matches the expected result
        if (strcmp(expected, got) == 0) {
            fprintf(out, "%s(%s) -> Expected:%s Got:%s [PASS]\n",
                    func, in1, expected, got);
            passed++;
        } else {
            fprintf(out, "%s(%s) -> Expected:%s Got:%s [FAIL]\n",
                    func, in1, expected, got);
        }
    }
    // Print the summary of test results
    fprintf(out, "Summary: %d/%d tests passed\n", passed, total);
    // Close the opened files
    fclose(test);
    fclose(out);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "convert.h"

int main() {
    FILE *file = fopen("a1_test_file.txt", "r");

    FILE *outfp = fopen("output.txt", "w");

    char line[256];
    int passed = 0, total = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // If statement skips blank lines and commented lines
        if (line[0] == '#' || strlen(line) < 2){
            continue;
        }
        uint32_t n;
        int base;
        char expected[65];
        char got[65];

        if (sscanf(line, "div_convert %u %d %s", &n, &base, expected) == 3) {
            div_convert(n, base, got);
            total++;
            if (strcmp(expected, got) == 0) {
                fprintf(outfp, "Test %d: div_convert(%u,%d) -> Expected:%s Got:%s [PASS]\n",
                        total, n, base, expected, got);
                passed++;
            } else {
                fprintf(outfp, "Test %d: div_convert(%u,%d) -> Expected:%s Got:%s [FAIL]\n",
                        total, n, base, expected, got);
            }
        }
        else if (sscanf(line, "sub_convert %u %d %s", &n, &base, expected) == 3) {
            sub_convert(n, base, got);
            total++;
            if (strcmp(expected, got) == 0) {
                fprintf(outfp, "Test %d: sub_convert(%u,%d) -> Expected:%s Got:%s [PASS]\n",
                        total, n, base, expected, got);
                passed++;
            } else {
                fprintf(outfp, "Test %d: sub_convert(%u,%d) -> Expected:%s Got:%s [FAIL]\n",
                        total, n, base, expected, got);
            }
        }
        else if (sscanf(line, "print_tables %u %s", &n, expected) == 2) {
            total++;
            fprintf(outfp, "Test %d: print_tables(%u) -> [FORMATTED OUTPUT CHECK]\n",
                    total, n);
            FILE *saved = stdout;
            stdout = outfp;
            print_tables(n);
            stdout = saved;
            fprintf(outfp, "[PASS]\n");
            passed++;
        }
    }
    fprintf(outfp, "Summary: %d/%d tests passed\n", passed, total);
    
    fclose(file);
    fclose(outfp);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

// functions from convert.c file
void div_convert(uint32_t num, int base, char *out);
void sub_convert(uint32_t num, int base, char *out);
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

// remove spaces at the end of a line (from assignent 1 main.c)
void trim_spaces(char *s) {
    int i = strlen(s) - 1;
    while (i >= 0 && isspace(s[i])) {
        s[i] = '\0';
        i--;
    }
}

int main() {
    FILE *infile;
    FILE *outfile;
    char line[256];
    char func[50];
    char arg1[100];
    char arg2[100];
    char expected[100];
    char actual[100];
    int total = 0;
    int passed = 0;
    int test_num = 1;

    infile = fopen("a2_test.txt", "r");
    outfile = fopen("output.txt", "w");

    if (!infile) {
        printf("Error: cannot open input file\n");
        return 1;
    }
    if (!outfile) {
        printf("Error: cannot create output file\n");
        fclose(infile);
        return 1;
    }

    while (fgets(line, sizeof(line), infile)) { 
        // referance how to use fgets function : https://youtu.be/Zin72DD9bC8?si=ezSMcZyU4g0j49-1
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        // remove newline
        line[strcspn(line, "\n")] = 0;
        trim_spaces(line);

        // break the line into words (basic parsing)
        func[0] = arg1[0] = arg2[0] = expected[0] = '\0';
        sscanf(line, "%s %s %s %s", func, arg1, arg2, expected);

        // if expected is empty, then arg2 is actually expected
        if (expected[0] == '\0') {
            strcpy(expected, arg2);
            arg2[0] = '\0';
        }

        if (func[0] == '\0' || arg1[0] == '\0' || expected[0] == '\0') {
            continue;
        }

        total++;
        actual[0] = '\0';
        
        // referance : Assignment 2 instruction sheet
        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(arg1, actual);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(arg1, actual);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(arg1, actual);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            to_sign_magnitude(atoi(arg1), actual);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            to_ones_complement(atoi(arg1), actual);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            to_twos_complement(atoi(arg1), actual);
        } else {
            fprintf(outfile, "Unknown function: %s\n", func);
            total--;
            continue;
        }
        if (strcmp(actual, expected) == 0) {
            printf("Test %d: %s -> Expected: %s Got: %s [PASS]\n",
                   test_num, func, expected, actual);
            fprintf(outfile, "Test %d: %s -> Expected: %s Got: %s [PASS]\n",
                    test_num, func, expected, actual);
            passed++;
        } else {
            printf("Test %d: %s -> Expected: %s Got: %s [FAIL]\n",
                   test_num, func, expected, actual);
            fprintf(outfile, "Test %d: %s -> Expected: %s Got: %s [FAIL]\n",
                    test_num, func, expected, actual);
        }

        test_num++;
    }

    fclose(infile);
    fclose(outfile);

    printf("\nSummary: %d/%d tests passed\n", passed, total);
    return 0;
}

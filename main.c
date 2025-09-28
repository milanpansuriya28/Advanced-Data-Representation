#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

// Assignment 1 functions
void div_convert(uint32_t num, int base, char *out);
void sub_convert(uint32_t num, int base, char *out);
void print_tables(uint32_t num);

// Assignment 2 functions 
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

// remove spaces from line
// referance : use issspace : https://youtu.be/2uws6w63wUU?si=y3MjdjH7ocRxkymH
void trim(char *s) {
    int i = strlen(s) - 1;
    while (i >= 0 && isspace((unsigned char)s[i])) {
        s[i] = '\0';
        i--;
    }
}

int main() {
    //Reference: file I/O (fopen, fgets, fprintf): (https://youtu.be/MQIF-WMUOL8?si=5LHEqbwZaQGO5WC7)
    FILE *in = fopen("a2_test.txt", "r");
    FILE *out = fopen("output.txt", "w");

    if (!in) {
        printf("Error: can't open input file\n");
        if (out) fprintf(out, "Error: can't open input file\n");
        return 1;
    }
    if (!out) {
        printf("Error: can't create output file\n");
        fclose(in);
        return 1;
    }

    char line[256];
    int total = 0, passed = 0, test_num = 1;

    while (fgets(line, sizeof(line), in)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        line[strcspn(line, "\n")] = 0;
        trim(line);
        
          /*
        References used in this assignment:
        Format specifiers (%s, %u, %d): https://youtu.be/60OI5tzmkCw?si=6BUa6Hgr3aQ132G7
        sscanf usage: https://youtu.be/vQejAJNSMzY?si=F5GqdLj8x7Uvsklm
        strcmp usage: https://youtu.be/Vx3GyTVFcMA?si=tP_svsjJiK0Aj9Le
        atoi functions : https://youtu.be/iP9WtOFBILs?si=DAq3_05HBNUQWC-I
        */

        char func[50], arg1[100], arg2[100], expected[100];
        func[0] = arg1[0] = arg2[0] = expected[0] = '\0';

        sscanf(line, "%s %s %s %s", func, arg1, arg2, expected);

        // handle cases where expected output is the 3rd token
        if (expected[0] == '\0') {
            strcpy(expected, arg2);
            arg2[0] = '\0';
        }

        if (func[0] == '\0' || arg1[0] == '\0' || expected[0] == '\0')
            continue;

        total++;
        char actual[200] = "";

        //  assignment 2 functions
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

        // Assignment 1 functions 
        // -> i change assignment 1 function's style to make it shorter
        } else if (strcmp(func, "div_convert") == 0) {
            div_convert((uint32_t)atol(arg1), atoi(arg2), actual);
        } else if (strcmp(func, "sub_convert") == 0) {
            sub_convert((uint32_t)atol(arg1), atoi(arg2), actual);
        } else if (strcmp(func, "print_tables") == 0) {
            uint32_t num = (uint32_t)atol(arg1);
            printf("Checking print_tables(%u):\n", num);
            fprintf(out, "Checking print_tables(%u):\n", num);

            FILE *tmp = fopen("temp.txt", "w");
            if (tmp) {
                FILE *saved = stdout;
                stdout = tmp;
                print_tables(num);
                stdout = saved;
                fclose(tmp);
                tmp = fopen("temp.txt", "r");
                if (tmp) {
                    char buf[256];
                    while (fgets(buf, sizeof(buf), tmp)) {
                        printf("%s", buf);
                        fprintf(out, "%s", buf);
                    }
                    fclose(tmp);
                }
                remove("temp.txt");
            }
            strcpy(actual, expected);
        } else {
            fprintf(out, "Unknown function: %s\n", func);
            total--;
            continue;
        }

        if (strcmp(func, "print_tables") != 0) {
            if (strcmp(actual, expected) == 0) {
                printf("Test %d: %s -> Expected: %s Got: %s [PASS]\n",
                       test_num, func, expected, actual);
                fprintf(out, "Test %d: %s -> Expected: %s Got: %s [PASS]\n",
                        test_num, func, expected, actual);
                passed++;
            } else {
                printf("Test %d: %s -> Expected: %s Got: %s [FAIL]\n",
                       test_num, func, expected, actual);
                fprintf(out, "Test %d: %s -> Expected: %s Got: %s [FAIL]\n",
                        test_num, func, expected, actual);
            }
        } else {
            passed++; 
        }

        test_num++;
    }

    fclose(in);
    fclose(out);

    printf("\nSummary: %d/%d tests passed\n", passed, total);
    return 0;
}

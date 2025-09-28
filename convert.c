#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

// reverse a string (function from assignment 1)
void reverse_str(char *s) {
    int len = strlen(s);
    int i;
    for (i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

//using division algorithm from assignment 1
void div_convert(uint32_t n, int base, char *out) {
    char temp[65];// Temporary buffer
    int pos = 0;

 // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }
    
  
    while (n > 0) {  // Extract digits from right to left
        int remainder = n % base;
        n = n / base;
        
        // Convert to character
        if (remainder < 10) {
            temp[pos++] = '0' + remainder;
        } else {
            temp[pos++] = 'A' + (remainder - 10);
        }
    }
    temp[pos] = '\0'; // Null terminate
    
    // I Reverse the result to get correct order
    reverse_str(temp);
    strcpy(out, temp);
}


// octal to binary
// referance : https://youtu.be/vIoP131rdgY?si=7wq2gMMMp133zSLR
void oct_to_bin(const char *oct, char *out) {
    const char *map[8] = {
        "000", "001", "010", "011",
        "100", "101", "110", "111"
    };
    int i = 0;      // index input string
    int k = 0;      // index output string

    while (i < (int)strlen(oct)) {
        int d = oct[i] - '0';
        if (d >= 0 && d <= 7) {
            strcpy(out + k, map[d]);
            k += 3;       
        }
        i++;
    }

    out[k] = '\0';  // null-terminate the result
}


// octal to hex with usee of binary
void oct_to_hex(const char *oct, char *out) {
    char bin[100];
    char padded[100];
    int len, i, pad;
    const char hexchars[] = "0123456789ABCDEF";

    oct_to_bin(oct, bin);
    len = strlen(bin);
    pad = (4 - (len % 4)) % 4;

    for (i = 0; i < pad; i++) {
        padded[i] = '0';
    }
    padded[pad] = '\0';
    strcat(padded, bin);

    len = strlen(padded);
    int pos = 0;
    int started = 0;

    for (i = 0; i < len; i += 4) {
        int v = 0;
        int j;
        for (j = 0; j < 4; j++) {
            v = (v << 1) | (padded[i + j] - '0');
        }
        if (v != 0 || started || i == len - 4) {
            out[pos++] = hexchars[v];
            started = 1;
        }
    }
    if (pos == 0) {
        out[pos++] = '0';
    }
    out[pos] = '\0';
}

// hex to binary
void hex_to_bin(const char *hex, char *out) {
    const char *map[16] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };
    int i, k = 0;
    int started = 0;
    for (i = 0; i < (int)strlen(hex); i++) {
        char c = toupper(hex[i]);
        int d;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'A' && c <= 'F') d = 10 + (c - 'A');
        else continue;

        if (d != 0 || started || i == (int)strlen(hex) - 1) {
            strcpy(out + k, map[d]);
            k += 4;
            started = 1;
        }
    }
    if (k == 0) {
        strcpy(out, "0000");
    } else {
        out[k] = '\0';
    }
}

// helper to make 32 bit binary
void int_to_bin32(uint32_t n, char *out) {
    int i;
    for (i = 31; i >= 0; i--) {
        out[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

// sign magnitude
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        int_to_bin32((uint32_t)n, out);
    } else {
        int_to_bin32((uint32_t)(-n), out);
        out[0] = '1';
    }
}

// ones complement
// referance : Assignment 2 instruction sheet
// i learned consept from https://youtu.be/kzw9oVz1rjw?si=twSC0W6DRkwtvGYz
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        int_to_bin32((uint32_t)n, out);
    } else {
        uint32_t p = (uint32_t)(-n);
        uint32_t one = ~p;
        int_to_bin32(one, out);
    }
}

// twos complement
void to_twos_complement(int32_t n, char *out) {
    int_to_bin32((uint32_t)n, out);
}

// simple wrapper
void sub_convert(uint32_t n, int base, char *out) {
    div_convert(n, base, out);
}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);
}
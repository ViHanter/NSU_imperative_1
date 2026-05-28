#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 65536

char buf[BUFFER_SIZE];
int buf_ptr = 0;
int buf_len = 0;
FILE *in;

char next_char() {
    if (buf_ptr >= buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, in);
        buf_ptr = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_ptr++];
}

long long read_long() {
    char c = next_char();
    while (c != EOF && c <= ' ') {
        c = next_char();
    }
    if (c == EOF) return 0;
    
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = next_char();
    } else if (c == '+') {
        c = next_char();
    }
    
    long long res = 0;
    while (c >= '0' && c <= '9') {
        res = res * 10 + (c - '0');
        c = next_char();
    }
    return res * sign;
}

int main() {
    in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    long long n = read_long();
    long long m = read_long();

    long long current_sum = 0;
    for (long long i = 0; i < n; i++) {
        long long val = read_long();
        current_sum = (current_sum + val) % m;
    }

    current_sum = (current_sum % m + m) % m;

    fprintf(out, "%lld\n", current_sum);

    fclose(in);
    fclose(out);
    return 0;
}

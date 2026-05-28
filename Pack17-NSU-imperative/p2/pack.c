#include <stdarg.h>
#include <string.h>
#include "pack.h"

int pack(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int total = 0;
    char *ptr = buffer;

    while (*format) {
        if (*format == '%') {
            format++;

            // %d
            if (*format == 'd') {
                int val = va_arg(args, int);

                if (buffer) {
                    memcpy(ptr, &val, sizeof(int));
                    ptr += sizeof(int);
                }

                total += sizeof(int);
            }
            // %lf
            else if (*format == 'l' && *(format + 1) == 'f') {
                double val = va_arg(args, double);

                if (buffer) {
                    memcpy(ptr, &val, sizeof(double));
                    ptr += sizeof(double);
                }

                total += sizeof(double);
                format++; // пропускаем 'f'
            }
            // %s
            else if (*format == 's') {
                char *str = va_arg(args, char *);
                int len = strlen(str) + 1; // включая '\0'

                if (buffer) {
                    memcpy(ptr, str, len);
                    ptr += len;
                }

                total += len;
            }
        }

        format++;
    }

    va_end(args);
    return total;
}
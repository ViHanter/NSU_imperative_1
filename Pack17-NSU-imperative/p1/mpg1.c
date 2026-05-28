#include <stdio.h>
#include <stdint.h>

int main() {
    printf("Compiler: ");
    #if defined(__clang__)
        printf("clang\n");
    #elif defined(__TINYC__)
        printf("TCC\n");
    #elif defined(__GNUC__) || defined(__GNUG__)
        printf("GCC\n");
    #elif defined(_MSC_VER)
        printf("MSVC\n");
    #endif

    printf("Bitness: ");
    #if INTPTR_MAX == INT64_MAX
        printf("64\n");
    #elif INTPTR_MAX == INT32_MAX
        printf("32\n");
    #endif

    printf("Asserts: ");
    #ifdef NDEBUG
        printf("disabled");
    #else
        printf("enabled");
    #endif
    return 0;
}

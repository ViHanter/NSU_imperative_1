#include <stdio.h>
#include <string.h>

/*
gcc main.c -o main
clang main.c -o main
cl main.c /Fe:program.exe
tcc main.c -o program.exe

Флаг	Описание
-o [name]	Задает имя исполняемого файла (для gcc, clang, tcc).
-Wall	Включает большинство предупреждений об ошибках в коде.
-O2 / -O3	Включает оптимизацию кода для повышения скорости работы.
/Fe:[name]	Задает имя выходного файла для компилятора cl.

*/

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char line[101];
    fgets(line,101,stdin);

    int i = 0;
    while (line[i] != '\0') {

        while (line[i] == ' ') {
            i++;
        }

        if (line[i] == '\0') {
            break;
        }

        if (line[i] == '"') {
            i++;
            printf("[");
            while (line[i] != '"' && line[i] != '\0') {
                putchar(line[i]);
                i++;
            }
            printf("]\n");
            if (line[i] == '"') {
                i++;
            }
        }

        else {
            printf("[");
            while (line[i] != ' ' && line[i] != '\0') {
                putchar(line[i]);
                i++;
            }
            printf("]\n");
        }
    }

    return 0;
}
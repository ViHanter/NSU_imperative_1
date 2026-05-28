#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 31
#define MAX_COUNTRY 11
#define MAX_MOVIE 21

typedef struct {
    char name[MAX_NAME];
    int birth_year;
    char country[MAX_COUNTRY];
} BioRecord;

typedef struct {
    char actor_name[MAX_NAME];
    char movie_name[MAX_MOVIE];
} MovieRecord;

// Функция сравнения для сортировки BioRecord по имени
int cmp_bio(const void *a, const void *b) {
    return strcmp(((BioRecord*)a)->name, ((BioRecord*)b)->name);
}

// Бинарный поиск первой записи с именем >= key
int lower_bound(BioRecord *arr, int n, const char *key) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (strcmp(arr[mid].name, key) < 0) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

// Чтение строки в кавычках
void read_quoted_string(char *dest, FILE *f) {
    char c;
    int i = 0;
    fscanf(f, " \"%c", &c);
    dest[i++] = c;
    while (1) {
        c = fgetc(f);
        if (c == '"') break;
        dest[i++] = c;
    }
    dest[i] = '\0';
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d\n", &N);

    BioRecord *bio = (BioRecord*)malloc(N * sizeof(BioRecord));
    for (int i = 0; i < N; i++) {
        read_quoted_string(bio[i].name, stdin);
        scanf("%d", &bio[i].birth_year);
        read_quoted_string(bio[i].country, stdin);
        // пропуск \n
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
    }

    scanf("%d\n", &M);

    MovieRecord *movie = (MovieRecord*)malloc(M * sizeof(MovieRecord));
    for (int i = 0; i < M; i++) {
        read_quoted_string(movie[i].actor_name, stdin);
        read_quoted_string(movie[i].movie_name, stdin);
        // пропуск \n
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
    }

    // Сортируем BioRecord по имени
    qsort(bio, N, sizeof(BioRecord), cmp_bio);

    // Обработка JOIN
    for (int i = 0; i < M; i++) {
        int pos = lower_bound(bio, N, movie[i].actor_name);
        // Проверяем все записи с таким именем
        while (pos < N && strcmp(bio[pos].name, movie[i].actor_name) == 0) {
            printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                   bio[pos].name, bio[pos].birth_year, bio[pos].country,
                   movie[i].actor_name, movie[i].movie_name);
            pos++;
        }
    }

    free(bio);
    free(movie);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
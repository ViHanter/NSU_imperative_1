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

int cmp_bio(const void *a, const void *b) {
    return strcmp(((BioRecord*)a)->name, ((BioRecord*)b)->name);
}

int cmp_movie(const void *a, const void *b) {
    return strcmp(((MovieRecord*)a)->actor_name, ((MovieRecord*)b)->actor_name);
}

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
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
    }

    scanf("%d\n", &M);

    MovieRecord *movie = (MovieRecord*)malloc(M * sizeof(MovieRecord));
    for (int i = 0; i < M; i++) {
        read_quoted_string(movie[i].actor_name, stdin);
        read_quoted_string(movie[i].movie_name, stdin);
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
    }

    qsort(bio, N, sizeof(BioRecord), cmp_bio);
    qsort(movie, M, sizeof(MovieRecord), cmp_movie);

    int i = 0, j = 0;
    while (i < N && j < M) {
        int cmp = strcmp(bio[i].name, movie[j].actor_name);
        if (cmp < 0) {
            i++;
        } else if (cmp > 0) {
            j++;
        } else {
            int bio_start = i;
            while (i < N && strcmp(bio[i].name, movie[j].actor_name) == 0) {
                i++;
            }
            int movie_start = j;
            while (j < M && strcmp(movie[j].actor_name, bio[bio_start].name) == 0) {
                j++;
            }
            for (int bi = bio_start; bi < i; bi++) {
                for (int mj = movie_start; mj < j; mj++) {
                    printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                           bio[bi].name, bio[bi].birth_year, bio[bi].country,
                           movie[mj].actor_name, movie[mj].movie_name);
                }
            }
        }
    }

    free(bio);
    free(movie);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
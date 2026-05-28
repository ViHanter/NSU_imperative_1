#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 31
#define MAX_COUNTRY 11
#define MAX_MOVIE 21
#define HASH_SIZE 100003

typedef struct BioNode {
    char name[MAX_NAME];
    int birth_year;
    char country[MAX_COUNTRY];
    struct BioNode *next;
} BioNode;

BioNode *hash_table[HASH_SIZE];

unsigned int hash(const char *str) {
    unsigned int h = 0;
    while (*str) {
        h = h * 31 + (unsigned char)(*str);
        str++;
    }
    return h % HASH_SIZE;
}

void add_bio(const char *name, int year, const char *country) {
    unsigned int index = hash(name);
    BioNode *node = (BioNode *)malloc(sizeof(BioNode));
    strcpy(node->name, name);
    node->birth_year = year;
    strcpy(node->country, country);
    node->next = hash_table[index];
    hash_table[index] = node;
}

BioNode *get_bio_list(const char *name) {
    unsigned int index = hash(name);
    BioNode *node = hash_table[index];
    return node;
}


void free_hash_table() {
    for (int i = 0; i < HASH_SIZE; i++) {
        BioNode *node = hash_table[i];
        while (node != NULL) {
            BioNode *temp = node;
            node = node->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
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

    for (int i = 0; i < N; i++) {
        char name[MAX_NAME];
        int year;
        char country[MAX_COUNTRY];
        
        read_quoted_string(name, stdin);
        scanf("%d", &year);
        read_quoted_string(country, stdin);
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);

        add_bio(name, year, country);
    }

    scanf("%d\n", &M);

    for (int i = 0; i < M; i++) {
        char actor_name[MAX_NAME];
        char movie_name[MAX_MOVIE];
        
        read_quoted_string(actor_name, stdin);
        read_quoted_string(movie_name, stdin);
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);

        BioNode *bio = get_bio_list(actor_name);
        while (bio != NULL) {
            if (strcmp(bio->name, actor_name) == 0) {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                       bio->name, bio->birth_year, bio->country,
                       actor_name, movie_name);
            }
            bio = bio->next;
        }
    }

    free_hash_table();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
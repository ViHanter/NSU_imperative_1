#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 31
#define MAX_COUNTRY 11
#define MAX_MOVIE 21

typedef struct BioRecord {
    int birth_year;
    char country[MAX_COUNTRY];
    struct BioRecord *next;
} BioRecord;

typedef struct BSTNode {
    char name[MAX_NAME];
    BioRecord *bio_list;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BioRecord* create_bio(int year, const char *country) {
    BioRecord *bio = (BioRecord*)malloc(sizeof(BioRecord));
    bio->birth_year = year;
    strcpy(bio->country, country);
    bio->next = NULL;
    return bio;
}

void add_bio_to_list(BioRecord **list, BioRecord *bio) {
    bio->next = *list;
    *list = bio;
}

BSTNode* bst_insert(BSTNode *root, const char *name, int year, const char *country) {
    if (root == NULL) {
        BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
        strcpy(node->name, name);
        node->bio_list = NULL;
        add_bio_to_list(&node->bio_list, create_bio(year, country));
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = bst_insert(root->left, name, year, country);
    } else if (cmp > 0) {
        root->right = bst_insert(root->right, name, year, country);
    } else {
        // имя совпало — добавляем биографию в список
        add_bio_to_list(&root->bio_list, create_bio(year, country));
    }
    return root;
}

BSTNode* bst_search(BSTNode *root, const char *name) {
    while (root != NULL) {
        int cmp = strcmp(name, root->name);
        if (cmp < 0) {
            root = root->left;
        } else if (cmp > 0) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

void free_tree(BSTNode *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    BioRecord *bio = root->bio_list;
    while (bio != NULL) {
        BioRecord *temp = bio;
        bio = bio->next;
        free(temp);
    }
    free(root);
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

    BSTNode *root = NULL;
    for (int i = 0; i < N; i++) {
        char name[MAX_NAME];
        int year;
        char country[MAX_COUNTRY];
        read_quoted_string(name, stdin);
        scanf("%d", &year);
        read_quoted_string(country, stdin);
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);

        root = bst_insert(root, name, year, country);
    }

    scanf("%d\n", &M);

    for (int i = 0; i < M; i++) {
        char actor_name[MAX_NAME];
        char movie_name[MAX_MOVIE];
        read_quoted_string(actor_name, stdin);
        read_quoted_string(movie_name, stdin);
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);

        BSTNode *node = bst_search(root, actor_name);
        if (node != NULL) {
            BioRecord *bio = node->bio_list;
            while (bio != NULL) {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                       node->name, bio->birth_year, bio->country,
                       actor_name, movie_name);
                bio = bio->next;
            }
        }
    }

    free_tree(root);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
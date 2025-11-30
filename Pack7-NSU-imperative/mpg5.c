#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char **arr;
} Tokens;

void tokensSplit(Tokens *t, const char *str, const char *delims) {
    int len = strlen(str);
    
    if (t->arr == NULL) {
        t->num = 0;
        int in_word = 0;
        for (int i = 0; i < len; i++) {
            if (!strchr(delims, str[i])) {
                if (!in_word) {
                    t->num++;
                    in_word = 1;
                }
            } else {
                in_word = 0;
            }
        }
    } else {
        int word_index = 0;
        int word_start = -1;
        
        for (int i = 0; i <= len; i++) {
            if (i < len && !strchr(delims, str[i])) {
                if (word_start == -1) {
                    word_start = i;
                }
            } else {
                if (word_start != -1) {
                    int word_len = i - word_start;
                    t->arr[word_index] = malloc(word_len + 1);
                    strncpy(t->arr[word_index], str + word_start, word_len);
                    t->arr[word_index][word_len] = '\0';
                    word_index++;
                    word_start = -1;
                }
            }
        }
        t->num = word_index;
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    char str[1000001];
    fgets(str, 1000001, in);
    
    int len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
    
    Tokens tokens = {0, NULL};
    
    tokensSplit(&tokens, str, ".,;:");
    
    tokens.arr = malloc(tokens.num * sizeof(char*));
    
    tokensSplit(&tokens, str, ".,;:");
    
    fprintf(out, "%d\n", tokens.num);
    for (int i = 0; i < tokens.num; i++) {
        fprintf(out, "%s\n", tokens.arr[i]);
    }
    
    for (int i = 0; i < tokens.num; i++) {
        free(tokens.arr[i]);
    }
    free(tokens.arr);
    
    fclose(in);
    fclose(out);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "intersect.h"

unsigned long hash_fun(char *str)
{
// https://stackoverflow.com/questions/7666509/hash-function-for-string
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

char *fwords(const char *file_name)
{
    FILE *fp;
    size_t file_sz = 0;
    char c;
    char *words = NULL;
    int pos = 0;

    fp = fopen(file_name, "r");
    if (!fp)
        return NULL;
    fseek(fp, 0, SEEK_END);
    file_sz = ftell(fp);
#ifdef DEBUG
    printf("DEBUG: filename: %s\n", file_name);
    printf("DEBUG: file %s size is: %ld\n", file, file_sz);
#endif
    rewind(fp);
    words = (char *) malloc(sizeof(char) * (file_sz + 1));
    while (true) {
        c = fgetc(fp);
        if (c == EOF) { //TODO: possible optimization here-ala move most likely to top
            words[pos] = '\0';
            fclose(fp);
            return words;
        } else if (c == '\n') {
            words[pos] = ' ';
        } else {
            words[pos] = c;
        }
        pos++;
    }
}

char **tokstr(char *words)
{
    int buffsz = 1;

    for (size_t i = 0;  i < strlen(words); i++) {
        if (isspace(words[i]))
            buffsz++;
    }

    char **toks = (char **) malloc(sizeof(char**) * buffsz);
    char *tok;
    int pos = 0;

    tok = strtok(words, " ");
    while (tok != NULL) {
        toks[pos] = tok;
        pos++;

        if (pos >= buffsz) {
#ifdef DEBUG
            printf("DEBUG: bufsz is: %d\n", buffsz);
            printf("DEBUG: pos is: %d\n", pos);
#endif
            buffsz += buffsz;
#ifdef DEBUG
            printf("DEBUG: bufsz before realloc is: %d\n", buffsz);
#endif
            toks = (char **) realloc(toks, buffsz);
        }
        tok = strtok(NULL, " ");
    }
    toks[pos] = NULL;
    return toks;
}

void nadd(const Node **root, char *data)
{

}


int main(int argc, char **argv)
{
    Node **root = NULL;
    char *all_words = fwords(argv[1]);
    char **toks = tokstr(all_words);

    int tmp = 0, len = 0;
    while (toks[tmp]) {
        tmp++;
        len++;
    }


    /* Create BST from first file */
    for (int i = 0; i < len; i++) {
        printf("%s ", toks[i]);

    }

    free(all_words);
    free(toks);
    return 0;
}

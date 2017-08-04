#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "intersect.h"

Node *mknode(void)
{
    Node *n = malloc(sizeof(Node));
    n->string = NULL;
    n->count  = 0;
    n->file   = 1;
    n->left   = NULL;
    n->right  = NULL;
    return n;
}

unsigned long hash_fun(char *str)
{
// https://stackoverflow.com/questions/7666509/hash-function-for-string
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
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
    printf("DEBUG: file %s size is: %ld\n", file_name, file_sz);
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

    tok = strtok(words, " \t\f\n\r\v");
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
        tok = strtok(NULL, " \t");
    }
    toks[pos] = NULL;
    return toks;
}

void nadd(Node *root, char *data)
{
    if (root->count) { //Non-empty tree
        Node *n = root;
        Node *m = root;
        while (n) {
            m = n;
            if (strcasecmp(n->string, data) < 0)
                n = n->right;
            else if (strcasecmp(n->string, data) > 0)
                n = n->left;
            else          //Already in BST
                return;
        }
        Node *tmp = mknode();
        tmp->string = data;
        tmp->count  = 1;
        if (strcasecmp(m->string, data) < 0)
            m->right = tmp;
        else if (strcasecmp(m->string, data) > 0)
            m->left = tmp;
    } else {            //Empty tree
        root->string = data;
        root->count++;
    }
}

void printnode(const Node *n)
{
    printf("%s\t%d\n", n->string, n->count);
}

void preprint(Node *root)
{
    if (root) {
        printnode(root);
        preprint(root->left);
        preprint(root->right);
    }
}

void ordprint(Node *root)
{
    if (root) {
        ordprint(root->left);
        printnode(root);
        ordprint(root->right);
    }
    return;
}

void intprint(Node *root, char num)
{
    if (root) {
        intprint(root->left, num);
        if (root->count >= num)
            printnode(root);
        intprint(root->right, num);
    }
    return;
}

void rmtree(Node *root)
{
    if (root) {
        rmtree(root->left);
        rmtree(root->right);
        free(root);
    }
}

bool tsearch(Node *root, char *term, char currfile)
{
    Node *tmp = root;
    while (tmp) {
        if (strcasecmp(tmp->string, term) < 0)
            tmp = tmp->right;
        else if (strcasecmp(tmp->string, term) > 0)
            tmp = tmp->left;
        else {
            if (tmp->file != currfile) {
                tmp->file = currfile;
                tmp->count++;
            }
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    Node *root = NULL;
    //TODO: args handling here
    if (argc < 2) {
        printf("Usage: %s FILE1 FILE2 ...\n", argv[0]);
        return -1;
    }
    char *all_words = fwords(argv[1]);
    char **toks = tokstr(all_words);
    if (!all_words || !toks) {
        printf("%s: unknown error!\n", argv[0]);
        return -1;
    }

    int tmp = 0, len = 0;
    while (toks[tmp]) {
        tmp++;
        len++;
    }


    /* Create BST from first file */
    root = mknode();
    for (int i = 0; i < len; i++) {
        nadd(root, toks[i]);
    }

    /* Compare words in next file to words in BST */
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            printf("%s: unknown error!\n", argv[0]);
            return -1;
        }
        char word[256];
        while (fscanf(fp, " %255s", word) == 1) {
            tsearch(root, word, i);
        }
        fclose(fp);
    }

    intprint(root, argc - 1);

    /* Cleanup, cleanup, everybody do your share! */
    rmtree(root);
    free(all_words);
    free(toks);
    return 0;
}

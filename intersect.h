#ifndef INTERSECT_LIB_H
#define INTERSECT_LIB_H

/********DEFINITIONS********/
#define WORD_BUF 64

/*********STRUCTURES********/
typedef struct node {
    char *string;
    char count;
    struct node *left;
    struct node *right;
} Node;

/*********FUNCTIONS*********/
Node *mknode(void);
char *fwords(const char *file_name);
char **tokstr(char *words);
void nadd(Node *root, char *data);

#endif

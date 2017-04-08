#ifndef _eighth_h
#define _eighth_h

struct bst{
        int key;
        int height;
        struct bst *left;
        struct bst *right;
};

void readFile(FILE *file);
void insert(int num);
void search(int num);
void empty(struct bst *ptr);

#endif

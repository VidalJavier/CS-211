#ifndef _ninth_h
#define _ninth_h

struct bst{
        int key;
        struct bst *left;
        struct bst *right;
};

void readFile(FILE *file);
void insertNode(int num);
void searchNode(int num);
void deleteNode(int num);
void empty(struct bst *ptr);

#endif

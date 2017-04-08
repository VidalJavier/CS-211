#ifndef _third_h
#define _third_h

struct list{
        int num;
        struct list *next;
};

void fillHash();
void readFile(FILE *file);
void insert(int number);
void search(int number);

#endif

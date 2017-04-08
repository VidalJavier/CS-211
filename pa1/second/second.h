#ifndef _second_h
#define _second_h

struct list{
        int num;
        struct list *ptr;
};

void readFile(FILE *file);
void insertNode(int current_num);
void deleteNode(int current_num);
void printResult();
void dealloc();

#endif

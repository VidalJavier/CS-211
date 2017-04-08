#ifndef _first_h
#define _first_h
 
struct trie{
	char *word; // word represented in leaf nodes
	int num_occ; // number of occurences
	int num_sup; // number of super words
	bool isLeaf; // true when node is end of a word
	struct trie *children[26]; // 26 letters in alphabet
};

struct trie *createNode();
void readDict(FILE *dict_file);
void readData(FILE *data_file);
void insert(char *word);
void matchStr(char* str);
void printResult();
void traverse(struct trie *ptr, FILE *output);
void deallocate(struct trie *ptr);

#endif

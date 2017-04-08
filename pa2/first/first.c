#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "first.h"

struct trie *head = NULL; // head of trie structure
int line_count = 1; // keeps count of line number in map_file

int main(int argc, char **argv){
	FILE *map_file = fopen(argv[1], "r");
	if(argc != 2 || !map_file){
		printf("invalid input\n");
		exit(0);
	}
	FILE *dict_file;
	FILE *data_file;
	char dict[100];
	char data[100];
	while(fscanf(map_file, "%s %s", dict, data) != EOF){
		head = createNode();
		
		dict_file = fopen(dict, "r");
		readDict(dict_file);
		fclose(dict_file);

		data_file = fopen(data, "r");
		readData(data_file);
		fclose(data_file);

		printResult();
		deallocate(head);
		line_count++;
		head = NULL;
	}
	fclose(map_file);
	return 0;
}

/* Creates trie node and assigns data fields
 * * to default values and children to NULL.
 *  */
struct trie *createNode(){
	struct trie *node = (struct trie*) malloc(sizeof(struct trie));
	node -> word = NULL;
	node -> num_occ = 0;
	node -> num_sup = 0;
	node -> isLeaf = false;

	int i;
	
	/* Set all children of node to NULL
 	 * */
	for(i = 0; i < 26; i++){
		node ->children[i] = NULL;
	}
	return node;
}

/* Takes a file pointer to the dictionary file and
 * * reads the unique words from the file. Calls insert
 *  *function everytime it finds a word.
 *   */
void readDict(FILE *dict_file){
	char dict_word[500];
	char dict_letter;
	int index = 0;
	while(fscanf(dict_file, "%c", &dict_letter) != EOF){
		if(isalpha(dict_letter)){
			dict_word[index] = tolower(dict_letter);
			index++;
		}else if(index != 0){
			dict_word[index] = '\0';
			insert(dict_word);
			index = 0;
		}
	}
	return;
}

/* Takes a file pointer to the data file and reads
 * * every word from the file. Calls matchStr function
 *  * eveytime it finds a word.
 *   */
void readData(FILE *data_file){
	char data_word[500];
	char data_letter;
	int index = 0;
	while(fscanf(data_file, "%c", &data_letter) != EOF){
		if(isalpha(data_letter)){
			data_word[index] = tolower(data_letter);
			index++;
		}else if(index != 0){
			data_word[index] = '\0';
			matchStr(data_word);
			index = 0;
		}
	}
	return;
}

/* Takes a pointer to a word from dictionary file and 
 * * populates the appropriate children index of each node
 *  * if it is empty. Once at the end of the word, determines
 *   * the node to be a leaf node and adds specific word to node.
 *    */
void insert(char *word){
	struct trie *ptr = head;
	int index; // index of character in word
	int ascii; // ascii of character
	for(index = 0; index < strlen(word); index++){
		ascii = word[index];
		if(ptr -> children[ascii - 97] == NULL){
			ptr -> children[ascii - 97] = createNode();
		}
		
		/* True only if at end of word
                 * */
                if((index + 1) == strlen(word)){
                 	ptr -> children[ascii - 97] -> isLeaf = true;
                }
		ptr = ptr -> children[ascii - 97];
	}
	
	/* Populates the leaf node with appropriate word
 	 * */ 	
	ptr -> word = (char*) malloc((strlen(word) + 1) * sizeof(char));
	for(index = 0; index < strlen(word); index++){
		ptr -> word[index] = word[index];
	}
	ptr -> word[index] = '\0';	
	return;
}

/* Takes a pointer to a word from data file and searches
 * * the trie that holds the unique dictionary words. If it
 *  * finds an occurence, it increments num_occ and if it finds
 *   * the word is a superword of one in dictionary, it increments
 *    * num_sup.
 *     */
void matchStr(char *str){
	struct trie *ptr = head;
	int index;
	int ascii;
	for(index = 0; index < strlen(str); index++){
		ascii = str[index];
		if(ptr -> children[ascii - 97] == NULL){
			return;
		}else{
			ptr = ptr -> children[ascii - 97];
			if(ptr -> isLeaf && (index + 1) == strlen(str)){
				ptr -> num_occ = ptr -> num_occ + 1;
			}else if(ptr -> isLeaf){
				ptr -> num_sup = ptr -> num_sup + 1;
			}
		}
	}
	return;
}

/* Creates output file with appropriate line number
 * * and then calls the traverse function.
 *  */
void printResult(){
	FILE *output; // output text file
	char out[20];
	sprintf(out, "out%d.txt", line_count);
	
	output = fopen(out, "w");
	traverse(head, output);
	fclose(output);
	return;
}

/* Takes a pointer to an output file and traverses
 * * the trie until if finds leaf nodes. Once it does,
 *  * it write to the output file.
 *   */
void traverse(struct trie *ptr, FILE *output){
	int i = 0;
	if(ptr == NULL){
		return;
	}

	/* True if node is end of a word
 	 * */ 	
	if(ptr -> isLeaf){
                fprintf(output, "%s %d %d\n", ptr -> word, ptr -> num_occ, ptr -> num_sup);
        }
	
	for(i = 0; i < 26; i++){
		traverse(ptr -> children[i], output);
	}
}

/* Traverses through the array and frees up each individual
 * * node, along with its words if appropriate.
 *  */
void deallocate(struct trie *ptr){
	int i;
	if(ptr == NULL){
		return;
	}
	
	for(i = 0; i < 26; i++){
		deallocate(ptr -> children[i]);
	}
	
	if(ptr -> isLeaf){
		free(ptr -> word);
	}
	
	free(ptr);
}

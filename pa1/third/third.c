#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "third.h"

struct list *hash[10000];
int main(int argc, char **argv){
	if(access(argv[1], F_OK) == -1){
		printf("error\n");
		exit(0);
	}

	FILE *file = fopen(argv[1], "r");
	fseek(file, 0, SEEK_END);
	if(ftell(file) == 0){
		exit(0);
	}

	rewind(file);
	fillHash();
	readFile(file);
	fclose(file);
	return 0;
}
/* Fills hash table with defualt NULL.
 * */
void fillHash(){
	int i;
	for(i = 0; i < 10000; i++){
		hash[i] = NULL;
	}
	return;
}

/* Takes a pointer to file and reads each line, calling
 * * the appropriate function depending on the character.
 *  * If format of file is incorrect, prints error.
 *   */
void readFile(FILE *file){
	char ch;
	int number;
	while(fscanf(file, "%c %d\n", &ch, &number) != EOF){
                if(ch != 'i' && ch != 's'){
                        printf("error\n");
                        continue;
                }
		if(ch == 'i'){
			insert(number);
		}else{
			search(number);
		}
	}
	return;
}

/* Takes number from file and inserts it into correct index
 * * of hash table. If number already exists, prints out
 *  * duplicate.
 *   */
void insert(int number){
	int index = abs(number % 10000);
        int check = 0;
        struct list *temp;
        for(temp = hash[index]; temp != NULL; temp = temp -> next){
        	if(temp -> num == number){
                	printf("duplicate\n");
                        check = 1;
                        break;
                }
        }
        if(check == 0){
        	struct list *node;
                node = (struct list*) malloc(sizeof(struct list));
                node -> num = number;
                node -> next = hash[index];
                hash[index] = node;
                printf("inserted\n");
        }
	return;
}

/* Takes number from file and searches the hash table for it. If 
 * * found, it prints out present, if not then prints out absent.
 *  */
void search(int number){
	int index = abs(number % 10000);
        int check = 0;
        struct list *temp;
        for(temp = hash[index]; temp != NULL; temp = temp -> next){
        	if(temp -> num == number){
                	printf("present\n");
                	check = 1;
                        break;
                }
        }
        if(check == 0){
        	printf("absent\n");
        }
	return;
}

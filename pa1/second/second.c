#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "second.h"

struct list *head = NULL;
int main(int argc, char** argv){
	if(access(argv[1], F_OK) == -1){
		printf("error\n");
		exit(0);
	}
	FILE *file = fopen(argv[1], "r");
	fseek(file,0, SEEK_END);
	if(ftell(file) == 0){
		exit(0);
	}
	rewind(file);
	readFile(file);
	fclose(file);
	printResult();
	dealloc();		
	return 0;
}

/* Takes a pointer to a file and reads each line, calling the
 * * corresponding function to the letter or printing error
 *  * if the line is incorrectly formatted.
 *   */
void readFile(FILE *file){
	char ch;
	int current_num;
	while(fscanf(file, "%c %d\n", &ch, &current_num) != EOF){
		if(ch != 'i' && ch != 'd' && ch != ' '){
                                printf("error\n");
                                exit(0);
		}
		if(ch == 'i'){
			insertNode(current_num);
		}else{
			deleteNode(current_num);
		}	
	}
	return;
}

/* Takes a number from the file and inserts it into the linked
 * * in the correct position.
 *  */
void insertNode(int current_num){
	if(head == NULL){
        	struct list *node;
                node = (struct list*) malloc(sizeof(struct list));
                node -> num = current_num;
                node -> ptr = NULL;
                head = node;
        }else{
        	struct list *temp;
                struct list *prev = head;
                int check = 0;
                for(temp = head; temp != NULL; temp = temp -> ptr){
                	if(temp -> num == current_num){
                        	check++;
                                break;
                        }
                        if(temp -> num > current_num){
                        	struct list *node;
                                node = (struct list*) malloc(sizeof(struct list));
                                node -> num = current_num;
                                if(temp -> num == prev -> num){
                                	node -> ptr = prev;
                                        head = node;
                                        check++;
                                        break;
                                }else{
                                        node -> ptr = temp;
                                        prev -> ptr = node;
                                        check++;
                                        break;
                                }
                        }
                        if(prev -> num != temp -> num){
                        	prev = prev -> ptr;
                        }
                }
                if(check == 0 && current_num > prev -> num){
                	struct list *node;
                        node = (struct list*) malloc(sizeof(struct list));
                        node -> num = current_num;
                        node -> ptr = temp;
                        prev -> ptr = node;
                }
        }
	return;
}

/* Takes a number from the file and searches the linked list
 * * for the number. If it finds it then it deletes the node and
 *  * connects the previous node and the next node.
 */
void deleteNode(int current_num){
	if(head != NULL){
        	if(head -> num == current_num){
                	head = head -> ptr;
                }else{
                	struct list *temp;
                        struct list *prev = head;
                        for(temp = head; temp != NULL; temp = temp -> ptr){
                        	if(temp -> num > current_num){
                                	 break;
                                }else{
                                	if(temp -> num == current_num){
                                        	prev -> ptr = temp -> ptr;
                                                break;
                                        }
                                }
                                if(prev -> num != temp -> num){
                                	prev = prev -> ptr;
                                }
                        }
                }
        }
	return;
}

/* Prints out the linked list.
 * */
void printResult(){
	struct list *temp;
	for(temp = head; temp != NULL; temp = temp -> ptr){
        	printf("%d\t", temp -> num);
        }
	printf("\n");
	return;
}

/* Traverses the linked list deleting each node one at a 
 * * time.
 *  */
void dealloc(){
	struct list *temp;
	while (head != NULL){
                temp = head;
                head = temp -> ptr;
                free(temp);
        }
	return;
}

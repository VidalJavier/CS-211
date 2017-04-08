#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "eighth.h"

struct bst *root = NULL;
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
	readFile(file);
	fclose(file);
	empty(root);
	return 0;
}

/* Takes a pointer to a file and calls the appropriate function
 * * depending on the character. If structure of file is incorrect
 *  * then prints out error and exits program.
 *   */
void readFile(FILE *file){
	char ch;
	int num;
	while(fscanf(file, "%c %d\n", &ch, &num) != EOF){
                if(ch != 'i' && ch != 's'){
                        printf("error\n");
                        exit(0);
                }
                if(ch == 'i'){
			insert(num);
		}else{
			search(num);
		}
	}
       return;
}

/* Takea a number from the file and inserts it into the BST at
 * * the coorect position.
 *  */
void insert(int num){
	if(root == NULL){
        	struct bst *temp;
                temp = (struct bst*) malloc(sizeof(struct bst));
                temp -> key = num;
                temp -> height = 1;
                temp -> left = NULL;
                temp -> right = NULL;
                root = temp;
                printf("inserted ");
                printf("%d\n", temp -> height);
        }else{
        	int check = 0;
                struct bst *ptr = root;
                while(ptr != NULL){
                	if(ptr -> key == num){
                        	printf("duplicate\n");
                                check = 1;
                                break;
                        }
                        if(ptr -> key > num){
                        	ptr = ptr -> left;
                        }else{
                        	ptr = ptr -> right;
                        }
                }
		if(check == 0){
                	int check2 = 0;
                        struct bst *temp;
                        struct bst*ptr = root;
                        temp = (struct bst*) malloc(sizeof(struct bst));
                        temp -> key = num;
                        temp -> left = NULL;
                        temp -> right = NULL;
                        while(check2 == 0){
                        	if(ptr -> key > num){
                                	if(ptr -> left == NULL){
                                        	temp -> height = ptr -> height + 1;
                                                ptr -> left = temp;
                                                printf("inserted ");
                                                printf("%d\n", temp -> height);
                                                check2 = 1;
                                	}else{
                                		ptr = ptr -> left;
                                        }
                                }else{
                                	if(ptr -> right == NULL){
                                        	temp -> height = ptr -> height + 1;
                                                ptr -> right = temp;
                                                printf("inserted ");
                                                printf("%d\n", temp -> height);
                                                check2 = 1;
                                        }else{
                                        	ptr = ptr -> right;
                                        }
                                }
                        }
                }
	}
	return;
}

/* Takes a number from the file and searches the BST for the 
 * * corresponding number. If present them prints out present, 
 *  * if not prints out absent.
 *   */
void search(int num){
	int check = 0;
        struct bst *ptr = root;
        while(ptr != NULL){
        	if(ptr -> key == num){
        		printf("present ");
                	printf("%d\n", ptr -> height);
                	check = 1;
                 	break;
        	}
        	if(ptr -> key > num){
        		ptr = ptr -> left;
        	}else{
        		ptr = ptr -> right;
        	}
        }
        
	if(check == 0){
        	printf("absent\n");
        }
	return;
}

/* Takes pointer to root and deletes each node of the BST
 * * in a recursive call.
 *  */
void empty(struct bst *ptr){
	if(ptr == NULL){
		return;
	}
	empty(ptr -> left);
	empty(ptr -> right);
	free(ptr);
}


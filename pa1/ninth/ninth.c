#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ninth.h"

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
	return 0;
}

/* Takes a pointer to a file and calls the appropriate
 * * function depending on the character of the file. If
 *  * the structure of the file is incorrect, then it 
 *   * prints out error and terminates the program.
 *    */
void readFile(FILE *file){
	char ch;
        int num;
        while(fscanf(file, "%c %d\n", &ch, &num) != EOF){
                if(ch != 'i' && ch != 's' && ch != 'd'){
                        printf("error\n");
                        exit(0);
                }
	
                if(ch == 'i'){
			insertNode(num);
		}else if(ch == 's'){
			searchNode(num);
		}else if(ch == 'd'){
			deleteNode(num);
		}
	}
	return;
}

/* Takes a number from the file and inserts the number in
 * * the correct position in the BST.
 *  */
void insertNode(int num){
	int height = 1;
        if(root == NULL){
        	struct bst *temp = (struct bst*) malloc(sizeof(struct bst));
                temp -> key = num;
                temp -> left = NULL;
                temp -> right = NULL;
                root = temp;
                printf("inserted ");
                printf("%d\n", height);
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
                        struct bst *temp = (struct bst*) malloc(sizeof(struct bst));;
                        struct bst *ptr = root;
                        temp -> key = num;
                        temp -> left = NULL;
                        temp -> right = NULL;
                        while(check2 == 0){
                        	if(ptr -> key > num){
                                	height++;
                                	if(ptr -> left == NULL){
                                        	ptr -> left = temp;
                                                printf("inserted ");
                                                printf("%d\n", height);
                                                check2 = 1;
                                        }else{
                                        	ptr = ptr -> left;
                                        }
                                }else{
                                	height++;
                                        if(ptr -> right == NULL){
                                        	ptr -> right = temp;
                                                printf("inserted ");
                                                printf("%d\n", height);
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

/* Takes a number from the file and searches the BST
 * * for the number. If found prints out present and 
 *  * not found prints out absent.
 *   */
void searchNode(int num){
	int height = 1;
	int check = 0;
        struct bst *ptr = root;
        while(ptr != NULL){
        	if(ptr -> key == num){
                	printf("present ");
                        printf("%d\n", height);
                        check = 1;
                        break;
                }
                if(ptr -> key > num){
                	height++;
                        ptr = ptr -> left;
                }else{
                	height++;
                        ptr = ptr -> right;
                }
        }

        if(check == 0){
        	printf("absent\n");
        }  
	return;
}

/* Takes number from file and searches BST for it. If
 * * it finds the number, deletes the node and adjusts 
 *  * the BST accordingly. 
 */
void deleteNode(int num){
	if(root == NULL){
		return;
	} 
	int check = 0;
        struct bst *ptr = root;
        struct bst *parent = root;
        
	/* Case 1 where number to be deleted is root */
	if(ptr -> key == num){
        	if(ptr -> left == NULL && ptr -> right == NULL){
                	root = NULL;
                        check = 1;
                }else if(ptr -> left == NULL){
                	root = ptr -> right;
                        check = 1;
                }else if(ptr -> right == NULL){
                	root = ptr -> left;
                        check = 1;
                }else if(ptr -> left != NULL && ptr -> right != NULL){
                	ptr = ptr -> right;
                        int temp2;
                        check = 1;
                        if(ptr -> left == NULL){
                        	temp2 = ptr -> key;
                                parent -> key = temp2;
                                parent -> right = ptr -> right;
                        }else{
                        	while(ptr -> left != NULL){
                                	ptr = ptr -> left;
                                        if(ptr -> left -> left == NULL){
                                        	if(ptr -> left -> right == NULL){
                                                	temp2 = ptr -> left -> key;
                                                        ptr -> left = NULL;
                                                }else{
                                                	temp2 = ptr -> left -> key;
                                                        ptr -> left = ptr -> left -> right;
                                                        break;
                                                }
                                        }
                                }
                                parent -> key = temp2;
                        }
                }
        }else{
		/* Traverse BST until it finds the number or a NULL node */
        	while(ptr != NULL && ptr -> key != num){
                	parent = ptr;
                        if(ptr -> key > num){
                        	ptr = ptr -> left;
                        }else{
                        	ptr = ptr -> right;
                        }
                }
                if(ptr != NULL){
			/* Case 2 where node to be deleted is on the right */
                	if(parent -> right == ptr){
                        	if(ptr -> left == NULL && ptr -> right == NULL){
                                	parent -> right = NULL;
                                        check = 1;
                                }else if(ptr -> left == NULL){
                                	parent -> right = ptr -> right;
                                        check = 1;
                                }else if(ptr -> right == NULL){
                                	parent -> right = ptr -> left;
                                        check = 1;
                                }else if(ptr -> left != NULL && ptr -> right != NULL){
                                	ptr = ptr -> right;
                                        int temp2;
                                        check = 1;
                                        if(ptr -> left == NULL){
                                        	temp2 = ptr -> key;
                                                parent -> right -> key = temp2;
                                                parent -> right -> right = ptr -> right;
                                        }else{
                                        	while(ptr -> left != NULL){
                                                	if(ptr -> left -> left == NULL){
                                                        	if(ptr -> left -> right == NULL){
                                                                	temp2 = ptr -> left -> key;
                                                                        ptr -> left = NULL;
                                                                        break;
                                                                }else{
                                                                	temp2 = ptr -> left -> key;
                                                                        ptr -> left = ptr -> right;
                                                                        break;
                                                                }
                                                        }
                                                        ptr = ptr -> left;
                                                }
                                                parent -> right -> key = temp2;
                                        }
                                }
			}else{
				/* Case 3 where node to be deleted is on the left */
				if(ptr -> left == NULL && ptr -> right == NULL){
                                	parent -> left = NULL;
                                        check = 1;
                                }else if(ptr -> left == NULL){
                                	parent -> left = ptr -> right;
                                        check = 1;
                                }else if(ptr -> right == NULL){
                                	parent -> left = ptr -> left;
                                        check = 1;
                                }else if(ptr -> left != NULL && ptr -> right != NULL){
                                	ptr = ptr -> right;
                                        int temp2;
                                        check = 1;
                                        if(ptr -> left == NULL){
                                        	temp2 = ptr -> key;
                                                parent -> left -> key = temp2;
                                                parent -> left -> right = ptr -> right;
                                        }else{
                                        	while(ptr -> left != NULL){
                                                	if(ptr -> left -> left == NULL){
                                                        	if(ptr -> left -> right == NULL){
                                                                	temp2 = ptr -> left -> key;
                                                                        ptr -> left = NULL;
                                                                        break;
                                                                }else{
                                                                	temp2 = ptr -> left -> key;
                                                                        ptr -> left = ptr -> right;
                                                                        break;
                                                                }
                                                        }
                                                        ptr = ptr -> left;
                                                }
                                                parent -> left -> key = temp2;
                                        }
                                }
			}
		}
	}
	if(check == 0){
        	printf("fail\n");
        }else{
        	printf("success\n");
        }
	return;
}

/* Takes a pointer to the BST and delets nodes using a 
 * * recursive call.
 *  */
void empty(struct bst *ptr){
	if(ptr == NULL){
		return;
	}
	empty(ptr -> left);
	empty(ptr -> right);
	free(ptr);
}

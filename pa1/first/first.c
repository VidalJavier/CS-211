#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
	printf("CHANGING\n");
	if(argc < 2){
		printf("error\n");
		exit(0);
	}
	int i;
	int val;
	for(i = 1; i < argc; i++){
		val = atoi(argv[i]);
		int c;
		for(c = 2; c < val; c++){
			if(val % c == 0){
				printf("no\n");
				return 0;
			}
		}
		printf("yes\n");
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("error\n");
		exit(0);
	}

	int i;
	char arr[argc-1];
	for(i = 1; i < argc; i++){
		arr[i-1] = argv[i][0];
	}
	
	arr[argc-1] = '\0';
	printf("%s\n", arr);
	return 0;
}

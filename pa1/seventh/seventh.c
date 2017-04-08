#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc < 2){
		printf("error\n");
		exit(0);
	}

	int i, size;
	char word[argc-1];
	for(i = 1; i < argc; i++){
		size = strlen(argv[i]);
		word[i-1] = argv[i][size-1];
	}

	word[argc-1] = '\0';
	printf("%s\n", word);
	return 0;
}

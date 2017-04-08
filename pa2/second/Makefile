all: second

second: second.c
	gcc -g -Wall -Werror -fsanitize=address second.c -o second

.PHONY = clean
clean:
	rm -f second                     

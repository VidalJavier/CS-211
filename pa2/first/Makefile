all: first

first: first.c
	gcc -g -Wall -Werror -fsanitize=address first.c -o first

.PHONY = clean
clean:
	rm -f first

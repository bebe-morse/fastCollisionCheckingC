all : main.c cell.c hash.c
	gcc main.c cell.c hash.c -g -lm -o main

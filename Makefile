# template for makefiles


output: main.o #name of the executable - change every time a group of files change
	gcc main.o -o output

main.o: main.c main.h
	gcc -c main.c

# target: dependencies
# 	action

clean: # remove all the output files
	rm -r *.o  output
	
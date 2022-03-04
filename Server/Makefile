# target: dependencies
# 	action

httpServer: main.o #name of the executable - change every time a group of files change
	gcc Server.o -o httpServer

main.o: Server.c
	gcc -c Server.c

clean: # remove all the output files
	rm -r *.o  httpServer
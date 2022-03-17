# target: dependencies
# 	action

# httpServer: main.o #name of the executable - change every time a group of files change
# 	gcc Server.o -o httpServer

ImageServer: ImageServer.o base64.o cJSON.o httpd.o tools.o
	gcc ImageServer.o base64.o cJSON.o httpd.o tools.o -lm -o ImageServer

ImageServer.o: ImageServer.c
	gcc -c ImageServer.c -o ImageServer.o 

base64.o: source/base64.c ./header/base64.h
	gcc -c source/base64.c -o base64.o

cJSON.o: ./source/cJSON.c ./header/cJSON.h
	gcc -c ./source/cJSON.c -o cJSON.o

httpd.o: ./source/httpd.c ./header/httpd.h
	gcc -c ./source/httpd.c -o httpd.o

tools.o: ./source/tools.c ./header/tools.h
	gcc -c ./source/tools.c -I. -o tools.o
	
clean: # remove all the output files
	rm -r *.o & rm -r ImageServer

# gcc main.c ./source/base64.c ./source/cJSON.c ./source/httpd.c ./source/tools.c -o server

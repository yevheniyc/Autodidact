# Makefile - Yevheniy Chuba - 02/09/2016

# Indicate compiler to use
CC=gcc
# -I flag tells gcc to look in the current directory (.) for the include files *.h
CFLAGS=-I.

client: echoclient2.c
	$(CC) -o client echoclient2.c

server: echoserver2.c
	$(CC) -o server echoserver2.c

clean:
	rm -f client server
	rm *.out *.o


############ Makefile Example + Shortcuts ###############################
# obj= getname.o getaccno.o main.o 						-> global of object files
# getinfo: $(obj) header.h 								-> dependencies including *.h files
# 	cc -o getinfo $(obj) header.h	
# 	@echo "make complete." 								-> @echo for debuggin makefiles
# main.o:                                               -> no need for >> gcc -c main.c
# getaccno.o:
# getname.o:
# clean:
# 	rm getinfo $(obj)
# 	@echo "getinfo, $(obj) files are removed."          -> @echo again!
#########################################################################
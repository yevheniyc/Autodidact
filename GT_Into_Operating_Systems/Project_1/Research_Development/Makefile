# Makefile - Yevheniy Chuba - 02/06/2016
# Example of using make

# For good examples:
	# - http://www.thegeekstuff.com/2010/08/make-utility/ 			-> general example
	# - http://www.gnu.org/software/make/manual/make.html				-> everything is here
	# - http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/  -> a few nice tricks for managing larger projects

# This program is called make. It reads in a file, called a Makefile, 
# that tells it how different files depend on each other, and works out 
# which files need to be re-compiled and which ones do not. 

# For example, a rule could say something like “if fromboz.o is older than fromboz.c, 
# that means someone must have changed fromboz.c, so it needs to be re-compiled.” 

# The makefile also has rules telling make how to re-compile the source file, 
# making it a much more powerful tool.


########## Makefile Example + Explanation ################################
#  foo: foo.c - dependencies
#      gcc -o foo foo.c

# It consists of two lines, a dependency line and a creation line.

# The dependency line here consists of the name of the program (known as the target), 
# followed by a colon, then whitespace, then the name of the source file. 
# When make reads this line, it looks to see if foo exists; if it exists, 
# it compares the time foo was last modified to the time foo.c was last modified. If foo does not exist, 
# or is older than foo.c, it then looks at the creation line to find out what to do. In other words, 
# this is the rule for working out when foo.c needs to be re-compiled.

# The creation line starts with a tab (press the tab key) and then the command you would type to create foo 
# if you were doing it at a command prompt. If foo is out of date, or does not exist, make then executes this 
# command to create it. In other words, this is the rule which tells make how to re-compile foo.c.

# So, when you type make, it will make sure that foo is up to date with respect to your latest changes to foo.c. 
# This principle can be extended to Makefiles with hundreds of targets—in fact, on FreeBSD, 
# it is possible to compile the entire operating system just by typing make world in the appropriate directory!

# $(variable) -> to use globally defined variables in the rule section
# -command -> to ignore the return value of the command
#########################################################################

# Indicate compiler to use
CC=gcc
# -I flag tells gcc to look in the current directory (.) for the include files *.h
CFLAGS=-I.

client: 6a_client.c
	$(CC) -o client 6a_client.c

server: 6b_server.c
	$(CC) -o server 6b_server.c

insertion: 7c_insertion_main.c 7b_insertion_sort.c
	$(CC) -o insertion 7c_insertion_main.c 7b_insertion_sort.c $(CFLAGS)

clean:
	-rm -f client server
	-rm *.out *.o
	-rm -f insertion


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
main: main.c tree.c tree.h
	gcc -Wall main.c tree.c tree.h -o main	

clean:
	rm -f *.o main
ALL : test.exe
test.exe : main.o ../LIB/libiml.a 
	gcc -Wall -o test.exe -L ../LIB main.o -liml 
main.o : main.c ../LIBHEADERS/analyseur.h ../LIBHEADERS/mnemoniques.h 
	gcc  -Wall -c -I ../LIBHEADERS main.c
clean :
	rm -f *.o test.exe

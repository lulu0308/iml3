ALL : assembleur.exe
assembleur.exe : assembleur.o HEADERS/table_des_symboles.o
	gcc -Wall -o assembleur.exe -L ../LIB   assembleur.o HEADERS/table_des_symboles.o -liml 
assembleur.o : assembleur.c 
	gcc  -Wall -c -I ./HEADERS assembleur.c 
HEADERS/table_des_symboles.o: HEADERS/table_des_symboles.c
	gcc  -Wall -c -I ./HEADERS HEADERS/table_des_symboles.c
clean :
	rm -f *.o *.exe
flush:
	
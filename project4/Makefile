main: crawler.o indexPage.o  josh.o main.c
 gcc -g crawler.o indexPage.o  josh.o main.c -o main -lm
crawler.o: crawler.c crawler.h
 gcc -g -c crawler.c -o crawler.o
indexPage.o: indexPage.c indexPage.h
 gcc -g -c indexPage.c -o indexPage.o
josh.o:  josh.c  josh.h
 gcc -g -c  josh.c -o  josh.o

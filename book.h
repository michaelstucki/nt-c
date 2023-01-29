#ifndef BOOK_H
#define BOOK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct book {
    char* title;
    int numberOfWords;
    size_t id;
    struct book* prev;
    struct book* next;
} book;

typedef struct set {
    int numberOfWords;    
    book* books;
    struct set* next;
} set;

typedef struct solution {
    unsigned int fit;
    struct set* sets;
} solution;

static const size_t BUFFER_SIZE = 10;

book* createBook(FILE*, const char*, const int, const size_t);
void addBook(FILE*, book**, book*);
void deleteBook(FILE*, book**, size_t);
book* getBook(FILE*, book*, size_t);
book* createLibary(FILE*, const char*);
void printLibrary(FILE*, book*);
void deleteLibrary(FILE*, book*);
size_t getLibrarySize(book*);
int getNumberOfWords(FILE*, book*);
solution* getSolution(FILE*, book*, size_t);
solution* createSolution(void);
set* createSet(void);
void addSet(set**, set*);
void printSol(FILE*, solution*);
void printSet(FILE*, set*);
void getFit(solution*, int);
void deleteSolution(FILE*, solution*);
#endif

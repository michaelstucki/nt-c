#ifndef NT_H
#define NT_H
#include <stddef.h>
#include "book.h"
static const char* BOOKS = "nt_books.txt";
static const char* LOG = "nt_log.txt";
static const int ITERATIONS = 20000000;
static const size_t CHAR_BUFFER = 80;
size_t isInteger(const char*);
size_t getNumberOfVerses(book*);
void printWelcome(void);
#endif

#include <string.h>
#include "book.h"
#include "current_time.h"
#include "random.h"
#include <math.h>
//#define PRINT_LOG

book* createBook(FILE* fp_log, const char* title, const int numberOfWords, const size_t count)
{
    book* node = malloc(sizeof(book));
    node->title = malloc(sizeof(char)*strlen(title));
    strcpy(node->title, title);
    node->numberOfWords = numberOfWords;
    node->id = count;
    node->prev = NULL;
    node->next = NULL;
#ifdef PRINT_LOG
    logCurrentTimeStamp(fp_log);
    fprintf(fp_log, "%s: creating book: title: %s, numberOfWords: %d, id: %zu\n",
        __func__, node->title, node->numberOfWords, node->id);
#endif
    return node;
}

void addBook(FILE* fp_log, book** list, book* new)
{
#ifdef PRINT_LOG
    logCurrentTimeStamp(fp_log);
    fprintf(fp_log, "%s: adding book: title: %s, numberOfWords: %d, id: %zu\n", 
        __func__, new->title, new->numberOfWords, new->id);
#endif
        
    if (*list == NULL) {
        *list = new;
    } else {
        new->next = *list;
        (*list)->prev = new;
        *list = new;
    }
}

void deleteBook(FILE* fp_log, book** list, size_t id)
{
    logCurrentTimeStamp(fp_log);
    while(*list != NULL) {
        if ((*list)->id == id) {
#ifdef PRINT_LOG
            logCurrentTimeStamp(fp_log);
            fprintf(fp_log, "%s: deleting book: title: %s, numberOfWords: %d, id: %zu\n", 
                __func__, (*list)->title, (*list)->numberOfWords, (*list)->id);
#endif
            ((*list)->prev)->next = (*list)->next;
            (*list)->prev = (*list)->prev;
            break;
        }
        *list = (*list)->next;
    }
}

book* getBook(FILE* fp_log, book* list, size_t id)
{
    book* result = NULL;	
    while(list != NULL) {
        if (list->id == id) {
#ifdef PRINT_LOG
            logCurrentTimeStamp(fp_log);
            fprintf(fp_log, "%s: found book with ID: %zu\n", __func__, id);
#endif
            result = createBook(fp_log, list->title, list->numberOfWords, list->id);
            break;
        }
        list = list->next;
    }
    return result;
}

book* createLibary(FILE* fp_log, const char* input_file)
{
#ifdef PRINT_LOG
    logCurrentTimeStamp(fp_log);
    fprintf(fp_log, "%s: creating library\n", __func__);
#endif
    book* list = NULL;
    FILE* fp = fopen(input_file, "r");
    char str[BUFFER_SIZE];
    size_t count = 0;
    while((fgets(str, BUFFER_SIZE, fp) != NULL)) {
        const char* title = strtok(str, ",");
        const char* numberOfWords = strtok(NULL, ",");
        book* node = createBook(fp_log, title, atoi(numberOfWords), count);
        addBook(fp_log, &list, node);
        count++;
    }
    fclose(fp);
    return list;
}

void printLibrary(FILE* fp_log, book* list)
{
    while(list != NULL) {
//#ifdef PRINT_LOG
        logCurrentTimeStamp(fp_log);
        fprintf(fp_log, "%s: title: %s, numberOfWords: %d, id: %zu\n", 
            __func__, list->title, list->numberOfWords, list->id);
//#endif
        list = list->next;
    }
}

void deleteLibrary(FILE* fp_log, book* list)
{
    while(list != NULL)
    {
        book* node = list;
        list = node->next;
#ifdef PRINT_LOG
        logCurrentTimeStamp(fp_log);
        fprintf(fp_log, "%s: deleting node: title: %s, numberOfWords: %d, id: %zu\n", 
            __func__, node->title, node->numberOfWords, node->id);
#endif
        free(node->title);
        free(node);
    }
}

size_t getLibrarySize(book* list)
{
    size_t count = 0;
    while(list != NULL)
    {
        count++;
        list = list->next;
    }
    return count;
}

int getNumberOfWords(FILE* fp_log, book* list)
{
    int wordCount = 0;
    while(list != NULL) {
        wordCount += list->numberOfWords;
#ifdef PRINT_LOG
        logCurrentTimeStamp(fp_log);
        fprintf(fp_log, "%s: numberOfWords: %d, wordCount: %d\n", __func__, list->numberOfWords, wordCount);
#endif
        list = list->next;
    }
    return wordCount;
}

set* createSet()
{
    set* s = malloc(sizeof(set));
    s->numberOfWords = 0;
    s->books = NULL;
    s->next = NULL;
    return s;
}

solution* createSolution(void)
{
    solution* s = malloc(sizeof(solution));
    s->fit = 0;
    s->sets = NULL;
    return s;
}

void addSet(set** list, set* new)
{
    if (*list == NULL) {
        *list = new;
    } else {
        new->next = *list;
        *list = new;
    }
}

void printSet(FILE* fp_log, set* set)
{
//#ifdef PRINT_LOG
    logCurrentTimeStamp(fp_log);
    fprintf(fp_log, "numberOfWords: %d\n", set->numberOfWords);
//#endif
    printLibrary(fp_log, set->books);
}

void printSol(FILE* fp_log, solution* sol)
{
//#ifdef PRINT_LOG
    logCurrentTimeStamp(fp_log);
    fprintf(fp_log, "solution fit: %i\n", sol->fit);
//#endif
    set* set = sol->sets;
    while(set != NULL) {
        printSet(fp_log, set);
        set = set->next;
    }
}

void getFit(solution* sol, int target)
{
    set* set = sol->sets;
    while(set != NULL) {
        sol->fit += abs(set->numberOfWords - target);
        set = set->next;
    }
}

void deleteSolution(FILE* fp_log, solution* sol)
{
    set* list = sol->sets;
    while(list != NULL) {
        set* node = list;
        list = node->next;
        deleteLibrary(fp_log, node->books);
#ifdef PRINT_LOG
        logCurrentTimeStamp(fp_log);
        fprintf(fp_log, "%s: deleting set: numberOfWords: %d\n", __func__, node->numberOfWords);
#endif
        free(node);
    }

    free(sol);
}

solution* getSolution(FILE* fp_log, book* list, size_t numberOfSets)
{
    int target = getNumberOfWords(fp_log, list) / numberOfSets;
#ifdef PRINT_LOG
    logCurrentTimeStamp(fp_log);
    fprintf(fp_log, "%s: number of words target: %d\n", __func__, target);
#endif

    size_t len = getLibrarySize(list);
    size_t* array = malloc(sizeof(size_t)*len);
    for (size_t i = 0; i < len; ++i) {
        array[i] = i;
    }    
    randomize(array, len);

    solution* sol = createSolution();
    for (size_t i = 0; i < numberOfSets; ++i) {
        addSet(&(sol->sets), createSet());
    }

    set* set = sol->sets;
    size_t sum = 0;
    for (size_t i = 0; i < len; ++i) {
        book* book = getBook(fp_log, list, array[i]);
        addBook(fp_log, &(set->books), book);
        sum += book->numberOfWords;
        if (sum >= target) {
            set->numberOfWords = sum;
            set = set->next;
            sum = 0;
        }
    }
    if (set != NULL) set->numberOfWords = sum;

    free(array);

    getFit(sol, target);
    
    return sol;
}


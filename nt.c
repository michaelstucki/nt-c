#include "nt.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main()
{
    srand(time(NULL));

    printWelcome();

    FILE* fp_log = fopen(LOG, "w");
    
    book* library = createLibary(fp_log, BOOKS);

    const size_t numberOfVerses = getNumberOfVerses(library);

    printf("Computing result...please wait.\n");

    solution* best = getSolution(fp_log, library, numberOfVerses);
    for (size_t i = 0; i < ITERATIONS; ++i) {
        solution* tmp = getSolution(fp_log, library, numberOfVerses);
        if (tmp->fit < best->fit) {
            deleteSolution(fp_log, best);
            best = tmp;
        } else {
            deleteSolution(fp_log, tmp);
        }
    }
    printSol(fp_log, best);
    deleteSolution(fp_log, best);

    printf("Look in %s for results.\n", LOG);
    printf("Goodbye!\n");

    fclose(fp_log);
    
    return EXIT_SUCCESS;
}

size_t isInteger(const char* string)
{
    size_t result = 1;
    size_t length = strlen(string);
    for (size_t i = 0; i < length; ++i) {
        if (!isdigit(string[i])) {
            result = 0;
            break;
        }
    }
    return result;
}

size_t getNumberOfVerses(book* list)
{
    size_t numberOfBooks = getLibrarySize(list);
    size_t numberOfVerses = 0;
    do {
        printf("Enter number of verses per day to memorize [1 to %zu]: ", numberOfBooks);
        char numberOfVersesStr[CHAR_BUFFER];
        scanf("%s", numberOfVersesStr);
        if (!isInteger(numberOfVersesStr)) continue;
        numberOfVerses = atoi(numberOfVersesStr);
    } while(numberOfVerses < 1 || numberOfVerses > numberOfBooks); 
    return numberOfVerses;
}

void printWelcome(void)
{
    printf("Welcome!\n");
    printf("This program evenly divides the books of the New Testament into\n");
    printf("a number of sets equal to the number of verses per day to memorize\n");
    printf("based on word count, such that the number of words in each set is as\n");
    printf("equal among the sets as is, within the limitations of this program,\n");
    printf("computationally possible.\n");
}

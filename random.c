#include "random.h"
#include <stdio.h>
size_t getRandomNumber(size_t lower, size_t upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

void randomize(size_t* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        size_t tmp = array[i];
        size_t rand_num = getRandomNumber(i, size - 1);
        array[i] = array[rand_num];
        array[rand_num] = tmp;
    }
}

/*
void randomize(size_t* ordered, size_t size, size_t* sorted)
{
    if (size == 0) {
        free(ordered);
        return;
    }
    size_t rand = getRandomNumber(0, size - 1);
    sorted[size - 1] = ordered[rand];
    size_t* tmp = malloc(sizeof(size_t)*(size - 1));
    for (size_t i = 0, j = 0; i < size; ++i) {
        if (ordered[i] == ordered[rand]) continue;
        tmp[j] = ordered[i];
        j++;
    }
    randomize(tmp, --size, sorted);
    printf("%p, %zu\n", ordered, size);
    free(ordered);
}
*/
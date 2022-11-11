//
// Created by Rodolfo on 11/11/2022.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef DESAFIO_SUBSTRINGSEARCH_H
#define DESAFIO_SUBSTRINGSEARCH_H
char *substring(char *string, int position, int length)
{
    char *p;
    int c;

    p = malloc(length+1);

    if (p == NULL)
    {
        printf("Unable to allocate memory.\n");
        exit(1);
    }

    for (c = 0; c < length; c++)
    {
        *(p+c) = *(string+position-1);
        string++;
    }

    *(p+c) = '\0';

    return p;
}
#endif //DESAFIO_SUBSTRINGSEARCH_H

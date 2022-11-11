#include <stdio.h>
#include "searchPattern.h"
#include "substringSearch.h"

int main(int argc, char* argv[]) {
    char const* const fileName = "D:\\Desafio\\calana.txt";
    char searchQuery[255];
    char searchQueryFiltered[255];
    int position, firstMarkerPosition, lastMarkerPosition;

    printf("Informe o padrão a ser buscado: \n");
    gets(searchQuery);

    firstMarkerPosition = matchPattern(searchQuery, "*");
    if (firstMarkerPosition != -1){
        searchQueryFiltered = searchQuery[firstMarkerPosition+1,strlen(&searchQueryFiltered)-1];
        printf("Posição da primeira ocorrência do marcador: %d\n",firstMarkerPosition+1);
        printf("searchQueryFiltrada: %s\n",searchQueryFiltered);
    }



    FILE* file = fopen(fileName, "r");

    if(!file){
        printf("\n Unable to open: %s ", fileName);
        return -1;
    }

    char line[255];

    while (fgets(line, sizeof (line), file)){
        position = matchPattern(line, searchQuery);
        if (position != -1){
            printf("Primeira ocorrência: %d\n", position + 1);
        }
        else {
            printf("Not found.\n");
        }
    }

    fclose(file);
    return 0;
}



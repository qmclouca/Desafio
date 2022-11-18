#include <string.h>
#include <stdio.h>
#include "searchPattern.h"
#include "substringSearch.h"

int main(int argc, char* argv[]) {
    char path[255];
    char tag[255];
    int position, count=0;

    if (argc == 1){
        printf ("Digite uma linha com os seguintes elementos, e na ordem numerica indicada:\n");
        printf ("1 - TAG a ser buscada;\n");
        printf ("2 - Path completo dos arquivos, sem \\ no final;\n");
        printf ("3 - Nomes dos arquivos a serem processados;\n");
        printf ("4 - todos os itens (1, 2 e 3), devem estar separados por espacos;\n");
        printf ("Ex: Desafio.exe DVLD1TFP_CA c:\\arquivos calana.txt caldig.txt\n");
        return 0;
    }
    strcpy(tag, argv[1]);

    for (count=0; count+3<argc; count++){
        memset(path,0,sizeof (path));
        strcat(path,argv[2]);
        strcat(path,"\\");
        strcat(path,argv[count+3]);
        FILE* file = fopen(path, "r");
        if(!file){
            printf("\n Unable to open: %s ", path);
            return -1;
        }

        char line[255];
        printf("arquivo %s: \n", argv[count+3]);

        while (fgets(line, sizeof (line), file)){
            position = matchPattern(line, tag);
            if (position != -1){
                printf(line);
                position = -1;
            }
        }
        fclose(file);
    }
    return 0;
}



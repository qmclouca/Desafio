#include <string.h>
#include <stdio.h>

int matchPattern(char text[], char pattern[]){
    int c, d, e, text_length, pattern_length, position = -1;

    text_length    = strlen(text);
    pattern_length = strlen(pattern);

    if (pattern_length > text_length) {
        return -1;
    }

    for (c = 0; c <= text_length - pattern_length; c++) {
        position = e = c;

        for (d = 0; d < pattern_length; d++) {
            if (pattern[d] == text[e]) {
                e++;
            }
            else {
                break;
            }
        }
        if (d == pattern_length) {
            return position;
        }
    }
    return -1;
}



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
        memset(path,0,sizeof (path)); //zerar
        strcat(path,argv[2]);
        strcat(path,"\\");
        strcat(path,argv[count+3]); // file name with path
        FILE* file = fopen(path, "r");
        if(!file){
            printf("\n Unable to open: %s ", path);
            return -1;
        }

        char line[255];
        char *lineTag;
        printf("\n arquivo %s: \n", argv[count+3]);

        while (fgets(line, sizeof (line), file)){
            char lineToPrint[255];
            strcpy(lineToPrint, line);
            lineTag = strtok(line, ";");
            position = -1;
            int tagLength = 0;
            tagLength = strlen(tag);

            if (tag[0]==(char)42){  //É UM PADRÃO
                char endTag[tagLength-1];
                memcpy(endTag, &tag[1],tagLength);
                position = matchPattern(endTag, "*"); //TEM DOIS *
                if (position != -1){ //ENCONTRA O PADRÃO EM QUALQUER LUGAR DA TAGLINE
                    int tagLength = strlen(tag);
                    char subTag[tagLength-2];
                    char *buff = tag;
                    memcpy(subTag, &buff[1],tagLength-1);

                    if (matchPattern(lineTag, subTag) != -1){
                        printf("%s\n ", lineToPrint); //imprime padrões em qualquer lugar da tag
                        position = -1;
                    }
                } else {  //SÓ TEM * NA FRENTE
                    int endTagLength = strlen(endTag);
                    int lineTagLength = strlen(lineTag);
                    char *buff = lineTag;
                    char subTag[endTagLength];
                    memcpy(subTag, &buff[lineTagLength-endTagLength],lineTagLength);
                    int comp = strcmp(subTag,endTag);
                    if (comp == 0) {
                        printf("%s\n ", lineToPrint); //imprime padrões de fim de tag
                    }
                }
            } else {
                if (tag[tagLength-1] == (char)42){
                    char *subTag = strtok(tag, "*");
                    int subTagLength = strlen(subTag);

                    char *buff = lineTag;
                    char subLineTag[subTagLength];
                    memcpy(subLineTag, &buff[0],subTagLength);
                    int comp = strcmp(subTag,subLineTag);
                    if (comp == 0){
                        printf("%s\n", lineToPrint); //imprime padrões no início da tag
                    }
                } else { //Se nenhum * na tag
                    position = matchPattern(lineTag, tag);
                    if (position != -1){
                        printf("%s, ", lineToPrint); //imprime tags sem padrões
                    }
                }
            }
        }
        fclose(file);
    }
    return 0;
}



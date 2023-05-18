#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cabecalho.h"


int main(){
    int c, run = 0;

    while((c = getchar()) != EOF && run == 0){
        switch(c){
            case 'q' : run = 1;
                break;
            case 'c' : commandCarreira();
                break;
            case 'p' : commandParagem();
                break;
            case 'l' : commandLigacoes();
                break;
            case 'i' : commandInterseccoes();
                break;
            default: printf("Invalid comand: %c\n", c);
        }
    }
    return 0;
}


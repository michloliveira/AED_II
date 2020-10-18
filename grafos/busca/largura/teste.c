#include <stdio.h>
#include <stdlib.h>
#include "buscaLargura.h"

int main(int argc, char *argv[]){
    grafo g;
    char origem;
    lerArquivo(&g, "arquivo");
    printf("Insira a origem: ");
    scanf("%c", &origem);
    buscaLargura(&g, origem);

}

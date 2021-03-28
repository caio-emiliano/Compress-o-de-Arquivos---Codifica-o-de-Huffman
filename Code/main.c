/**
 * @file main.c
 * @brief Função Principal do Programa
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char *argv[]){

    //verifica se a forma de compilar está correta
    if(argc != 4 || (strcmp(argv[1], "-c") && strcmp(argv[1], "-d"))){
        printf("Para compilar digite: %s [-c,-d] arq. entrada arq. saida\n", argv[0]);
        exit(0);
    }
    
    //verifica se o arquivo de entrada pode ser aberto para leitura
    if(!(in = fopen(argv[2], "r"))){
    	printf("O arquivo de entrada não pode ser aberto\n");
    	return 0;
    }

    //verifica se o arquivo de saída já existe
    else if((out = fopen(argv[3], "r"))){
     	printf("O arquivo de saida já existe\n");
     	return 0;
    }

    //verifica se o arquivo de saída pode ser aberto para escrito
    else if(!(out = fopen(argv[3], "w"))){
     	printf("O arquivo de saida não pode ser aberto\n");
     	return 0;
    }
    
    //verifica se é para compactar ou descompactar o arquivo
    if(!strcmp(argv[1], "-c")) codifica(argv[2]);
    else decodifica();
        
    return 0;
}
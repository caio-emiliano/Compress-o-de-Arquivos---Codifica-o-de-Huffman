//huffman.c file
/**
 * @file huffman.c
 * @brief Implementação das funções do cabeçalho huffman.h
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"

/*******************************************************************
*   IMPLEMENTATION
*******************************************************************/


//Cria uma nova string com a letra adicionada no prefixo

char *concat(char *prefixo, char letra){
    char *resultado = (char *)malloc(strlen(prefixo) + 2);
    sprintf(resultado, "%s%c", prefixo, letra);
    return resultado;
}


//Ordena um vetor de ponteiros para struct. É utilizada para ordenar a pilha pela frequência das letras.

int cmpr(const void* a, const void* b) {
    struct arvore *ptr_esq_struct = *(arvore**)a;
    struct arvore *ptr_dir_struct = *(arvore**)b;

    //comparação feita pelo qsort para ordenação
    //a ordenação é feita em ordem decrescente de frequência
	if (ptr_esq_struct->x < ptr_dir_struct->x)
	    return 1;
	else if (ptr_esq_struct->x > ptr_dir_struct->x)
	    return -1;
	else
	    return 0;

}


//Adiciona o elemento na pilha. Obs: A pilha é um vetor de ponteiros

void push(arvore* node){
	if(topo != 257){
		topo = topo+1;
		vet[topo] = node;
	}
}


//Retira o ultimo elemento do vetor (pilha). Obs: A pilha é um vetor de ponteiros

arvore* pop(){
	if(topo > -1){
		arvore* k;
		k = vet[topo];
		topo -= 1;
		return k;
	}
}


//Inicializa a pilha. Topo recebe -1

void inicializa(){
	topo = -1;
}


//Escreve uma mensagem de erro e finaliza o programa. A mensagem de erro também é escrita no arquivo de saída

void erro(char erro[]){
	printf("%s\n", erro);
	fprintf(out, "%s\n", erro);
	exit(1);
}


//Lê o arquivo de entrada e conta a frequência de caracteres, (i.e.) o número de aparições de cada caracter. A frequência é armazenada no vetor freq[]

void conta_freq(){
	int letra;
	memset(freq, 0, sizeof freq); //zera a frequência do vetor freq.
	freq[fim_arquivo] = 1; //insere o pseudo-caracter (fim de arquivo) na lista de frequências
	
	//lê até o final do arquivo e conta a frequência de cada caracter
	while((letra = fgetc(in)) != EOF){
			freq[letra] += 1;
	}
	fclose(in);
}


//Cria um nó da árvore de huffman para cara caracter lido

arvore* cria_no(int ch, int f, arvore* e, arvore* d){
	arvore* no = malloc(sizeof(arvore));
	no->c = ch;
	no->x = f;
	no->esq = e;
	no->dir = d;
	return no;
}


//Cria a árvore de huffman

void cria_arvore(char verificacao){ 
	
	//verifica se a chamada da função foi para codificar
	//ou decodificar
	if(verificacao == 'c'){
		conta_freq();
	}

	int soma;

	inicializa(); //inicializa a pilha

	//cria no de cada caracter e empilha-os
	for(int i=0; i<257; i++){
		if(freq[i] > 0){
			push(cria_no(i, freq[i], NULL, NULL));
		}
	}

	qsort(vet, topo+1, sizeof(arvore*), cmpr); //ordena a pilha pela prioridade de freq.
	
	//repete até sobrar o raiz
	while(topo > 0){
		//remover os 2 nós com menor freq.
	 	arvore* e = vet[topo];
	 	pop();
	 	arvore* d = vet[topo];
	 	pop();

	 	//cria um nó novo (soma da freq. dos outros 2)
		soma = e->x + d->x;
		push(cria_no('*', soma, e, d)); //empilha o novo nó
		qsort(vet, topo+1, sizeof(arvore*), cmpr); //reordena a pilha pela prioridade de freq.
	}
	raiz = vet[topo]; //raiz recebe o ult. elemento da pilha
	
}


//Cria o código de cada caracter através da árvore. O código gerado é armazenado na variável tabela (variável global)

void cria_tabela(arvore* raiz, char *prefixo){
	
	if(raiz == NULL){
		return;
	}
	
	//caso base da recursão. é quando não existem mais filhos
	//a serem olhados na tabela
	if(!raiz->esq && !raiz->dir){
		tabela[raiz->c] = prefixo;
	}

	//chamadas recursivas percorrendo a árvore.
	else{
		if(raiz->esq) cria_tabela(raiz->esq, concat(prefixo, '0'));
		if(raiz->dir) cria_tabela(raiz->dir, concat(prefixo, '1'));
		free(prefixo);
	}
}


//Libera a memória utilizada na variável tabela.

void free_tabela(){

	//percorre a tabela e libera a memória alocada
	for (int i=0; i<256; i++){
		if(tabela[i] > 0){
			free(tabela[i]);
		}
	}

}


//Escreve o cabeçalho no arquivo de saida. No arquivo de saída é escrito o número de caracteres diferentes do arquivo de entrada, cada caracter e sua respectiva frequência. Obs: o cabeçalho é utilizado na reconstrução da árvore na decodificação

void escreve_cabecalho(){
	
	int n = 0; //numero de diferentes caract. lidos no arq.
	
	//conta o número de caracteres diferentes no arquivo
	for(int i=0; i<257; i++){
		if(freq[i] > 0){
			n++;
		}
	}
	
	fprintf(out, "%d\n", n);
	
	//escreve o caracter e sua frequência no arquivo de saida
	//essas informações representam o cabeçalho para a reconstrução
	//da árvore
	for(int i=0; i<257; i++){
		if(freq[i] > 0){
			fprintf(out, "%d %d\n", i, freq[i]);
		}
	}
}


//Escreve o bit em questão no arquivo de saída.

void escreve_bits(const char *cod){
    static int bits = 0, contabit = 0;
    
    while(*cod){
        
        //puxa os bits da direita
        bits = bits * 2 + *cod - '0';
        contabit++;

        //quando completa o char, escreve-o na saída como um único caracter
        if(contabit == 8){
            fputc(bits, out);
            bits = 0;
            contabit = 0;
        }
        cod++;
    }
}


//Codifica o arquivo de entrada.

void codifica(char arq[]){
	
	//prefixo é a variável de controle utilizada na recursão da função
	//cria_tabela
	char *prefixo = (char*) calloc(1,sizeof(char));
	int letra;

	cria_arvore('c');
	cria_tabela(raiz, prefixo);
	free(raiz);
	escreve_cabecalho();

	//abre o arquivo para leitura
	in = fopen(arq,"r");
	rewind(in);

	//enquanto a leitura é diferente do final do arquivo
	//escreve cada caracter lido de forma codificada no arquivo de saída
    while((letra = fgetc(in)) != EOF){
        escreve_bits(tabela[letra]);
    }
	
	//escreve o caracter fim_arquivo no arquivo de saída
	escreve_bits(tabela[fim_arquivo]);

	//escreve uma sequência de bits para dar flush no buffer 
	escreve_bits("00000000");

	free_tabela();
	fclose(in);
	fclose(out);
}


//Lê o cabeçalho do arquivo de entrada. As frequências lidas são armazenadas no vetor vet[]

void le_cabecalho(){
	
	int letra, frequencia, n;
	
	//verifica se o arquivo de entrada possui o num de caracteres
	//diferentes lidos na codificação
	if(fscanf(in, "%d", &n) != 1){
		erro("Entrada invalida");
	}

	//verifica se o arquivo de entrada possui 2 valores para cada linha
	//e se os valores estão no intervalo correto
	for(int i=0; i<n; i++){
		if(fscanf(in, "%d %d", &letra, &frequencia) != 2 ||letra < 0 ||letra > 256){
			erro("Entrada invalida");
		}

		//caso as condições acima forem válidas, adiciona a frequência
		//do caracter no vetor freq.
		freq[letra] = frequencia;
	}

	fgetc(in);
}


//Lê um único bit do arquivo de entrada

int le_bit(){

    static int bits = 0, contabit = 0;
    int proxbit;
    
    if(contabit == 0){
        bits = fgetc(in);
        contabit = (1 << 7);
    }
    
    proxbit = bits / contabit;
    bits %= contabit;
    contabit /= 2;

    return proxbit;
}


//Decodifica a letra gerada pela sequência de bits.

int decodifica_letra(arvore* raiz){
	
	//caso base da recursão. é quando não existem mais 
	//filhos para serem olhados
	if(!raiz->esq && !raiz->dir){
    	return raiz->c;
    }

    //chamadas recursivas percorrendo a árvore
    else{
       	if(le_bit()) decodifica_letra(raiz->dir); //1 para direita
       	else decodifica_letra(raiz->esq); //0 para esquerda
    }

    //verificação de erro caso a árvore esteja errada
    if(!raiz) erro("Arquivo de Entrada Inválido");

}


//Decodifica o arquivo de entrada.

void decodifica(){
	int ascii; //inteiro que recebe a letra decodificada
	memset(freq, 0, sizeof freq); //zera o vetor de freq.

	le_cabecalho();
	cria_arvore('d');
	
	//escreve a decodificação do arquivo até o 
	//pseudo-caracter fim_arquivo
    
    while((ascii = decodifica_letra(raiz)) != fim_arquivo){
        fputc(ascii, out);
    }
	
	//fecha os ponteiros dos arquivos de entrada e saida
	// e libera a memoria da árvore 
	fclose(in);
	fclose(out);
	free(raiz);
}


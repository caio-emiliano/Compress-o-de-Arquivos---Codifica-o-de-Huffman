/**
 * @file huffman.h
 * @brief Definição das funções, estruturas e variáveis globais
*/

#ifndef HUFFMAN_H_ 
#define HUFFMAN_H_

/*******************************************************************
*   STRUCT
*******************************************************************/
/**
 * @struct arvore
 * @brief É a arvore de huffman. Possui dois atributos do tipo int (x e c), que representam
 * respectivamente a frequência do caracter lido e o caracter em questão. Possui também dois ponteiros do tipo árvore.
 * Um ponteiro para a esquerda (esq) e um ponteiro para a direita (dir).
*/
typedef struct arvore{ //arvore de huffman
	int x;
	int c;
	struct arvore *esq;
	struct arvore *dir;
}arvore;

/*******************************************************************
*   DEFINES
*******************************************************************/

/**
 * @def fim_arquivo
 * @brief Utilizado como um pseudo-caracter para indicar o fim
 * do arquivo na escrita dos bits
*/
#define fim_arquivo 256

/*******************************************************************
*   GLOBAL VARIABLES
*******************************************************************/

/**
 * @var freq
 * @brief Vetor que armazena a frequência dos caracteres lidos
*/
int freq[257];

/**
 * @var tabela
 * @brief Matriz que armazena a codificação dos caracteres lidos
*/
static char *tabela[257];

/**
 * @var raiz
 * @brief Ponteiro do tipo árvore que indica a raiz da árvore de huffman
*/
arvore* raiz; //raiz da arvore de huffman

/**
 * @var vet
 * @brief Vetor que representa a pilha. A pilha é representada por um vetor de ponteiros do tipo árvore
*/
arvore* vet[257]; //vetor da pilha

/**
 * @var topo
 * @brief Variável de controle do topo da pilha
*/
int topo; // topo pilha

/**
 * @var in
 * @brief Ponteiro para o arquivo de entrada
*/
FILE* in;

/**
 * @var out
 * @brief Ponteiro para o arquivo de saída
*/
FILE* out;

/*******************************************************************
*   LOCAL PROTOTYPES
*******************************************************************/

/**
 * @fn concat(char *prefixo, char letra)
 * @brief Cria uma nova string com a letra adicionada no prefixo
 * @param prefixo - String a ser concatenada
 * @param letra - Letra a ser adicionada no prefixo da nova string
 * @return Nova string com a letra adicionada no prefixo
*/
char *concat(char *prefixo, char letra);

/**
 * @fn cmpr(const void* a, const void* b)
 * @brief Ordena um vetor de ponteiros para struct. É utilizada para ordenar a pilha pela frequência das letras.
 * @param a - Parâmetro de ordenação utilizado pelo qsort
 * @param b - Parâmetro de ordenação utilizado pelo qsort
 * @return Retorna a comparação entre as frêquencias das letras
*/
int cmpr(const void* a, const void* b);

/**
 * @fn push(arvore* node)
 * @brief Adiciona o elemento na pilha. Obs: A pilha é um vetor de ponteiros
 * @param node - Nó da árvore a ser empilhado.
*/
void push(arvore* node);

/**
 * @fn pop()
 * @brief Retira o ultimo elemento do vetor (pilha). Obs: A pilha é um vetor de ponteiros
 * @return Retorna o elemento removido.
*/
arvore* pop();

/**
 * @fn inicializa()
 * @brief Inicializa a pilha. Topo recebe -1
*/
void inicializa();

/**
 * @fn erro(char erro[])
 * @brief Escreve uma mensagem de erro e finaliza o programa. A mensagem de erro também é escrita no arquivo de saída
 * @param erro - Mensagem de erro a ser escrita.
*/
void erro(char erro[]);

/**
 * @fn conta_freq()
 * @brief Lê o arquivo de entrada e conta a frequência de caracteres, (i.e.) o número de aparições de cada caracter. A frequência é armazenada no vetor freq[]
*/
void conta_freq();

/**
 * @fn cria_no(int ch, int f, arvore* e, arvore* d)
 * @brief Cria um nó da árvore de huffman para cara caracter lido
 * @param ch - Caracter lido no arquivo de entrada
 * @param f - Frequência do caracter lido
 * @param e - Ponteiro para o elemento a esquerda
 * @param d - Ponteiro para o elemento a direita
*/
arvore* cria_no(int ch, int f, arvore* e, arvore* d);

/**
 * @fn cria_arvore(char verificacao)
 * @brief Cria a árvore de huffman
 * @param verificacao - Especifica se a chamada da criação da árvore é feita na codificação ou na decodificação
*/
void cria_arvore(char verificacao);

/**
 * @fn cria_tabela(arvore* raiz, char *prefixo)
 * @brief Cria o código de cada caracter através da árvore. O código gerado é armazenado na variável tabela (variável global)
 * @param raiz - Inicialmente raiz da árvore. Na recursão a variável é utilizada para caminhar na árvore
 * @param prefixo - Variável de controle utilizada na recursão. Recebe 0 na chamada a esquerda e 1 na chamada a direita.
*/
void cria_tabela(arvore* raiz, char *prefixo);

/**
 * @fn free_tabela()
 * @brief Libera a memória utilizada na variável tabela. 
*/
void free_tabela();

/**
 * @fn escreve_cabecalho()
 * @brief Escreve o cabeçalho no arquivo de saida. No arquivo de saída é escrito o número de caracteres diferentes do arquivo de entrada, cada caracter e sua respectiva frequência. Obs: o cabeçalho é utilizado na reconstrução da árvore na decodificação
*/
void escreve_cabecalho();

/**
 * @fn escreve_bits(const char *cod)
 * @brief Escreve o bit em questão no arquivo de saída.
 * @param cod - Código correspondente ao caracter em questão. Esse código foi gerado pela função cria_tabela percorrendo a árvore.
*/
void escreve_bits(const char *cod);

/**
 * @fn codifica(char arq[])
 * @brief Codifica o arquivo de entrada.
 * @param arq - Arquivo de entrada especificado pelo usuário 
*/
void codifica(char arq[]);

/**
 * @fn le_cabecalho()
 * @brief Lê o cabeçalho do arquivo de entrada. As frequências lidas são armazenadas no vetor vet[]
 * @remarks Se o arquivo de entrada não possuir N, o número caracteres diferentes lidos na codificação, 
 * não possuir 2 números nas N linhas seguintes (indicando caracter e frequência respectivamente), ou possuir um 
 * número no intervalo inválido da tabela ASCII, o programa escreve uma mensagem de erro e finaliza.
*/
void le_cabecalho();

/**
 * @fn le_bit()
 * @brief Lê um único bit do arquivo de entrada
 * @return Retorna o bit lido 
*/
int le_bit();

/**
 * @fn decodifica_letra(arvore* raiz)
 * @brief Decodifica a letra gerada pela sequência de bits.
 * @param raiz - Inicialmente raiz da árvore. Na recursão a variável é utilizada para caminhar na árvore
*/
int decodifica_letra(arvore* raiz);

/**
 * @fn decodifica()
 * @brief Decodifica o arquivo de entrada.
*/
void decodifica();

#endif // huffman_H_
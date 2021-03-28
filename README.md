# Compressão de Arquivos

Em computação os conceitos de reduzir, economizar ou até mesmo ganhar espaço são imprescindíveis a qualquer usuário de computador. Compreendida como o ato de reduzir o espaço ocupado por dados num determinado dispositivo, a compressão de dados é algo extremamente relacionado à vida das pessoas, diretamente ou indiretamente. A compressão de arquivos, na internet, ajuda a diminuir a quantidade de tráfego na grande rede, aumentando a velocidade de navegação, realização de downloads de arquivos e visualização de vídeos. Na vida offline, arquivos compactados são preferíveis quando há interesse de armazenamento de maior número de dados possível no menor espaço de memória secundária disponível, como em pen-drives, memmory cards, discos rígidos e demais unidades de memória.

![GitHub Logo](/Images/compressao.png)

<img src="https://github.com/caio-emiliano/Huffman-Compression/blob/main/Images/compressao.png">

Devido a sua grande utilizade, técnicas de compressão de dados são amplamente utilizadas. Diversas extensões de arquivos famosas, como **pdf** (textos, e-books), **mp3** (áudio, músicas), **gif** (imagens, fotos), **zip** (arquivos em geral), **mpg** (vídeos), utilizam algoritmos de compactação em suas concepções.

Diante disso, inúmeros algoritmos de compressão existem: Codificação de Huffman, Lempel-Ziv-Welch, Codificação aritmética, Codificação Run-length etc. Para o objetivo deste projeto, realizaremos a implementação da codificação de Huffman.

# Huffman Compression

O método de codificação de Huffman consiste em um algoritmo de compressão de dados que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. Desenvolvido em 1952 por David A. Huffman, utiliza uma árvore binária completa, chamada de árvore de Huffman e, é construída recursivamente a partir da junção dos dois símbolos de menor probabilidade, que são então somados em símbolos auxiliares e estes símbolos auxiliares recolocados no conjunto de símbolos. O processo termina quando todos os símbolos forem unidos em símbolos auxiliares, formando uma árvore binária. A árvore é então percorrida, atribuindo-se valores binários de 1 ou 0 para cada aresta, e os códigos são gerados a partir desse percurso.

<img src="https://github.com/caio-emiliano/Huffman-Compression/blob/main/Images/huffman-example.png">

## Exemplo de Codificação

Como exemplo de codificação e montagem da árvore de Huffman usaremos a sequinte sequência de caracteres: **AAAAAABBBBBCCCCDDDEEF**. Como primeiro passo do algoritmo, precisamos obter a frequência de cada caracter. Assim temos: 

<img src="https://github.com/caio-emiliano/Huffman-Compression/blob/main/Images/example_figure1.png">

O próximo passo é construirmos a árvore de Huffman. Para isso, basta escolhermos 2 nós de nosso domínio (neste caso representado pelos símbolos A, B, C, D, E e F) e uni-los. Na figura abaixo pode-se observar a representação desta etapa.

Fig2

Ao unirmos os nós E e F, criamos um nó pai cujo peso é a soma dos pesos dos filhos. Este novo nó é inserido no domínio de nós a serem unidos. Assim o processo se repetirá (agora unindo os nós D e E+F).

Fig3

Continuando o processo temos:

Fig4

Fig5

Por fim temos a última união, que será dos nós A+D+E+F com o nó B+C.

Fig6

Assim, gerando nossa árvore de Huffman que agora é uma árvore estritamente binária:

Fig7

Ao observamos as arestas da árvore, podemos perceber que cada caminho para um nó corresponde a seu código. Abaixo listamos os códigos Huffman para cada um dos símbolos que usamos:

Fig 8

Agora, ao codificarmos a nossa sequência original temos: 000000000000101010101011111111010010010011001100111 totalizando apenas 51 bits. A nossa compressão foi de 12 bits, ou cerca de 20% (dado que a sequência ogirinal possuia 63 bits).


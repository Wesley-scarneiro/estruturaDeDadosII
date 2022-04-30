/*
    Implementação de uma estrutura e funções para trabalhar com grafos direcionados.
    Os grafos serão representados por uma matriz de adjacências.
*/

// Valores booleanos
typedef int bool;

// Constantes
#define TRUE 1
#define FALSE 0 
#define MAX 100                 // Tamanho maximo da matriz
#define AN -1                   // Valor que representa uma aresta nula ou uma aresta ausente.
#define INVALIDO -1             // Vertice invalido ou ausente.



/*
    Estrutura de um grafo direcionado.
*/
typedef struct
{
    int **matriz;
    int nVertices;
    int nArestas;
}GRAFO;


/*
    Funções para manipular os grafos simples que serão utilizados.
*/

void alocarMatriz(GRAFO *grafo, int nv);

bool desalocarMatriz(GRAFO *grafo);

bool inicializarGrafo(GRAFO *grafo, int nv);

void insereAresta(int v1, int v2, int peso, GRAFO *grafo);

bool existeAresta(int v1, int v2, GRAFO *grafo);

bool removeAresta(int v1, int v2, int *peso, GRAFO *grafo);

bool listaAdjVazia(int v, GRAFO* grafo);

int primeiroListaAdj(int v, GRAFO* grafo);

int proxListaAdj(int v, GRAFO *grafo, int atual);

void imprimeGrafo(GRAFO *grafo);
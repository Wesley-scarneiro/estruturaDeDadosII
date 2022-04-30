/*
    Biblioteca para uma estrutura de dados e funções para trabalhar com grafos direcionados e não direcionados.
    Os grafos serão representados em uma lista de adjacências.
*/

// Valores booleanos
typedef int bool;

// Constantes
#define TRUE 1
#define FALSE 0 
#define MAX 100                 // Tamanho maximo da matriz.
#define AN -1                   // Valor que representa uma aresta nula ou uma aresta ausente.
#define INVALIDO -1             // Vertice invalido ou ausente.


/*
    Estrutura para representar cada aresta do grafo.
    'vdest' é o vértice de destino.
*/
typedef struct EstruturaAresta
{
    int vdest;
    int peso;
    struct EstruturaAresta *prox;
} ARESTA;

/*
    Estrutura de um grafo.
*/
typedef struct
{
    ARESTA *lista;              // Um array de listas do tipo ARESTA.
    int nVertices;
    int nArestas;
}GRAFO;

/*
    Funções para manipular os grafos.
*/

bool inicializarGrafo(GRAFO *grafo, int nv);

bool excluirGrafo(GRAFO *grafo);

bool insereAresta(int v1, int v2, int peso, GRAFO *grafo);

bool existeAresta(int v1, int v2, GRAFO *grafo);

bool removeAresta(int v1, int v2, int *peso, GRAFO *grafo);

bool listaAdjVazia(int v, GRAFO* grafo);

ARESTA* primeiroListaAdj(int v, GRAFO* grafo);

ARESTA* proxListaAdj(int v, GRAFO *grafo, ARESTA *atual);

void imprimeGrafo(GRAFO *grafo);
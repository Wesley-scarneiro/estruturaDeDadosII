/*
    Implementação de uma estrutura para trabalhar com grafos direcionados.
    Os grafos serão representados por uma matriz de adjacências.
*/

#include <malloc.h>
#include "grafo_matrizAdj.h"

/*
    Aloca uma matriz para a representação do grafo direcionado.
*/
void alocarMatriz(GRAFO *grafo, int nv)
{
    grafo->matriz = (int**) malloc(sizeof(int*)*nv);

    int i;
    for (i = 0; i < nv; ++i)
    {
        grafo->matriz[i] = (int*) malloc(sizeof(int)*nv);
    }
}

/*
    Para excluir a matriz e liberar a memória utilizada.
*/
bool desalocarMatriz(GRAFO *grafo)
{
    int i;

    if (grafo->matriz != NULL)
    {
        for (i = 0; i < grafo->nVertices; ++i)
        {
            free(grafo->matriz[i]);
        }
    
        free(grafo->matriz);

        return TRUE;
    }
    else
    {
        FALSE;
    }
}



/*
    Inicializa o grafo alocando uma matriz.
    Atribui -1 para todos os elementos a_ij da matriz.
    Atribui 'nv' a 'nVertices' e 0 em 'nArestas'.
*/
bool inicializarGrafo(GRAFO *grafo, int nv)
{
    if (nv <= 0 || nv > MAX)
    {
        return FALSE;
    }

    alocarMatriz(grafo, nv);
    int i, j;
    
    for (i = 0; i < nv; ++i)
    {
        for (j = 0; j < nv; ++j)
        {
            grafo->matriz[i][j] = AN;
        }
    }

    grafo->nVertices = nv;
    grafo->nArestas = 0;
    
    return TRUE;
}

/*
    Dado os vértices 'v1' e 'v2', é criada uma aresta com valor igual ao 'peso' repassado.
    O campo 'nArestas' é incrementado.
*/
void insereAresta(int v1, int v2, int peso, GRAFO *grafo)
{
    grafo->matriz[v1][v2] = peso;
    grafo->nArestas++;
}

/*
    Verifica se existe uma aresta conectando 'v1' e 'v2'.
    Se existir retorna TRUE, caso ao contrário, FALSE.
*/
bool existeAresta(int v1, int v2, GRAFO *grafo)
{
    if (grafo->matriz[v1][v2] != AN)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
    Se existir uma aresta entre 'v1' e 'v2', é atribuido o peso da aresta para 'peso' e depois a aresta é retirada.
    O campo 'nArestas' é decrementado.
*/
bool removeAresta(int v1, int v2, int *peso, GRAFO *grafo)
{
    if (grafo->matriz[v1][v2] != AN)
    {
        *peso = grafo->matriz[v1][v2];
        grafo->matriz[v1][v2] = AN;
        grafo->nArestas--;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
    Verifica se a lista de adjacências do vértice 'v' é vazia ou não (percorrendo as colunas da linha 'v').
    Se for vazia é retornado TRUE, caso ao contrário, FALSE.
*/
bool listaAdjVazia(int v, GRAFO* grafo)
{
    int j;

    for (j = 0; j < grafo->nVertices; ++j)
    {
        if (grafo->matriz[v][j] != AN)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*
    Retorna o primeiro vértice da lista de adjacência de 'v'.
    Se a lista estiver vazia, é retornado INVALIDO.
*/
int primeiroListaAdj(int v, GRAFO* grafo)
{
    int j;

    for (j = 0; j < grafo->nVertices; ++j)
    {
        if (grafo->matriz[v][j] != AN)
        {
            return j;
        }
    }

    return INVALIDO;
}

/*
    Retorna o próximo vértice adjacente a 'v' depois do vértice adjacente 'atual'.
    Se não houver outro vértice adjacente, é retornado a constante INVALIDO (-1).
*/
int proxListaAdj(int v, GRAFO *grafo, int atual)
{
    // Menor ou igual ao índice do penúltimo elemento.
    if (atual < grafo->nVertices - 1)
    {
        ++atual;

        if (grafo->matriz[v][atual] != AN)
        {
            return atual;
        }
        else
        {
            return INVALIDO;
        }
    }

    return INVALIDO;
}

void imprimeGrafo(GRAFO *grafo)
{
    int i, j;

    for (i = 0; i < grafo->nVertices; ++i)
    {
        for (j = 0; j < grafo->nVertices; ++j)
        {
            printf("%d ", grafo->matriz[i][j]);
        }
        
        printf("\n");
    }
}
/*
    Implementação de um grafo direcionado por meio de uma lista de adjacências.
*/

#include <stdio.h>
#include <malloc.h>
#include "grafo_listaAdj.h"

/*
    Inicializa a representação do grafo em uma lista de adjacências.
    Cria um array do tipo ARESTA, no qual haverá a representação da lista de adjacências de cada vértice do grafo.
    Após a alocação, percorre a lista para anular os ponteiros de cada vértice.
    Retorna TRUE se inicializou com sucesso ou FALSE caso contrário.
*/
bool inicializarGrafo(GRAFO *grafo, int nv)
{
    grafo->nVertices = nv;
    grafo->nArestas = 0;
    grafo->lista = (ARESTA*) malloc(sizeof(ARESTA)*nv);

    if (grafo->lista != NULL)
    {
        int i;
        for (i = 0; i < nv; ++i)
        {
            grafo->lista[i].prox = NULL;
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
    Exclui cada elemento das listas ligadas do array de ARESTAS e depois o ponteiro do array.
    Retorna TRUE se excluir o grafo ou FALSE caso contrário.
*/
bool excluirGrafo(GRAFO *grafo)
{
    if (grafo->lista != NULL)
    {
        ARESTA *prox, *apagar;
        int i;

        for (i = 0; i < grafo->nVertices; ++i)
        {
            prox = grafo->lista[i].prox;

            while (prox != NULL)
            {
                apagar = prox;
                prox = prox->prox;
                free(apagar);
            }
        }

        free(grafo->lista);
        grafo->lista = NULL;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
    Insere uma aresta (u, v) na lista de adjacencia de 'u'.
    A inserção não é ordenada e não verifica a preexistência de uma aresta.
    O intervalo do índice de cada vértice é [0; nv-1].
    Todo vértice 'v' é inserido no início da lista de 'u'.
    A cada inserção é realizada a atualização do campo 'nArestas'.
    A função retorna TRUE se a inserção da aresta foi realizada ou FALSE caso contrário.
*/
bool insereAresta(int v1, int v2, int peso, GRAFO *grafo)
{
    if ((v1 < 0 || v1 >= grafo->nVertices) || (v2 < 0 || v2 >= grafo->nVertices))
    {
        return FALSE;
    }

    ARESTA *novo, *prox;
    novo = (ARESTA*) malloc(sizeof(ARESTA));
    novo->peso = peso;
    novo->vdest = v2;

    prox = grafo->lista[v1].prox;
    grafo->lista[v1].prox = novo;
    novo->prox = prox;
    ++grafo->nArestas;

    return TRUE;
}

/*
    Verifica se uma aresta (u, v) existe no grafo, buscando 'v' na lista de ajacência de 'u'.
    O intervalo do índice de cada vértice é [0; nv-1].
    Retorna TRUE se a aresta existe ou FALSE caso contrário.
*/
bool existeAresta(int v1, int v2, GRAFO *grafo)
{
    if ((v1 < 0 || v1 >= grafo->nVertices) || (v2 < 0 || v2 >= grafo->nVertices))
    {
        return FALSE;
    }

    ARESTA *prox = grafo->lista[v1].prox;
    
    while (prox != NULL)
    {
        if (prox->vdest == v2)
        {
            return TRUE;
        }
        prox = prox->prox;
    }

    return FALSE;
}

/*
    Remove uma aresta (u, v) do grafo.
    O intervalo do índice de cada vértice é [0; nv-1].
    Se a aresta existir, remove o vértice 'v' da lista de adjacência de 'u'.
    A cada remoção é realizada a atualização do campo 'nArestas'.
    Retorna TRUE se a remoção foi realizada ou FALSE caso contrário.
*/
bool removeAresta(int v1, int v2, int *peso, GRAFO *grafo)
{
    if ((v1 < 0 || v1 >= grafo->nVertices) || (v2 < 0 || v2 >= grafo->nVertices))
    {
        return FALSE;
    }

    bool existe = existeAresta(v1, v2, grafo);

    if (existe == TRUE)
    {
        ARESTA *prox, *ant;
        prox = grafo->lista[v1].prox;
        ant = &grafo->lista[v1];
        
        while (prox != NULL)
        {
            if (prox->vdest == v2)
            {
                *peso = prox->peso;
                ant->prox = prox->prox;
                free(prox);
                --grafo->nArestas;
                return TRUE;
            }
            ant = prox;
            prox = prox->prox;
        }
    }
    else
    {
        return FALSE;
    }
}

/*
    Verifica se a lista de adjacência do vértice 'v' está vazia ou não.
    O intervalo dos índices de 'v' é [0; nv-1].
    Retorna TRUE se vazia ou FALSE caso contrário.
*/
bool listaAdjVazia(int v, GRAFO* grafo)
{
    if (v < 0 || v >= grafo->nVertices)
    {
        return FALSE;
    }
    else
    {
        if (grafo->lista[v].prox == NULL)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

/*
    Retorna o endereço de memória do primeiro vértice da lista de adjacência de 'v'.
    O retorno será NULL se a lista de adjacência de 'v' estiver vazia.
*/
ARESTA* primeiroListaAdj(int v, GRAFO* grafo)
{
    if (v < 0 || v >= grafo->nVertices)
    {
        return NULL;
    }
    else if (grafo->lista[v].prox != NULL)
    {
        return grafo->lista[v].prox;
    }
    else
    {
        return NULL;
    }
}

/*
    Retorna o endereço do próximo vértice adjacente a 'v' que está depois do vértice 'atual'.
    Não realiza a chegagem se o vértice 'atual' de fato é adjacente a 'v'.
    Retorna o endereço se houver próximo ou NULL caso contrário.
*/
ARESTA* proxListaAdj(int v, GRAFO *grafo, ARESTA *atual)
{
    if (grafo->lista[v].prox == NULL || atual == NULL)
    {
        return NULL;
    }
    else if (atual->prox != NULL)
    {
        return atual->prox;
    }
    else
    {
        return NULL;
    }
}

/*
    Impreme a lista de adjacência de cada vértice do grafo.
*/
void imprimeGrafo(GRAFO *grafo)
{
    printf("++ Imprimindo grafo ++\n-> Total de vertices: %d\n-> Total de arestas: %d\n", grafo->nVertices, grafo->nArestas);

    int i;
    ARESTA *prox;

    for (i = 0; i < grafo->nVertices; ++i)
    {
        prox = grafo->lista[i].prox;
        printf("v%d: ", i);

        while (prox != NULL)
        {
            printf("(v%d, %d); ", prox->vdest, prox->peso);
            prox = prox->prox;
        }
        printf("\n");
    }
}
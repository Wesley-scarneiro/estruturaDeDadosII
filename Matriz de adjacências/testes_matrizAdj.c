/*
    Programa para testar a implementação de um grafo direcionado.
    O grafo é implementado através de uma matriz de adjacências.

    1) Inicialização do grafo [ok]
    2) Inserção de arestas [ok]
    3) Verificação de arestas [ok]
    4) Remoção de arestas [ok]
    5) Verificação da lista de adjacências de um vértice [ok]
    6) Primeiro vértice adjacente [ok]
    7) Próximo vértice adjacente [ok]
    8) Desalocação da matriz [ok]
*/

#include <stdio.h>
#include "implementacao_matrizAdj.c"

/*
    Imprime o estado do grafo: Quantidade de vértices e arestas.
    Chama a função para imprimir o grafo.
*/
void estadoGrafo(GRAFO *grafo)
{
    printf("\n++ Estado atual do grafo ++\n");
    printf("-> Total de vertices: %d\n", grafo->nVertices);
    printf("-> Total de arestas: %d\n\n", grafo->nArestas);
    imprimeGrafo(grafo);
    printf("\n");
}

/*
    Teste para a inicialização da matriz e do grafo.
*/
void testarInicializacao(GRAFO *grafo, int n)
{
    if (inicializarGrafo(grafo, n))
    {
        printf("-> Grafo inicializado. Tamanho = %d.\n", n);
        estadoGrafo(grafo);
    }
    else
    {
        printf("-> Grafo nao inicializado. Tamanho = %d excede o permitido.\n", n);
    }
}

/*
    Recebe as arestas da matriz de adjacências.
    Chama a função 'insereAresta'.
    Os pesos são definidos para 10.
*/
void receberArestas(GRAFO *grafo, int qtdArestas)
{
    printf("-> Matriz %dx%d | Arestas (u v):\n", grafo->nVertices, grafo->nVertices, qtdArestas);

    int i, v1, v2;

    for (i = 0; i < qtdArestas; ++i)
    {
        scanf("%d %d", &v1, &v2);
        insereAresta(v1, v2, 10, grafo);
    }

    printf("-> Grafo recebido.\n");
    estadoGrafo(grafo);
}

/*
    Verifica a existência de uma aresta entre v1 e v2.
*/
void verificarAresta(int v1, int v2, GRAFO *grafo)
{
    if (existeAresta(v1, v2, grafo))
    {
        printf("-> Existe aresta: %d --> %d.\n", v1, v2);
    }
    else
    {
        printf("-> Nao existe aresta: %d --> %d.\n", v1, v2);
    }
}

/*
    Testa a remoção de uma aresta no grafo.
*/
void testarRemocao(int v1, int v2, GRAFO *grafo)
{
    int p;
    
    if (removeAresta(v1, v2, &p, grafo))
    {
        printf("-> Aresta %d -- (%d) --> %d removida\n", v1, p, v2);
    }
    else
    {
        printf("-> Aresta %d --> %d nao existe\n", v1, v2);
    }
}

/*
    Verifica a lista de adjacencia de um vértice do grafo.
*/
void testeListaAdj(int v, GRAFO *grafo)
{
    if (listaAdjVazia(v, grafo))
    {
        printf("-> Lista de adjacencia de '%d' eh vazia.\n", v);
    }
    else
    {
        printf("-> Lista de adjacencia de '%d' nao eh vazia.\n", v);
    }
}

/*
    Retorna  o primeiro vértice adjacente de um vértice do grafo.
*/
void testePrimeiroAdj(int v, GRAFO *grafo)
{
    int u = primeiroListaAdj(v, grafo);

    if (u != INVALIDO)
    {
        printf("-> Vertice '%d' eh o primeiro adjacente a '%d'.\n", u, v);
    }
    else
    {
        printf("-> Lista de adjacencia de '%d' eh vazia.\n", v);
    }
}

/*
    REtorno o próximo vértice adjacente de um vértice do grafo.
*/
void testeProxAdj(int v, GRAFO *grafo, int atual)
{
    int u = proxListaAdj(v, grafo, atual);

    if (u != INVALIDO)
    {
        printf("-> Vertice '%d' eh o proximo adjacente a '%d'.\n", u, v);
    }
    else
    {
        printf("-> Nao existe proximo para o vertice '%d' adjacente a '%d'\n", atual, v);
    }
}

void testarDesalocar(GRAFO *grafo)
{
    if (desalocarMatriz(grafo))
    {
        printf("-> Matriz desalocada com sucesso. Grafo nao existe mais.\n");
    }
    else
    {
        printf("-> Matriz nao desalocada. Algum problema ocorreu.\n");
    }
}

int main()
{
    GRAFO grafo;

    // Inicializando o grafo
    printf("++ Teste de inicializacao do grafo ++\n");
    testarInicializacao(&grafo, 500);
    testarInicializacao(&grafo, 5);

    /*
        Entrada da matriz:
        0 0 1 0 1
        1 1 1 1 0
        0 1 0 0 0
        1 1 0 0 1
        1 0 0 0 0

        Arestas:
        0 2
        0 4
        1 0
        1 1
        1 2
        1 3
        2 1
        3 0
        3 1
        3 4
        4 0
    */
   printf("++ Teste de insercoes de arestas no grafo ++\n");
   receberArestas(&grafo, 11);

    // Verificando algumas arestas.
    printf("++ Teste de verificacoes das arestas do grafo ++\n");    
    verificarAresta(0, 2, &grafo);
    verificarAresta(0, 4, &grafo);
    verificarAresta(2, 0, &grafo);
    verificarAresta(4, 4, &grafo);

    // Removendo arestas
    printf("++ Teste de remocao de arestas ++\n");
    testarRemocao(4, 0, &grafo);
    testarRemocao(1, 1, &grafo);
    testarRemocao(1, 4, &grafo);
    estadoGrafo(&grafo);

    // Lista de adjacências de um vértice
    printf("++ Teste da lista de adjacencias de um vertice do grafo ++\n");
    testeListaAdj(4, &grafo);
    testeListaAdj(1, &grafo);

    // Primeiro vértice adjacente
    printf("++ Teste do primeiro vertice adjacente de um vertice do grafo ++\n");
    testePrimeiroAdj(0, &grafo);
    testePrimeiroAdj(4, &grafo);

    // Próximo vértice adjacente
    printf("++ Teste do proximo vertice adjacente a um vertice do grafo ++\n");
    testeProxAdj(3, &grafo, 0);
    testeProxAdj(3, &grafo, 4);

    // Desalocando a matriz
    printf("++ Testando o desalocamento da matriz do grafo ++\n");
    testarDesalocar(&grafo);

    return 0;
}

/* SAÍDA:

++ Teste de inicializacao do grafo ++
-> Grafo nao inicializado. Tamanho = 500 excede o permitido.
-> Grafo inicializado. Tamanho = 5.

++ Estado atual do grafo ++
-> Total de vertices: 5
-> Total de arestas: 0

-1 -1 -1 -1 -1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1

++ Teste de insercoes de arestas no grafo ++
-> Matriz 5x5 | Arestas (u v):
0 2
0 4
1 0
1 1
1 2
1 3
2 1
3 0
3 1
3 4
4 0
-> Grafo recebido.

++ Estado atual do grafo ++
-> Total de vertices: 5
-> Total de arestas: 11

-1 -1 10 -1 10
10 10 10 10 -1
-1 10 -1 -1 -1
10 10 -1 -1 10
10 -1 -1 -1 -1

++ Teste de verificacoes das arestas do grafo ++
-> Existe aresta: 0 --> 2.
-> Existe aresta: 0 --> 4.
-> Nao existe aresta: 2 --> 0.
-> Nao existe aresta: 4 --> 4.
++ Teste de remocao de arestas ++
-> Aresta 4 -- (10) --> 0 removida
-> Aresta 1 -- (10) --> 1 removida
-> Aresta 1 --> 4 nao existe

++ Estado atual do grafo ++
-> Total de vertices: 5
-> Total de arestas: 9

-1 -1 10 -1 10
10 -1 10 10 -1
-1 10 -1 -1 -1
10 10 -1 -1 10
-1 -1 -1 -1 -1

++ Teste da lista de adjacencias de um vertice do grafo ++
-> Lista de adjacencia de '4' eh vazia.
-> Lista de adjacencia de '1' nao eh vazia.
++ Teste do primeiro vertice adjacente de um vertice do grafo ++
-> Vertice '2' eh o primeiro adjacente a '0'.
-> Lista de adjacencia de '4' eh vazia.
++ Teste do proximo vertice adjacente a um vertice do grafo ++
-> Vertice '1' eh o proximo adjacente a '3'.
-> Nao existe proximo para o vertice '4' adjacente a '3'
++ Testando o desalocamento da matriz do grafo ++
-> Matriz desalocada com sucesso. Grafo nao existe mais.

*/
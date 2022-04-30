/*
    Programa para testar a implementação do grafo em uma lista de adjacências.

    1) Inicialização do grafo [ok]
    2) Insersão de arestas [ok]
    3) Verificação de arestas [ok]
    4) Remoção de arestas [ok]
    5) Verificação de adjacência vazia [ok]
    6) Verificação do primeiro vértice adjacente [ok]
    7) Verificação do próximo vértice adjacente [ok]
    8) Visualização do grafo (impressão) [ok]
    9) Exclusão do grafo (Apagar lista de adjacências) [ok]
*/

#include <stdio.h>
#include "implementacao_listaAdj.c"

/*
    Função para testar a inicialização do grafo.
*/
void testeInicializarGrafo(GRAFO *grafo, int nv)
{
    if (inicializarGrafo(grafo, nv) == TRUE)
    {
        printf("++ Grafo inicializado com sucesso ++\n");
        printf("-> nVertices: %d\n-> nArestas: %d\n", grafo->nVertices, grafo->nArestas);
    }
    else
    {
        printf("++ Grafo nao inicializado ++\n");
    }
}

/*
    Função para receber os dados das arestas a partir de um arquivo de entrada.
    Realiza apenas a leitura do arquivo.txt (r).
    n: Número total de arestas.
    (u, v): Par de vértices que representam uma aresta.
*/
void entradaDeDados(GRAFO *grafo)
{
    FILE *fp = fopen("dadosDeEntrada.txt", "r");
    
    if (fp != NULL)
    {
        printf("++ Arquivo de dados aberto com sucesso ++\n");
    }
    else
    {
        printf("++ Falha ao abrir arquivo de dados ++\n");
        exit(1);
    }

    
    int i, n, u, v, peso;

    // Recebendo o número total de arestas.
    fscanf(fp, "%d", &n);
    printf("-> Total de arestas a serem recebidas: %d\n", n);

    // Recebendo as arestas e pesos.
    for (i = 0; i < n; ++i)
    {
        fscanf(fp, "%d %d %d", &u, &v, &peso);
        if (insereAresta(u, v, peso, grafo) == TRUE)
        {
            printf("-> (%d) Aresta v%d --(%d)--> v%d recebida com sucesso.\n", (i+1), u, peso, v);
        }
        else
        {
            printf("-> (%d) Aresta nao recebida.\n", (i+1));
        }
    }

    fclose(fp);
    printf("-> Arquivo de dados fechado.\n");
}

/*
    Verificando a existência das arestas do grafo.
*/
void testarExisteAresta(GRAFO *grafo)
{
    printf("++ Verificando a existencia das arestas do grafo ++\n");
    int i, j;
    for (i = 0; i < grafo->nVertices; ++i)
    {
        for (j = 0; j < grafo->nVertices; ++j)
        {
            if (existeAresta(i, j, grafo))
            {
                printf("-> Existe a aresta v%d --> v%d.\n", i, j);
            }
            else
            {
                printf("-> Nao existe a aresta v%d --> v%d.\n", i, j);
            }
        }
    }
}

/*
    Testa a remoção de algumas arestas do grafo.
*/
void testarRemoveAresta(int v1, int v2, GRAFO *grafo)
{
    int peso;

    if (removeAresta(v1, v2, &peso, grafo))
    {
        printf("-> Aresta v%d --(%d)--> v%d removida.\n", v1, peso, v2);
    }
    else
    {
        printf("-> Aresta v%d --> v%d nao existe.\n", v1, v2);
    }
}

/*
    Veriricando a lista de adjacências de cada vértice se está vazia.
*/
void testarListaAdjVazia(GRAFO* grafo)
{
    int i;
    for (i = 0; i < grafo->nVertices; ++i)
    {
        if (listaAdjVazia(i, grafo) == TRUE)
        {
            printf("-> Lista de adjacencia do vertice 'v%d' eh vazia.\n", i);
        }
        else
        {
            printf("-> Lista de adjacencia do vertice 'v%d' nao eh vazia.\n", i);
        }
    }
}

/*
    Testando a verificação do primeiro vértice adjacente de cada lista.
*/
void testarPrimeiroListaAdj(GRAFO* grafo)
{
    ARESTA *primeiro;
    int i;

    for (i = 0; i < grafo->nVertices; ++i)
    {
        primeiro = primeiroListaAdj(i, grafo);

        if (primeiro != NULL)
        {
            printf("-> Vertice 'v%d' eh o primeiro da lista do vertice 'v%d'.\n", primeiro->vdest, i);
        }
        else
        {
            printf("-> Vertice 'v%d' nao possui adjacencias.\n", i);
        }
    }
}

/*
    Testando a verificação do próximo vértice adjacente de cada lista.
*/
void testarProxListAdj(GRAFO *grafo)
{
    ARESTA *primeiro, *prox;
    int i;

    for (i = 0; i < grafo->nVertices; ++i)
    {
        primeiro = primeiroListaAdj(i, grafo);
        prox = proxListaAdj(i, grafo, primeiro);

        if (prox != NULL)
        {
            printf("-> (Lista de v%d) O vertice 'v%d' eh o proximo de 'v%d'.\n", i, prox->vdest, primeiro->vdest);
        }
        else
        {
            printf("-> (Lista de v%d) Nao existe proximo.\n", i);
        }
        
    }
}

/*
    Testando a exclusão do grafo da memória.
*/
void testarExcluirGrafo(GRAFO *grafo)
{

    if (excluirGrafo(grafo) != FALSE)
    {
        printf("-> Grafo escluido da memoria.\n");
    }
    else
    {
        printf("-> Algum problema ocorreu ao tentar-se excluir o grafo.\n");
    }
}

int main()
{

    /*
        Teste de inicialização do grafo.
        Número de vértices = 5.
    */
    GRAFO grafo;
    testeInicializarGrafo(&grafo, 5);

    /*
        Obtendo as arestas do grafo no arquivo de entrada.
    */
   entradaDeDados(&grafo);
   imprimeGrafo(&grafo);

   /*
        Verificando a existência de algumas arestas do grafo.
   */
   testarExisteAresta(&grafo);

   /*
        Testando a remoção de algumas arestas existentes e não existentes no grafo.
   */
  printf("++ Testando a remocao de algumas aretas do grafo ++\n");
  testarRemoveAresta(0, 1, &grafo);
  testarRemoveAresta(0, 5, &grafo);
  testarRemoveAresta(4, 3, &grafo);
  testarRemoveAresta(5, 3, &grafo);
  imprimeGrafo(&grafo);

  /*
        Testando o reconhecimento de lista de adjacências vazias.
  */
   printf("++ Testando a busca de listas de adjacencias vazias ++\n");
   testarListaAdjVazia(&grafo);

   /*
    Testando a verificação do primeiro vértice adjacente de cada lista.
   */
   printf("++ Testando a verificacao do primeiro vertice adjacente de cada lista ++\n");
   testarPrimeiroListaAdj(&grafo);

   /*
        Testando a verificação dos próximos vértice de cada lista.
   */
   printf("++ Verificando os proximos vertices de cada lista ++\n");
   testarProxListAdj(&grafo);

   /*
        Removendo o grafo da memória.
   */
   printf("++ Removendo o grafo da memoria ++\n");
   testarExcluirGrafo(&grafo);
   testarExcluirGrafo(&grafo);

    return 0;
}
/*
    EXERCÍCIO DE PROGRAMAÇÃO - ESTRUTURA DE DADOS II
    Professor: Helton
    Aluno: Wesley Carneiro

    Programa que implementa o algoritmo de Prim, para a produção de uma árvore geradora mínima (AGM), de uma grafo não-direcionado e conexo.
    O algoritmo implementado seguiu uma estratégia de resolução mais simples e com uso de um arranjo para representar a AGM, ao invés de uma fila de prioridades.
    Algoritmo possui complexidade O(V*E), sendo V vértices e E arestas de um grafo G(v, E).

    Para a execução do programa, é necessário especificar na linha de comando um arquivo de entrada e um arquivo de saída, definidos no parâmetro da função main().
    O arquivo de entrada contem o número total de vértices e arestas, além do par de vértices 'u v' de cada aresta do grafo.
    O arquivo de saída especifica o custo mínimo do ARG e suas arestas. 
    
    fonte: https://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/

#include <stdio.h>
#include <malloc.h>

// Valores booleanos
typedef int bool;

// Constantes
#define TRUE 1
#define FALSE 0 
#define MAX 100                 // Tamanho maximo da matriz
#define AN -1                   // Valor que representa uma aresta nula ou uma aresta ausente.
#define INVALIDO -1             // Vertice invalido ou ausente.
#define INFINITY 1000000  	// (10^6) Peso arbitrario para as arestas da árvore geradora mínima (AGM).


/*
    Estrutura de um grafo direcionado/não-direcionado.
*/
typedef struct
{
    int **matriz;
    int *arvore;	// AGM
    int custo;		// Custo da AGM
    int nVertices;
    int nArestas;
}GRAFO;


/*
    Aloca uma matriz para a representação do grafo.
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
        free(grafo->arvore);

        return TRUE;
    }
    else
    {
        FALSE;
    }
}



/*
    Inicializa o grafo alocando uma matriz e o array da AGM.
    Atribui -1 para todos os elementos a_ij e a_ji da matriz.
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
    grafo->custo = 0;
    grafo->arvore = (int*) malloc(sizeof(int)*nv);
    
    return TRUE;
}

/*
    Dado os vértices 'v1' e 'v2', é criada uma aresta com valor igual ao 'peso' repassado.
    O campo 'nArestas' é incrementado.
*/
void insereAresta(int v1, int v2, int peso, GRAFO *grafo)
{
    grafo->matriz[v1][v2] = peso;
    grafo->matriz[v2][v1] = peso;
    grafo->nArestas++;
}

/*
    Função para receber os dados das arestas a partir de um arquivo de entrada.
    Realiza apenas a leitura e escrita dos arquivos especificados.
    nv: Número total de vértices.
    na: Número total de arestas.
    (u, v): Par de vértices que representam uma aresta.
*/
void entradaDeDados(GRAFO *grafo, char *argv[], FILE *fp1, FILE *fp2)
{
    if (fp1 == NULL)
    {
        fprintf(fp2, "Falha ao abrir arquivo de dados\n");
        exit(1);
    }

    int i, nv, na, u, v, peso;

    // Recebendo o número total de vértices, arestas e inicializando o grafo.
    fscanf(fp1, "%d %d", &nv, &na);
    inicializarGrafo(grafo, nv);

    // Recebendo as arestas e pesos.
    for (i = 0; i < na; ++i)
    {
        fscanf(fp1, "%d %d %d", &u, &v, &peso);
        insereAresta(u, v, peso, grafo);
    }

    fclose(fp1);
}

/*
    Imprime as arestas da AGM.
    Como a raiz é sempre definida no vértice 0, a iteração começa a partir de i = 1.
    As arestas são imprimidas na ordem de cada filho de um nó.
*/
void imprimeGrafo(GRAFO *grafo, FILE *fp)
{
    int i, j;

    fprintf(fp, "%d\n", grafo->custo);
    for (i = 1; i < grafo->nVertices; ++i)
    {
        fprintf(fp, "%d %d\n", grafo->arvore[i], i);
    }
}

/*
    Recebe um grafo e um array (pais de cada nó) para representar o custo e os vértices finais da árvore geradora mínima (AGM).
    O grafo recebido deve ser não-direcionado e conexo.
    Neste algoritmo, não é utilizada uma fila de prioridades, ao invés disso, é realizada a verificação dos menores pesos de 
    arestas de forma iterativa.
    Após ser encontrada a aresta de menor peso entre um vértice 'u' e 'v', guardamos o seu custo em um somatório.
*/
void algoritmoDePrim(GRAFO *grafo)
{
    int i;

    // Inicializando o array de vértices da AGM.
    for (i = 0; i < grafo->nVertices; ++i)
    {
        grafo->arvore[i] = -1;
    }

   // Definindo a raiz da AGM.
   grafo->arvore[0] = 0;

    while (TRUE) 
    {
        int min = INFINITY;
        int x, y, u, v;

        // Iterações para buscar a aresta de menor custo entre 'u' e 'v'.
        for (u = 0; u < grafo->nVertices; ++u) 
        {
            if (grafo->arvore[u] == -1)
            {
                continue;
            }
        
            for (v = 0; v < grafo->nVertices; ++v)
            {
                if (grafo->arvore[v] == -1 && (grafo->matriz[u][v] != -1 && grafo->matriz[u][v] < min))
                { 
                    min = grafo->matriz[u][v];
                    x = u;
                    y = v;
                }
            }
        }

        if (min == INFINITY)
        {
            break;
        }
        
        // O vértice de índice 'y' se torna filho de 'x'. 
        grafo->arvore[y] = x;
        grafo->custo += grafo->matriz[x][y];
    }
}

/*
	argv[1]: Arquivo de entrada, que contém a representação do grafo.
	argv[2]: Arquivo de saída, que contém o custo e arestas de uma AGM.
*/
int main(int args, char *argv[])
{
    GRAFO grafo;
    FILE *fp1 = fopen(argv[1], "r"); // Leitura
    FILE *fp2 = fopen(argv[2], "w"); // Escrita

    entradaDeDados(&grafo, argv, fp1, fp2);
    fclose(fp1);
    algoritmoDePrim(&grafo);
    imprimeGrafo(&grafo, fp2);
    fclose(fp2);
    desalocarMatriz(&grafo);
    
    return 0;
}


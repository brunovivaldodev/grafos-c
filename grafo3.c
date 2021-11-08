#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "grafo3.h"
#include <stdbool.h>

static int V = 0;

// Aloca memória para a criação de um Grafo e inicializa os dados das arestas.
Tipo_Grafo *cria_grafo(int tamanho)
{
    Tipo_Grafo *grafo;
    int i, j;

    grafo = (Tipo_Grafo *)malloc(sizeof(Tipo_Grafo) * 2);
    grafo->vertices = (Tipo_Vertice *)malloc(sizeof(Tipo_Vertice) * tamanho * 2);
    grafo->arestas = (Tipo_Aresta **)malloc(sizeof(Tipo_Aresta) * tamanho * 2);
    grafo->num_vertices = 0;

    for (i = 0; i < tamanho; i++)
    {
        grafo->arestas[i] = (Tipo_Aresta *)malloc(sizeof(Tipo_Aresta) * tamanho * 2);
    }

    for (i = 0; i < tamanho; i++)
    {
        for (j = 0; j < tamanho; j++)
        {
            grafo->arestas[i][j].conectado = 0;
            grafo->arestas[i][j].pessoa = INFINITO;
            grafo->arestas[i][j].visitada = 0;
        }
    }
    return grafo;
}

void imprime(Tipo_Grafo *grafo)
{
    int i, k;
    for (i = 0; i <= grafo->num_vertices; i++)
    {
        for (k = 0; k <= grafo->num_vertices; k++)
            printf("%d %d %d\n", i, k, grafo->arestas[i][k].pessoa);
    }
}

void imprimirRotas(Tipo_Grafo *grafo)
{
    int i, k;
    for (i = 0; i <= grafo->num_vertices; i++)
    {
        for (k = 0; k <= grafo->num_vertices; k++)
            if (grafo->arestas[i][k].pessoa != 1000000)
                printf("%d %d %d\n", i, k, grafo->arestas[i][k].pessoa);
    }
}
void imprimirRotasComTotal(Tipo_Grafo *grafo)
{
    int i, k, b;
    b = 0;
    for (i = 0; i <= grafo->num_vertices; i++)
    {
        for (k = 0; k <= grafo->num_vertices; k++)
            if (grafo->arestas[i][k].pessoa != 1000000)
            {
                printf("%d %d %d\n", i, k, grafo->arestas[i][k].pessoa);
                b += grafo->arestas[i][k].pessoa;
            }
    }
    printf("O total de pessoas é %d", b);
}

void imprimirRotasAEliminar(Tipo_Grafo *grafo)
{
    int i, k;
    for (i = 0; i <= grafo->num_vertices; i++)
    {
        for (k = 0; k <= grafo->num_vertices; k++)
        {
            if (grafo->arestas[i][k].pessoa != 1000000 && grafo->arestas[i][k].visitada == 0)
            {
                printf("%d %d %d\n", i, k, grafo->arestas[i][k].pessoa);
            }
        }
    }
}
// Faz uma busca para encontrar um vertice a partir de uma cidade.
int busca_vertice(Tipo_Grafo *grafo, int cidade)
{
    int i;
    for (i = 0; i < V; i++)
        if (grafo->vertices[i].cidade == cidade)
            return i;
    return -1;
}

// Insere uma cidade em um vertice do Grafo.
int insere_vertice(Tipo_Grafo *grafo, int cidade)
{
    if (busca_vertice(grafo, cidade) == -1)
    {
        grafo->vertices[grafo->num_vertices].cidade = cidade;
        grafo->vertices[grafo->num_vertices].chave = grafo->num_vertices;
        grafo->num_vertices++;
        V = grafo->num_vertices + 1;
        return 1;
    }
    return 0;
}

int remover_vertice(Tipo_Grafo *grafo, int cidade)
{

    int i, j;
    if (busca_vertice(grafo, cidade) != -1)
    {
        for (i = 0; i <= V; i++)
        {
            grafo->arestas[cidade][i].conectado = 0;
            grafo->arestas[cidade][i].pessoa = INFINITO;
            grafo->arestas[cidade][i].visitada = 0;
            grafo->arestas[i][cidade].conectado = 0;
            grafo->arestas[i][cidade].pessoa = INFINITO;
            grafo->arestas[i][cidade].visitada = 0;
        }
        // grafo->num_vertices--;
        V = grafo->num_vertices - 1;
        return 1;
    }
    return 0;
}
// Insere uma aresta (ligação de uma cidade a outra) no Grafo.
void insere_aresta(Tipo_Grafo *grafo, int chave_1, int chave_2, int pessoas)
{
    grafo->arestas[chave_1][chave_2].conectado = 1;
    grafo->arestas[chave_1][chave_2].pessoa = pessoas;
    grafo->arestas[chave_2][chave_1].conectado = 1;
    grafo->arestas[chave_2][chave_1].pessoa = pessoas;
}

// Libera a memória utilizada pelo Grafo.
void termina_grafo(Tipo_Grafo *grafo, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
        free(grafo->arestas[i]);

    free(grafo->vertices);
    free(grafo);
}

// Calcula as distâncias de uma origem a todos os outros vértices do Grafo.
void dijkstra(Tipo_Grafo *grafo, int origem, int destino)
{
    int dist[grafo->num_vertices + 2], perm[grafo->num_vertices + 2], path[grafo->num_vertices + 2];
    int corrente, i, k, dc;
    int menor_quantidade_pessoas, nova_menor_quantidade_pessoas;

    /* Inicializa todos os índices de 'perm' como 0 e de 'dist' como INFINITY */
    for (i = 0; i <= grafo->num_vertices + 2; i++)
    {
        perm[i] = NAOMEMBRO;
        dist[i] = INFINITO;
    }

    /* Inclui 's' em perm (perm[s]=1) e configura(armazena) sua distancia como sendo zero */
    perm[origem] = MEMBRO;
    dist[origem] = 0;

    /* define 's' como origem (fonte) da busca */
    corrente = origem;
    k = corrente;

    while (corrente != destino)
    {

        menor_quantidade_pessoas = INFINITO;
        dc = dist[corrente];

        for (i = 0; i <= grafo->num_vertices + 2; i++)
        {

            //se o elemento NÃO está em perm
            if (perm[i] == NAOMEMBRO)
            {

                if (grafo->arestas[corrente][i].conectado)
                {
                    nova_menor_quantidade_pessoas = dc + grafo->arestas[corrente][i].pessoa;

                    if (nova_menor_quantidade_pessoas < dist[i])
                    {
                        dist[i] = nova_menor_quantidade_pessoas;
                        path[i] = corrente;
                    }
                }

                if (dist[i] < menor_quantidade_pessoas)
                {
                    menor_quantidade_pessoas = dist[i];
                    k = i;
                }
            }
        }

        /* embora estamos assumindo grafos ponderados e conexos, este if garante que
         em caso de não existência de um caminho o programa não entre em loop infinito */
        if (corrente == k)
        {
            printf("\n\nCAMINHO NAO EXISTE\n\n");
            return;
        }
        corrente = k;
        perm[corrente] = MEMBRO;
    }

    printf("\n\nRESULTADO: ");
    int caminho = destino;

    printf("%d <- ", destino);

    while (caminho != origem)
    {
        printf("%d", path[caminho]);
        caminho = path[caminho];

        if (caminho != origem)
            printf(" <- ");
    }
    printf("\n\ncusto: %d\n\n", dist[destino]);
}

int circulacaoMinima(Tipo_Grafo *grafo)
{
    int no_edge;
    int selected[V];

    memset(selected, false, sizeof(selected));

    no_edge = 0;

    selected[0] = true;

    int x;
    int y;

    printf("Caminhos a eliminar\n");

    while (no_edge < V - 1)
    {

        int min = INFINITO;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < V; j++)
                {
                    if (!selected[j] && grafo->arestas[i][j].pessoa)
                    {
                        if (min > grafo->arestas[i][j].pessoa)
                        {
                            min = grafo->arestas[i][j].pessoa;
                            grafo->arestas[i][j].visitada = 1;
                            grafo->arestas[j][i].visitada = 1;
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        selected[y] = true;
        no_edge++;
    }
    imprimirRotasAEliminar(grafo);

    return 0;
}

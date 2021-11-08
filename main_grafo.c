
#include "grafo3.c"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Menu()
{
	printf("___________________SEJA BEM-VINDO ________________\n");
	printf("| 1.Adicionar ponto                              |\n");
	printf("| 2.Remover ponto                                |\n");
	printf("| 3.Adicionar rota                               |\n");
	printf("| 4.Eliminar rota                                |\n");
	printf("| 5.Destruir o plano de rotas                    |\n");
	printf("| 6.Imprimir rotas                               |\n");
	printf("| 7.Procurar melhor rota minima                  |\n");
	printf("| 8.Circulaçao minima                            |\n");
	printf("| 9.Mostrar todas as rotas                       |\n");
	printf("| 10.Sair                                        |\n");
	printf("__________________________________________________");
}
int main(int argc, char *argv[])
{
	Tipo_Grafo *grafo;
	int vertice, aresta;
	printf("Digite o numero de vertices\n");
	scanf("%i", &vertice);
	printf("Digite o numero de arestas\n");
	scanf("%i", &aresta);
	grafo = cria_grafo(vertice + 3);
	int i, j;
	for (i = 0; i < vertice; i++)
	{
		insere_vertice(grafo, i);
	}
	int chave1, chave2, pessoas;
	for (int j = 1; j <= aresta; j++)
	{
		scanf("%i %i %i", &chave1, &chave2, &pessoas);
		if (chave1 == 0 && chave2 == 0)
		{
			printf("saindo");
			break;
		}
		else
		{
			insere_aresta(grafo, chave1, chave2, pessoas);
		}
	}

	int opcao;
	int ponto;
	do
	{
		Menu();
		printf("Digite a sua opçao: ");
		scanf("%i", &opcao);
		switch (opcao)
		{
		case 1:
			do
			{
				printf("Digite o primeiro ponto\n");
				scanf("%i", &chave1);
				printf("Digite o segundo ponto\n");
				scanf("%i", &chave2);
				printf("Digite a quantidade de pessoas\n");
				scanf("%i", &pessoas);
				insere_aresta(grafo, chave1, chave2, pessoas);
			} while (chave1 < aresta || chave1 < aresta);
			break;

		case 2:

			printf("Digite o ponto que deseja remover: \n ");
			scanf("%i", &ponto);
			remover_vertice(grafo, ponto);
			break;
		case 3:
			break;

		case 4:
			printf("Qual é a rota que deseja eliminar\n");
			printf("Digite a partida:\n");
			scanf("%i", &chave1);
			printf("Digite a chegada:\n");
			scanf("%i", &chave2);

			break;

		case 5:
			termina_grafo(grafo, vertice);
			break;
		case 6:
			imprimirRotasComTotal(grafo);
			break;
		case 7:
			printf("Digite a partida:\n");
			scanf("%i", &chave1);
			printf("Digite a chegada:\n");
			scanf("%i", &chave2);
			dijkstra(grafo, chave1, chave2);
			break;
		case 8:
			circulacaoMinima(grafo);
			break;
		case 9:
			printf("\n");
			imprimirRotas(grafo);
			break;
		}

	} while (opcao != 10);

	return 0;
}

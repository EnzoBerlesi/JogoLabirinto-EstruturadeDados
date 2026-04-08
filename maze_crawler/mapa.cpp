#include "mapa.h"
#include "pilha.h"
#include <cstdio>
#include <cstdlib>

char mapa[LINHAS][COLUNAS] = {
    "##############",
    "#....#........",
    "#.##.#.####...",
    "#.#..#....#...",
    "#.#.###.#.#...",
    "#...#...#.#...",
    "#.###.###.#...",
    "#.#.......#...",
    "#.#.#####.#...",
    "#...#.....#...",
    "#.#.#.###.#...",
    "#.#...#...#...",
    "#.###.#.###...",
    "#.#...#....E..",
    "#.#.#########.",
    "#...#.........",
    "#####.#######.",
    "#.............",
    "#.############",
    "##############"};

bool posicaoValida(int x, int y)
{
    if (x < 0 || x >= COLUNAS)
        return false;
    if (y < 0 || y >= LINHAS)
        return false;
    return mapa[y][x] != '#';
}

bool ehSaida(int x, int y)
{
    return mapa[y][x] == 'E';
}

void marcarRastro(int x, int y)
{
    if (mapa[y][x] == '.' || mapa[y][x] == ' ')
        mapa[y][x] = '*';
}

void apagarRastro(int x, int y)
{
    if (mapa[y][x] == '*')
        mapa[y][x] = '.';
}

void desenharMapa(int playerX, int playerY, int raioVisao,
                  int passos, bool cooldownAtivo, bool podeDesfazer,
                  Pilha *historico, int ultimoDx, int ultimoDy)
{

    system("cls");

    printf("--- MAZE CRAWLER - Disciplina: Estrutura de Dados ---\n");
    printf("[ STATUS DO JOGO ]\n");
    printf("  Jogador (@): (%d, %d)\n", playerX, playerY);
    printf("  Passos Dados: %d\n", passos);
    printf("  Nos na Pilha: %d\n", tamanhoPilha(historico));
    printf("  Pulo [F]: %s\n\n", cooldownAtivo ? "Cooldown..." : "Disponivel!");

    printf("[ LABIRINTO (Matriz %dx%d) ]      ", LINHAS, COLUNAS);
    printf("[ PILHA DE MOVIMENTOS (DINAMICA) ]\n");

    NoPilha *cursor = historico->topo;

    for (int i = 0; i < LINHAS; i++)
    {
        printf("|");
        for (int j = 0; j < COLUNAS - 1; j++)
        {
            int dist = abs(i - playerY) + abs(j - playerX);
            bool visiv = (dist <= raioVisao);

            if (i == playerY && j == playerX)
            {
                printf("@");
            }
            else if (!visiv)
            {
                printf(" ");
            }
            else
            {
                printf("%c", mapa[i][j]);
            }
        }
        printf("|");
        printf("   ");

        if (i == 0)
        {
            printf("TOP (No* topo) ->");
        }
        else if (i == 1)
        {
            if (cursor != nullptr)
                printf("  (%2d,%2d)  <-- Recem empilhado", cursor->x, cursor->y);
            else
                printf("  [pilha vazia]");
        }
        else if (cursor != nullptr)
        {
            cursor = cursor->proximo;
            if (cursor != nullptr)
                printf("  (%2d,%2d)", cursor->x, cursor->y);
        }

        printf("\n");
    }

    printf("\n");
    printf("[ CONTROLES: W/A/S/D Mover | U Desfazer | F Pular parede | Q Sair ]\n");
    printf("  Undo: %s", podeDesfazer ? "[disponivel]" : "[pilha vazia]");
    printf("  |  Ultima direcao gravada: (%d, %d)\n", ultimoDx, ultimoDy);
    printf("> ");
}

void inicializarMapa() {}
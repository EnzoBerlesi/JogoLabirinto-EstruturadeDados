#include "mapa.h"
#include "pilha.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>

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

// Move o cursor pro (0,0) sem apagar a tela
static void moverCursorInicio()
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void desenharMapa(int playerX, int playerY, int raioVisao,
                  int passos, bool cooldownAtivo, bool podeDesfazer,
                  Pilha *historico, int ultimoDx, int ultimoDy)
{

    // Buffer que vai acumular o frame inteiro antes de imprimir
    // 8192 bytes e suficiente para todo o conteudo da tela
    static char buf[8192];
    static bool primeiraVez = true;

    if (primeiraVez)
    {
        system("cls");
        primeiraVez = false;
    }

    // Zera o buffer e começa a montar o frame
    int pos = 0;
    buf[0] = '\0';

// Macro auxiliar: adiciona texto ao buffer via sprintf acumulado
#define W(fmt, ...) pos += sprintf(buf + pos, fmt, ##__VA_ARGS__)

    W("--- MAZE CRAWLER - Disciplina: Estrutura de Dados ---\n");
    W("[ STATUS DO JOGO ]                                   \n");
    W("  Jogador (@): (%d, %d)                              \n", playerX, playerY);
    W("  Passos Dados: %-5d                                 \n", passos);
    W("  Nos na Pilha: %-3d                                 \n", tamanhoPilha(historico));
    W("  Pulo [F]: %-40s\n\n", cooldownAtivo ? "Cooldown..." : "Disponivel!");

    W("[ LABIRINTO (Matriz %dx%d) ]      ", LINHAS, COLUNAS);
    W("[ PILHA DE MOVIMENTOS (DINAMICA) ]\n");

    NoPilha *cursor = historico->topo;

    for (int i = 0; i < LINHAS; i++)
    {

        W("|");
        for (int j = 0; j < COLUNAS - 1; j++)
        {
            int dist = abs(i - playerY) + abs(j - playerX);
            bool visiv = (dist <= raioVisao);

            if (i == playerY && j == playerX)
                W("@");
            else if (!visiv)
                W(" ");
            else
                W("%c", mapa[i][j]);
        }
        W("|   ");

        if (i == 0)
        {
            W("TOP (No* topo) ->              ");
        }
        else if (i == 1)
        {
            if (cursor != nullptr)
                W("  (%2d,%2d)  <-- Recem empilhado", cursor->x, cursor->y);
            else
                W("  [pilha vazia]               ");
        }
        else if (cursor != nullptr)
        {
            cursor = cursor->proximo;
            if (cursor != nullptr)
                W("  (%2d,%2d)                    ", cursor->x, cursor->y);
            else
                W("                              ");
        }
        else
        {
            W("                              ");
        }

        W("\n");
    }

    W("\n");
    W("[ CONTROLES: W/A/S/D Mover | U Desfazer | F Pular parede | Q Sair ]\n");
    W("  Undo: %-15s | Ultima direcao: (%d, %d)          \n",
      podeDesfazer ? "[disponivel]" : "[pilha vazia]",
      ultimoDx, ultimoDy);
    W("> ");

#undef W

    // Imprime o frame inteiro de uma vez so — sem flash
    moverCursorInicio();
    fputs(buf, stdout);
    fflush(stdout);
}

void inicializarMapa() {}
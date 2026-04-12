#include <cstdio>
#include <conio.h>
#include "mapa.h"
#include <windows.h>
#include "jogador.h"

void configurarConsole()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Tamanho da janela (colunas x linhas)
    SMALL_RECT janela = {0, 0, 79, 34};
    SetConsoleWindowInfo(hOut, TRUE, &janela);

    // Buffer do mesmo tamanho da janela — sem scroll
    COORD tamanhoBuffer = {80, 35};
    SetConsoleScreenBufferSize(hOut, tamanhoBuffer);

    // Esconde o cursor
    CONSOLE_CURSOR_INFO cursor = {1, FALSE};
    SetConsoleCursorInfo(hOut, &cursor);
}

int main()
{
    configurarConsole();
    inicializarMapa();

    Jogador *jogador = criarJogador(1, 1);
    const int RAIO_VISAO = 7;
    bool rodando = true;

    while (rodando)
    {
        desenharMapa(
            jogador->x, jogador->y, RAIO_VISAO,
            jogador->passos,
            !podePular(jogador->cooldown),
            !pilhaVazia(jogador->historico),
            jogador->historico,
            jogador->ultimoDx, jogador->ultimoDy);

        if (ehSaida(jogador->x, jogador->y))
        {
            printf("\n*** PARABENS! Voce chegou na saida! ***\n");
            printf("    Passos dados: %d\n\n", jogador->passos);
            break;
        }

        char tecla = getch();

        switch (tecla)
        {
        case 'w':
        case 'W':
            mover(jogador, 0, -1);
            break;
        case 's':
        case 'S':
            mover(jogador, 0, +1);
            break;
        case 'a':
        case 'A':
            mover(jogador, -1, 0);
            break;
        case 'd':
        case 'D':
            mover(jogador, +1, 0);
            break;
        case 'u':
        case 'U':
            desfazer(jogador);
            break;
        case 'f':
        case 'F':
            pularParede(jogador);
            break;
        case 'q':
        case 'Q':
            rodando = false;
            break;
        }
    }

    destruirJogador(jogador);
    return 0;
}
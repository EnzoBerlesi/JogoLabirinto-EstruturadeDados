#include <cstdio>
#include <conio.h>
#include "mapa.h"
#include "jogador.h"

int main()
{
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
            break; // pulo na ultima direcao
        case 'q':
        case 'Q':
            rodando = false;
            break;
        }
    }

    destruirJogador(jogador);
    return 0;
}
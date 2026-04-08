#pragma once
#include "pilha.h"
#include "fila.h"

const int COOLDOWN_PASSOS = 5;

struct Jogador
{
    int x, y;
    int passos;
    int ultimoDx, ultimoDy; // ultima direcao movida (para o pulo com F)
    Pilha *historico;
    Fila *cooldown;
};

Jogador *criarJogador(int xInicial, int yInicial);
void mover(Jogador *j, int dx, int dy);
void desfazer(Jogador *j);
void pularParede(Jogador *j); // usa a ultima direcao automaticamente
void destruirJogador(Jogador *j);
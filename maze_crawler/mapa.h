#pragma once
#include "pilha.h"

const int LINHAS = 20;
const int COLUNAS = 15;

extern char mapa[LINHAS][COLUNAS];

void inicializarMapa();
void desenharMapa(int playerX, int playerY, int raioVisao,
                  int passos, bool cooldownAtivo, bool podeDesfazer,
                  Pilha *historico, int ultimoDx, int ultimoDy);
bool posicaoValida(int x, int y);
bool ehSaida(int x, int y);
void marcarRastro(int x, int y);
void apagarRastro(int x, int y);
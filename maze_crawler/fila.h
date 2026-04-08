#pragma once

// No da fila: guarda um "token" de espera.
// O valor em si nao importa muito — a fila funciona como contador.
struct NoFila
{
    int valor;
    NoFila *proximo;
};

// A fila tem dois ponteiros: inicio (quem sai) e fim (quem entra).
struct Fila
{
    NoFila *inicio; // proximo a sair (FIFO)
    NoFila *fim;    // ultimo que entrou
    int tamanho;
};

Fila *criarFila();
void enfileirar(Fila *f, int valor);
bool desenfileirar(Fila *f);
bool filaVazia(Fila *f);
void ativarCooldown(Fila *f, int passos); // enche com N tokens apos um pulo
void processarPasso(Fila *f);             // remove 1 token a cada passo
bool podePular(Fila *f);                  // true = fila vazia = liberado
void destruirFila(Fila *f);
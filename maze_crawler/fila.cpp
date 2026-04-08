#include "fila.h"
#include <cstddef>

Fila *criarFila()
{
    Fila *f = new Fila();
    f->inicio = nullptr;
    f->fim = nullptr;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int valor)
{
    NoFila *novo = new NoFila();
    novo->valor = valor;
    novo->proximo = nullptr;

    if (f->fim == nullptr)
    {
        f->inicio = novo;
        f->fim = novo;
    }
    else
    {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->tamanho++;
}

bool desenfileirar(Fila *f)
{
    if (filaVazia(f))
        return false;

    NoFila *removido = f->inicio;
    f->inicio = removido->proximo;

    if (f->inicio == nullptr)
        f->fim = nullptr;

    delete removido;
    f->tamanho--;
    return true;
}

bool filaVazia(Fila *f)
{
    return f->inicio == nullptr;
}

void ativarCooldown(Fila *f, int passos)
{
    for (int i = 0; i < passos; i++)
        enfileirar(f, 1);
}

void processarPasso(Fila *f)
{
    desenfileirar(f);
}

bool podePular(Fila *f)
{
    return filaVazia(f);
}

void destruirFila(Fila *f)
{
    while (!filaVazia(f))
        desenfileirar(f);
    delete f;
}
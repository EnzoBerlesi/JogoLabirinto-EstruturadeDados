#include "pilha.h"
#include <cstddef> // para nullptr

// Cria uma pilha vazia e devolve um ponteiro pra ela.
Pilha *criarPilha()
{
    Pilha *p = new Pilha(); // aloca a struct na memoria heap
    p->topo = nullptr;      // ainda nao tem nenhum no
    p->tamanho = 0;
    return p;
}

// Empilha uma coordenada (x, y) no topo.
// new = aloca espaco na memoria. precisa de um delete correspondente!
void empilhar(Pilha *p, int x, int y)
{
    NoPilha *novo = new NoPilha(); // cria o post-it
    novo->x = x;
    novo->y = y;
    novo->proximo = p->topo; // o novo aponta pra quem era o topo
    p->topo = novo;          // agora o novo E o topo
    p->tamanho++;
}

// Remove o topo e coloca as coordenadas em x e y (por referencia).
// Retorna false se a pilha estiver vazia.
bool desempilhar(Pilha *p, int &x, int &y)
{
    if (pilhaVazia(p))
        return false;

    NoPilha *removido = p->topo; // guarda o no que vai sair
    x = removido->x;             // copia as coords pra fora
    y = removido->y;
    p->topo = removido->proximo; // topo agora e o proximo
    delete removido;             // LIBERA a memoria! sem isso = memory leak
    p->tamanho--;
    return true;
}

bool pilhaVazia(Pilha *p)
{
    return p->topo == nullptr;
}

int tamanhoPilha(Pilha *p)
{
    return p->tamanho;
}

// Destroi a pilha inteira: esvazia tudo e libera a struct.
void destruirPilha(Pilha *p)
{
    int x, y;
    while (!pilhaVazia(p))
        desempilhar(p, x, y); // cada pop ja faz o delete do no
    delete p;                 // libera a struct Pilha em si
}
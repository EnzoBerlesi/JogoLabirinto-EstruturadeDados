#pragma once

// Um "no" (node) e a menor unidade da pilha.
// Pensa nele como um post-it que guarda uma coordenada.
struct NoPilha
{
    int x, y;         // coordenadas salvas
    NoPilha *proximo; // aponta pro post-it abaixo dele na pilha
};

// A pilha em si: so precisa saber onde e o topo.
struct Pilha
{
    NoPilha *topo; // ponteiro pro no do topo (null se vazia)
    int tamanho;   // quantos nos existem agora
};

Pilha *criarPilha();
void empilhar(Pilha *p, int x, int y);
bool desempilhar(Pilha *p, int &x, int &y); // & = devolve as coords pra fora
bool pilhaVazia(Pilha *p);
int tamanhoPilha(Pilha *p);
void destruirPilha(Pilha *p);
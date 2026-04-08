#include "jogador.h"
#include "mapa.h"

Jogador *criarJogador(int xInicial, int yInicial)
{
    Jogador *j = new Jogador();
    j->x = xInicial;
    j->y = yInicial;
    j->passos = 0;
    j->ultimoDx = 0;
    j->ultimoDy = 0;
    j->historico = criarPilha();
    j->cooldown = criarFila();
    return j;
}

void mover(Jogador *j, int dx, int dy)
{
    int novoX = j->x + dx;
    int novoY = j->y + dy;

    if (!posicaoValida(novoX, novoY))
        return;

    empilhar(j->historico, j->x, j->y);
    marcarRastro(j->x, j->y);

    j->x = novoX;
    j->y = novoY;
    j->ultimoDx = dx;
    j->ultimoDy = dy;
    j->passos++;

    processarPasso(j->cooldown);
}

void desfazer(Jogador *j)
{
    if (pilhaVazia(j->historico))
        return;

    int anteriorX, anteriorY;
    desempilhar(j->historico, anteriorX, anteriorY);
    apagarRastro(anteriorX, anteriorY);

    j->x = anteriorX;
    j->y = anteriorY;
}

// Pulo de parede com F: usa automaticamente a ultima direcao movida.
// Condicoes: celula imediata deve ser parede + celula alem deve ser livre.
void pularParede(Jogador *j)
{
    if (!podePular(j->cooldown))
        return;
    if (j->ultimoDx == 0 && j->ultimoDy == 0)
        return; // sem direcao ainda

    int dx = j->ultimoDx;
    int dy = j->ultimoDy;

    int paredeX = j->x + dx;
    int paredeY = j->y + dy;
    int alemX = j->x + dx * 2;
    int alemY = j->y + dy * 2;

    bool imediataEhParede = (paredeX >= 0 && paredeX < COLUNAS &&
                             paredeY >= 0 && paredeY < LINHAS &&
                             !posicaoValida(paredeX, paredeY));
    bool alemEhLivre = posicaoValida(alemX, alemY);

    if (!imediataEhParede || !alemEhLivre)
        return;

    empilhar(j->historico, j->x, j->y);
    marcarRastro(j->x, j->y);

    j->x = alemX;
    j->y = alemY;
    j->passos++;

    ativarCooldown(j->cooldown, COOLDOWN_PASSOS);
}

void destruirJogador(Jogador *j)
{
    destruirPilha(j->historico);
    destruirFila(j->cooldown);
    delete j;
}
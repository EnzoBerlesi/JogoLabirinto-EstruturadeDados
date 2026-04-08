# Maze Crawler
**Disciplina:** Análise de Dados — Estrutura de Dados  
**Instituição:** Centro Universitário Autônomo do Brasil — UniBrasil  
**Professor(a):** Sâmela S. Sartin

---

## Integrantes
- ___________________________________
- ___________________________________
- ___________________________________
- ___________________________________
- ___________________________________

---

## Objetivo do Jogo

Maze Crawler é um jogo de labirinto em terminal (ASCII) onde o jogador controla um explorador (`@`) que deve encontrar a saída (`E`) de uma caverna representada por uma matriz `char[20][15]`.

À medida que o jogador se move, ele deixa um rastro (`*`) e sua posição anterior é salva em uma **Pilha Dinâmica (LIFO)**. Isso permite a função de **Desfazer (Backtracking)**, que retorna o jogador à posição anterior removendo o topo da pilha.

O diferencial visual é o **campo de visão**: o jogador só enxerga as células próximas a ele (raio de 7 casas via distância Manhattan), simulando a exploração real de uma caverna escura.

---

## Como Compilar e Executar

### Pré-requisitos
- Compilador g++ com suporte a C++11 (MinGW no Windows)
- Terminal Windows (CMD, PowerShell ou terminal integrado do VS Code)

### Compilar
Abra o terminal na pasta do projeto e execute:

```bash
g++ -o MazeCrawler main.cpp pilha.cpp fila.cpp mapa.cpp jogador.cpp
```

### Executar
```bash
.\MazeCrawler.exe
```

---

## Controles

| Tecla | Ação |
|-------|------|
| `W` | Mover para cima |
| `S` | Mover para baixo |
| `A` | Mover para esquerda |
| `D` | Mover para direita |
| `U` | Desfazer último movimento (Backtracking) |
| `F` | Pular parede na última direção movida (função extra) |
| `Q` | Sair do jogo |

---

## Estrutura de Arquivos

```
maze_crawler/
├── main.cpp        ← Game loop principal
├── pilha.h/.cpp    ← Pilha Dinâmica (LIFO) — coração do projeto
├── fila.h/.cpp     ← Fila Dinâmica (FIFO) — cooldown do pulo
├── mapa.h/.cpp     ← Labirinto, renderização e visibilidade
├── jogador.h/.cpp  ← Movimento, backtracking e pulo de parede
└── README.md
```

---

## Estruturas de Dados Implementadas

### Pilha Dinâmica (LIFO)
Cada vez que o jogador se move, a posição anterior é salva em um nó alocado dinamicamente com `new`. A pilha cresce para cima: o último movimento é sempre o primeiro a ser desfeito.

```
Topo → Nó(x=3, y=5) → Nó(x=3, y=4) → Nó(x=2, y=4) → null
```

No `pop()`, o nó é removido do topo e sua memória é liberada com `delete`, evitando vazamento de memória (memory leak).

**Funções:**
- `criarPilha()` — inicializa a pilha vazia
- `empilhar(p, x, y)` — cria um nó e coloca no topo
- `desempilhar(p, x, y)` — remove o topo e libera memória
- `pilhaVazia(p)` — verifica se há elementos
- `destruirPilha(p)` — libera todos os nós e a struct

### Fila Dinâmica (FIFO)
Usada como mecanismo de cooldown para a função extra de pulo de parede. Ao pular, a fila é preenchida com tokens. A cada passo dado, um token é removido do início. Enquanto a fila não estiver vazia, o pulo está bloqueado.

```
Entra pelo fim →  [token][token][token][token][token]  → Sai pelo início
                   (após pular)       (um por passo)
```

**Funções:**
- `criarFila()` — inicializa a fila vazia
- `enfileirar(f, valor)` — insere no fim
- `desenfileirar(f)` — remove do início e libera memória
- `ativarCooldown(f, passos)` — enche a fila com N tokens
- `processarPasso(f)` — remove 1 token a cada movimento
- `podePular(f)` — retorna true se a fila estiver vazia

---

## Função Extra — Pulo de Parede com Cooldown

### Finalidade
Permite que o jogador atravesse **uma parede** na direção em que estava se movendo, abrindo novos caminhos no labirinto e tornando a exploração mais dinâmica. Para evitar uso abusivo, a habilidade entra em **cooldown de 5 passos** após ser usada.

### Como usar
1. Mova-se em alguma direção com `W/A/S/D`
2. Pressione `F` para pular a parede à sua frente (na mesma direção)
3. O status `[Cooldown...]` ou `[Disponivel!]` aparece na HUD

### Lógica de Desenvolvimento
A função `pularParede()` em `jogador.cpp` funciona assim:

1. Verifica se o cooldown está disponível (`filaVazia`)
2. Lê a última direção movida (`ultimoDx`, `ultimoDy`)
3. Calcula a célula imediata (`posição + direção`) — deve ser `#` (parede)
4. Calcula a célula além da parede (`posição + direção * 2`) — deve ser livre
5. Se ambas as condições forem verdadeiras, move o jogador para além da parede
6. Empilha a posição anterior (permite desfazer o pulo com `U`)
7. Chama `ativarCooldown()` para preencher a fila com 5 tokens de espera

A integração entre **Pilha** (para o undo do pulo) e **Fila** (para o cooldown) é o que torna esta função tecnicamente completa como demonstração das duas estruturas de dados no mesmo mecanismo.

---

## Campo de Visão (Visibilidade)

O jogador não enxerga o labirinto inteiro — apenas as células dentro de um **raio de 7 casas**, calculado por distância Manhattan:

```
distância = |linha_jogador - linha_célula| + |coluna_jogador - coluna_célula|
```

Células fora do raio aparecem como espaço em branco no terminal, criando o efeito de "caverna escura". Isso foi implementado na função `desenharMapa()` em `mapa.cpp`.

---

## Interface ASCII

A tela exibe duas colunas lado a lado, como especificado no enunciado:

```
[ LABIRINTO (Matriz 20x15) ]      [ PILHA DE MOVIMENTOS (DINAMICA) ]
|##############|                  TOP (No* topo) ->
|# @  #        |                    ( 3,  5)  <-- Recem empilhado
|#.## #.####   |                    ( 3,  4)
...                                 ( 2,  4)
```

---

## Gestão de Memória

Cada `new` tem um `delete` correspondente:

| Alocação | Liberação |
|----------|-----------|
| `empilhar()` → `new NoPilha` | `desempilhar()` → `delete removido` |
| `enfileirar()` → `new NoFila` | `desenfileirar()` → `delete removido` |
| `criarPilha()` → `new Pilha` | `destruirPilha()` → `delete p` |
| `criarFila()` → `new Fila` | `destruirFila()` → `delete f` |
| `criarJogador()` → `new Jogador` | `destruirJogador()` → `delete j` |

---

## Dificuldades Encontradas

> *(Preencher com as dificuldades reais do grupo durante a implementação)*

- ...
- ...
- ...

---

## Critérios de Avaliação

| Critério | Peso |
|----------|------|
| Lógica de Gerenciamento (LIFO/FIFO correto) | 30% |
| Função Extra (relevância e criatividade) | 25% |
| Defesa Técnica (explicar ponteiros e nós) | 20% |
| Modularização e boas práticas | 15% |
| Interface de Usuário | 10% |
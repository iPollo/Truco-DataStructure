#ifndef _BARALHO_ENC_H_
#define _BARALHO_ENC_H_

typedef struct Nodo{
   Carta info;
   struct Nodo *prox;
   struct Nodo *ant;
} Nodo;

typedef struct Baralho{
   Nodo *topo;
} Baralho;

// Funcao que cria um baralho
Baralho* criarBaralho();

void baralhoInserirCarta(Baralho* baralho, Carta novaCarta);
Carta baralhoRemoverCarta(Baralho* baralho);
void baralhoImprimir(Baralho* baralho);
int baralhoTamanho(Baralho* baralho);
void baralhoEmbaralhar(Baralho* baralho, int tamanho);
Carta baralhoEscolherCartaID(Baralho* baralho, int id);
void baralhoLimpar(Baralho* baralho);
void baralhoGerarBaralhoTruco(Baralho* baralho);


//// Funcao que destroi uma pilha
//void destroiPilhaEnc(PilhaEnc *pilha);
//

//// Funcao que determina se uma pilha eh vazia
//int vaziaPilhaEnc(PilhaEnc* pilha);

#endif

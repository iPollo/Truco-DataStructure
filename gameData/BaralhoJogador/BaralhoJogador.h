#ifndef _LISTA_ENC_DUPLA_H_
#define _LISTA_ENC_DUPLA_H_

#define BARALHO_JOGADOR_TAMANHO_MAX 3

typedef struct{
   Nodo *prim;
} BaralhoJogador;

BaralhoJogador* criarBaralhoJogador();
void baralhoJogadorInserirCartaInicio(BaralhoJogador* baralho, Carta carta);
void baralhoJogadorRemoverCarta(BaralhoJogador* baralho, Carta carta);
void baralhoJogadorImprimir(BaralhoJogador* baralho);
int baralhoJogadorTamanho(BaralhoJogador* baralho);
void baralhoJogadorLimpar(BaralhoJogador* baralho);

#endif

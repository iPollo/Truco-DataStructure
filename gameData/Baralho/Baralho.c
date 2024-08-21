#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma pilha com primeiro nodo vazio
Baralho* criarBaralho(){
   Baralho *novoBaralho = (Baralho*)malloc(sizeof(Baralho));
   if (novoBaralho != NULL)
      novoBaralho->topo = NULL;

   return novoBaralho;
}

// Insere uma nova carta no topo do baralho
void baralhoInserirCarta(Baralho *baralho, Carta novaCarta){
   Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
   if (novo != NULL){
      novo->info = novaCarta;
      novo->prox = baralho->topo;
      baralho->topo = novo;
   }

   //cartaImprimir(novaCarta);
}

// Remove uma carta do topo do baralho
Carta baralhoRemoverCarta(Baralho* baralho){
   
   Nodo *aux = baralho->topo;   
   Carta cartaRemovida = aux->info;
   //if(cartaRemovida.naipe < 0 || cartaRemovida.naipe > 4) TraceLog(LOG_FATAL, "CARTA NÃO VÁLIDA!!!!!");
   baralho->topo = aux->prox;
   free(aux);

   return cartaRemovida;
}

void baralhoImprimir(Baralho* baralho){

   Nodo* aux = baralho->topo;

   while(aux != NULL){
   
      cartaImprimir(aux->info);
      aux = aux->prox;

   }
}

void baralhoLimpar(Baralho* baralho){
   Nodo *aux = baralho->topo;
   while(aux != NULL){
      Nodo *tmp = aux->prox;
      free(aux); // Cuidar ordem do free
      aux = tmp;
   }

   baralho->topo = NULL;
}

void baralhoGerarTruco(Baralho* baralho){
   for(int i = 0; i < 10; i++){
		for(int j = 0; j < 4; j++){
			baralhoInserirCarta(baralho, (Carta){j, i});
		}
	}
	baralhoEmbaralhar(baralho, baralhoTamanho(baralho));
}

int baralhoTamanho(Baralho* baralho){
   int counter = 0;
   Nodo* aux = baralho->topo;
   while(aux != NULL){
      aux = aux->prox;
      counter++;
   }
   return counter;
}

void baralhoEmbaralhar(Baralho* baralho, int tamanho){

   Carta cartas[tamanho];

   for(int i = 0; i < tamanho; i++){
      cartas[i] = baralhoRemoverCarta(baralho);
   }

   for(int i = 0; i < tamanho; i++){
      int novaPos = GetRandomValue(0, tamanho);
      Carta cartaAntiga = cartas[novaPos];
      cartas[novaPos] = cartas[i];
      cartas[i] = cartaAntiga;
   }

   for(int i = 0; i < tamanho; i++){
      baralhoInserirCarta(baralho, cartas[i]);
   }
}

Carta baralhoEscolherCartaID(Baralho* baralho, int id){
   int tamanho = baralhoTamanho(baralho);
   int counter = 0;
   Nodo* aux = baralho->topo;
   while(counter != id){
      aux = aux->prox;
      counter++;
   }
   return aux->info;
}


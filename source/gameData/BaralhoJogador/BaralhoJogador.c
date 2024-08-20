
BaralhoJogador* criarBaralhoJogador(){
   BaralhoJogador *baralho = (BaralhoJogador*)malloc(sizeof(BaralhoJogador));
   baralho->prim = NULL;
   return baralho;
}

void baralhoJogadorInserirCartaInicio(BaralhoJogador* baralho, Carta carta){
   Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
   novo->info = carta;
   novo->ant = NULL;
   novo->prox = baralho->prim;
   if (baralho->prim != NULL)
      baralho->prim->ant = novo;
   baralho->prim = novo;
}

void baralhoJogadorRemoverCarta(BaralhoJogador* baralho, Carta carta){

   Nodo *aux = baralho->prim;

   if(baralho->prim == NULL) return;

   for(aux = baralho->prim; aux != NULL; aux = aux->prox)
   {
      if((aux->info.naipe == carta.naipe && aux->info.valor == carta.valor)){
         // TraceLog(LOG_INFO, "TENTATIVA DE REMOVER PRIMEIRA CARTA!");
         // TraceLog(LOG_INFO, "   ");
         cartaImprimir(carta);

         // Caso tenha apenas um elemento no baralho
         if(aux->prox == NULL && aux == baralho->prim){
            baralho->prim = NULL;
            free(aux);
            return;
         }

         // Caso seja o elemento central
         else if(aux->ant != NULL && aux->prox != NULL){

            (aux->ant)->prox = aux->prox;
            (aux->prox)->ant = aux->ant;
            baralho->prim = aux->ant;
            baralho->prim->ant = NULL;
            free(aux);
            return;
         }

         // Caso seja o último elemento
         else if(aux->prox == NULL && aux->ant != NULL){
            (aux->ant)->prox = NULL;
            free(aux);
            return;
         }

         // Caso seja o primeiro elemento
         else if(aux->prox != NULL && aux->ant == NULL){
            (aux->prox)->ant = NULL;
            baralho->prim = aux->prox;
            free(aux);
            return;
         }
         
      }
   }
}

void baralhoJogadorLimpar(BaralhoJogador* baralho){
   Nodo *aux = baralho->prim;
   while(aux != NULL){
      Nodo *tmp = aux->prox;
      free(aux); // Cuidar ordem do free
      aux = tmp;
   }
}

void baralhoJogadorImprimir(BaralhoJogador* baralho){
   Nodo *aux;
   for(aux = baralho->prim; aux != NULL; aux = aux->prox)
   {
      cartaImprimir(aux->info);
   }
}

int baralhoJogadorTamanho(BaralhoJogador* baralho){
   Nodo *aux;
   int counter = 0;
   for(aux = baralho->prim; aux != NULL; aux = aux->prox)
      counter++;

   return counter;
}

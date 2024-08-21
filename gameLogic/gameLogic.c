// Retorna uma carta aleatório no baralho atual

// Escolhe a manilha (primeira carta virada após distribuição)
Carta logicEscolherManilha(Baralho* baralho){
    Carta aux = baralhoRemoverCarta(baralho);
    return aux;
}

// Inicializa os dados dos jogadores
void logicInicializarJogadores(Jogador jogador[4]){

    strcpy(jogador[0].nome, "Você");
    jogador[0].prox = &jogador[1];
    jogador[0].pontos = 0;
    jogador[0].id = 0;
    jogador[0].baralhoJogador = criarBaralhoJogador();
    
    strcpy(jogador[1].nome, "Amanda");
    jogador[1].prox = &jogador[2];
    jogador[1].pontos = 0;
    jogador[1].id = 1;
    jogador[1].baralhoJogador = criarBaralhoJogador();
    
    strcpy(jogador[2].nome, "Prof. Dr. Thiago");
    jogador[2].prox = &jogador[3];
    jogador[2].pontos = 0;
    jogador[2].id = 2;
    jogador[2].baralhoJogador = criarBaralhoJogador();

    strcpy(jogador[3].nome, "Rebeca");
    jogador[3].prox = &jogador[0];
    jogador[3].pontos = 0;
    jogador[3].id = 3;
    jogador[3].baralhoJogador = criarBaralhoJogador();

}

// Distribui as cartas do baralho
void logicDistribuirCartas(Baralho* baralho, Jogador jogador[4]){

    TraceLog(LOG_INFO, "---- CARTAS DISTRIBUIDAS ----");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            Carta cartaRemovida = baralhoRemoverCarta(baralho);
            //TraceLog(LOG_WARNING, "CARTA REMOVIDA: %d", cartaRemovida.naipe);
            while(cartaRemovida.naipe < 0 || cartaRemovida.naipe > 4) cartaRemovida = baralhoRemoverCarta(baralho);
            baralhoJogadorInserirCartaInicio(jogador[i].baralhoJogador, cartaRemovida);
        }

    }

    PlaySound(gameSound[SFX_CARDAWAY]);

}

// Joga uma carta na mesa
void logicJogarCarta(Jogador* jogador, Carta carta, Baralho* cartasJogadas, ListaCircular* lista, int index, Carta textureInfo[4]){

    carta.jogadorQueJogou = jogador->id;    
    baralhoJogadorRemoverCarta(jogador->baralhoJogador, carta);
    baralhoInserirCarta(cartasJogadas, carta);
    textureInfo[index] = carta;
    lista->prim = jogador->prox;
    PlaySound(gameSound[SFX_CARD]);
}

// Verifica o ganhador com base ans cartas jogadas na mesa
Jogador logicVerificarGanhador(Jogador jogador[4], Baralho* cartasJogadas){

    Carta cartaRemovida;
    Carta cartaMaisAlta = {NAIPE_OURO, VALOR_4};
    Nodo *aux = cartasJogadas->topo;
    int idJogadorCartaMaisAlta = 0;

    while(aux != NULL){
        cartaRemovida = aux->info;
        //cartaImprimir(cartaRemovida);


        if(cartaRemovida.valor > cartaMaisAlta.valor){

            if(cartaRemovida.valor == cartaMaisAlta.valor && cartaRemovida.naipe > cartaMaisAlta.naipe){
                idJogadorCartaMaisAlta = cartaRemovida.jogadorQueJogou;
                cartaMaisAlta = cartaRemovida;
            }
            else{
                idJogadorCartaMaisAlta = cartaRemovida.jogadorQueJogou;
                cartaMaisAlta = cartaRemovida;
            }
        }

        aux = aux->prox;
    }

    TraceLog(LOG_WARNING, "ID JOGADOR GANHADOR: %d", idJogadorCartaMaisAlta);
    TraceLog(LOG_WARNING, "CARTA MAIS ALTA");
    cartaImprimir(cartaMaisAlta);

    for(int i = 0; i < 4; i++){
        if(jogador[i].id == idJogadorCartaMaisAlta){
            jogador[i].pontos += valorPontoRodada;
            return jogador[i];
        }
    }
}

// Verifica o ganhador/perdedor final (após atingir a pontuação máxima)
bool logicVerificarGanhadores(Jogador jogadores[4]){

    if(!isGameRunning) return false;

    if((jogadores[0].pontos + jogadores[2].pontos) >= MAX_POINTS_TO_WIN){
        isGameOver = true;
        isOnFinalScreen = true;
        return true;
    }
    else if((jogadores[1].pontos + jogadores[3].pontos) >= MAX_POINTS_TO_WIN){
        isGameOver = true;
        isOnFinalScreen = true;
        return true;
    }

    isGameOver = false;
    return false;

}

// Imprime informações no LOG (usado apenas para debug)
void logicImprimirTodasInformacoes(Jogador jogador[4], Baralho* baralho, Jogador roundJogador, Carta manilha, Baralho* cartasJogadas, int rodada){

    TraceLog(LOG_WARNING, "===================== GAME INFO (RODADA: %d) =====================", rodada);
    for(int i = 0; i < 4; i++){
        TraceLog(LOG_WARNING, "Jogador: %s PONTOS: %d", jogador[i].nome, jogador[i].pontos);
        baralhoJogadorImprimir(jogador[i].baralhoJogador);
        TraceLog(LOG_WARNING, "            ");
    }

    TraceLog(LOG_WARNING, " ------------------>> TAMANHO BARALHO:");
    TraceLog(LOG_WARNING, "%d", baralhoTamanho(baralho));
    TraceLog(LOG_WARNING, "            ");

    TraceLog(LOG_WARNING, " ------------------>> MANILHA");
    cartaImprimir(manilha);
    TraceLog(LOG_WARNING, "            ");

    TraceLog(LOG_WARNING, " ------------------>> VEZ DE");
    TraceLog(LOG_WARNING, "%s", roundJogador.nome);
    TraceLog(LOG_WARNING, "            ");
    


    TraceLog(LOG_WARNING, " ------------------>> CARTAS JOGADAS");
    baralhoImprimir(cartasJogadas);

    TraceLog(LOG_WARNING, "===================== GAME INFO =====================");
    TraceLog(LOG_WARNING, "            ");
    TraceLog(LOG_WARNING, "            ");
}















// Define o número máximo de textras do jogo
#define MAX_ASSETS 32

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Enum responsável por controlar as texturas do jogo
enum{
	ASSET_BACKGROUND,
    ASSET_BACKGROUND_WINNERS,
    ASSET_DECK_1_CARDS,
    ASSET_DECK_2_CARDS,
    ASSET_DECK_3_CARDS,
    ASSET_CARTA_BRANCA,
    ASSET_CARTA_2,
    ASSET_CARTA_3,
    ASSET_CARTA_4,
    ASSET_CARTA_5,
    ASSET_CARTA_6,
    ASSET_CARTA_7,
    ASSET_CARTA_Q,
    ASSET_CARTA_J,
    ASSET_CARTA_K,
    ASSET_CARTA_A,
    ASSET_CARTA_OURO,
    ASSET_CARTA_COPAS,
    ASSET_CARTA_PAUS,
    ASSET_CARTA_ESPADA,
    ASSET_TRUCOTELA,
    ASSET_TRUCOTELA_SOLO,
    TRUCO_MAINMENU_SCOREBOARD,
    TRUCO_MAINMENU_CARREGAR,
    TRUCO_MAINMENU_INICIAR,
    TRUCO_MAINMENU_SAIR,
};

// Inicializa as texturas do jogo usando um Texture2D (Struct do próprio Raylib)
Texture2D assets[MAX_ASSETS];


// Enums para controlar as opções do menu (botões selecionados)
enum{
	OPTION_START,
	OPTION_LOAD,
	OPTION_SCOREBOARD,
	OPTION_SAIR,
};

enum{
	MENU_MAIN,
	MENU_SCOREBOARD,
};

// Dados de controle do menu e dos botões 
int menuCurrentSelectedOption = OPTION_START;
int menuCurrentMenu = MENU_MAIN;

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa e carrega todas as textura (sprites)
void InicializarAssets(){
	assets[ASSET_BACKGROUND] = LoadTexture(TextFormat("%s/gameAssets/ASSET_BACKGROUND.png", GetWorkingDirectory()));
    assets[ASSET_DECK_1_CARDS] = LoadTexture(TextFormat("%s/gameAssets/ASSET_DECK_1_CARDS.png", GetWorkingDirectory()));
    assets[ASSET_DECK_2_CARDS] = LoadTexture(TextFormat("%s/gameAssets/ASSET_DECK_2_CARDS.png", GetWorkingDirectory()));
    assets[ASSET_DECK_3_CARDS] = LoadTexture(TextFormat("%s/gameAssets/ASSET_DECK_3_CARDS.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_BRANCA] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_BRANCA.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_2] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_2.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_3] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_3.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_4] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_4.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_5] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_5.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_6] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_6.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_7] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_7.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_Q] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_Q.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_J] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_J.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_K] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_K.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_A] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_A.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_OURO] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_OURO.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_COPAS] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_COPAS.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_PAUS] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_PAUS.png", GetWorkingDirectory()));
    assets[ASSET_CARTA_ESPADA] = LoadTexture(TextFormat("%s/gameAssets/ASSET_CARTA_ESPADA.png", GetWorkingDirectory()));
    assets[ASSET_TRUCOTELA] = LoadTexture(TextFormat("%s/gameAssets/ASSET_TRUCOTELA.png", GetWorkingDirectory()));
    assets[ASSET_TRUCOTELA_SOLO] = LoadTexture(TextFormat("%s/gameAssets/ASSET_TRUCOTELA_SOLO.png", GetWorkingDirectory()));
    assets[ASSET_BACKGROUND_WINNERS] = LoadTexture(TextFormat("%s/gameAssets/ASSET_BACKGROUND_WINNERS.png", GetWorkingDirectory()));

    assets[TRUCO_MAINMENU_SCOREBOARD] = LoadTexture(TextFormat("%s/gameAssets/TRUCO_MAINMENU_SCOREBOARD.png", GetWorkingDirectory()));
    assets[TRUCO_MAINMENU_CARREGAR] = LoadTexture(TextFormat("%s/gameAssets/TRUCO_MAINMENU_CARREGAR.png", GetWorkingDirectory()));
    assets[TRUCO_MAINMENU_INICIAR] = LoadTexture(TextFormat("%s/gameAssets/TRUCO_MAINMENU_INICIAR.png", GetWorkingDirectory()));
    assets[TRUCO_MAINMENU_SAIR] = LoadTexture(TextFormat("%s/gameAssets/TRUCO_MAINMENU_SAIR.png", GetWorkingDirectory()));



}

void DesenharTelaDeFundo(){
	DrawTexture(assets[ASSET_BACKGROUND], 0, 0, WHITE);
}

void DesenharCartas(Jogador jogadores[4]){
    
    switch(baralhoJogadorTamanho(jogadores[2].baralhoJogador)){
        case 0: break;
        case 1: DrawTextureEx(assets[ASSET_DECK_1_CARDS], (Vector2){250, 180}, 0, 0.4, WHITE); break;
        case 2: DrawTextureEx(assets[ASSET_DECK_2_CARDS], (Vector2){250, 180}, 0, 0.4, WHITE); break;
        case 3: DrawTextureEx(assets[ASSET_DECK_3_CARDS], (Vector2){250, 180}, 0, 0.4, WHITE); break;
    }

    switch(baralhoJogadorTamanho(jogadores[3].baralhoJogador)){
        case 0: break;
        case 1: DrawTextureEx(assets[ASSET_DECK_1_CARDS], (Vector2){250, 495}, 0, 0.4, WHITE); break;
        case 2: DrawTextureEx(assets[ASSET_DECK_2_CARDS], (Vector2){250, 495}, 0, 0.4, WHITE); break;
        case 3: DrawTextureEx(assets[ASSET_DECK_3_CARDS], (Vector2){250, 495}, 0, 0.4, WHITE); break;
    }

    switch(baralhoJogadorTamanho(jogadores[1].baralhoJogador)){
        case 0: break;
        case 1: DrawTextureEx(assets[ASSET_DECK_1_CARDS], (Vector2){750, 180}, 0, 0.4, WHITE); break;
        case 2: DrawTextureEx(assets[ASSET_DECK_2_CARDS], (Vector2){750, 180}, 0, 0.4, WHITE); break;
        case 3: DrawTextureEx(assets[ASSET_DECK_3_CARDS], (Vector2){750, 180}, 0, 0.4, WHITE); break;
    }
}

void DesenharCartaUnica(int naipe, int valor, Vector2 pos, float scale, Color color){

    Texture2D txtNaipe = assets[ASSET_CARTA_COPAS];
    Texture2D txtValor = assets[ASSET_CARTA_2];
    Color valorColor = BLACK;

    switch(naipe){
        case 0: txtNaipe = assets[ASSET_CARTA_OURO]; valorColor = RED; break;
        case 1: txtNaipe = assets[ASSET_CARTA_ESPADA]; break;
        case 2: txtNaipe = assets[ASSET_CARTA_COPAS]; valorColor = RED; break;
        case 3: txtNaipe = assets[ASSET_CARTA_PAUS]; break;
    }

    switch(valor){
        case 0: txtValor = assets[ASSET_CARTA_4]; break;
        case 1: txtValor = assets[ASSET_CARTA_5]; break;
        case 2: txtValor = assets[ASSET_CARTA_6]; break;
        case 3: txtValor = assets[ASSET_CARTA_7]; break;
        case 4: txtValor = assets[ASSET_CARTA_Q]; break;
        case 5: txtValor = assets[ASSET_CARTA_J]; break;
        case 6: txtValor = assets[ASSET_CARTA_K]; break;
        case 7: txtValor = assets[ASSET_CARTA_A]; break;
        case 8: txtValor = assets[ASSET_CARTA_2]; break;
        case 9: txtValor = assets[ASSET_CARTA_3]; break;
    }


    DrawTextureEx(assets[ASSET_CARTA_BRANCA], pos, 0, scale, color);
    DrawTextureEx(txtNaipe, pos, 0, scale, WHITE);
    DrawTextureEx(txtValor, pos, 0, scale, valorColor);

}

void DesenharCartasJogadas(Baralho* cartasJogadas, Carta textureInfoCartasJogadas[4]){

    Color cardColor = WHITE;
    int size = baralhoTamanho(cartasJogadas);
    if(size == 0) return;

    if(textureInfoCartasJogadas[0].jogadorQueJogou == 1 || textureInfoCartasJogadas[0].jogadorQueJogou == 3) cardColor = (Color){255, 244, 128, 255}; else cardColor = WHITE;
    DesenharCartaUnica(textureInfoCartasJogadas[0].naipe, textureInfoCartasJogadas[0].valor, (Vector2){431-2, 348}, 1, cardColor);
    
    if(size == 1) return;

    if(textureInfoCartasJogadas[1].jogadorQueJogou == 1 || textureInfoCartasJogadas[1].jogadorQueJogou == 3) cardColor = (Color){255, 244, 128, 255}; else cardColor = WHITE;
    DesenharCartaUnica(textureInfoCartasJogadas[1].naipe, textureInfoCartasJogadas[1].valor, (Vector2){518-2, 348}, 1, cardColor);
    
    if(size == 2) return;
    
    if(textureInfoCartasJogadas[2].jogadorQueJogou == 1 || textureInfoCartasJogadas[2].jogadorQueJogou == 3) cardColor = (Color){255, 244, 128, 255}; else cardColor = WHITE;
    DesenharCartaUnica(textureInfoCartasJogadas[2].naipe, textureInfoCartasJogadas[2].valor, (Vector2){607-4, 348}, 1, cardColor);
    
    if(size == 3) return;
    
    if(textureInfoCartasJogadas[3].jogadorQueJogou == 1 || textureInfoCartasJogadas[3].jogadorQueJogou == 3) cardColor = (Color){255, 244, 128, 255}; else cardColor = WHITE;
    DesenharCartaUnica(textureInfoCartasJogadas[3].naipe, textureInfoCartasJogadas[3].valor, (Vector2){695-2, 348}, 1, cardColor);
}

void DesenharCartasJogador(int max, Jogador jogador){
        int xOffset = 0;
        if(max == 3) xOffset = 0;
        else if(max == 2) xOffset = 50;
        else if(max == 1) xOffset = 100;

        Carta cartas = {};
    
    for(int i = 0; i < max; i++){
        int yOffset = 0;
        if(i%2 == 0) yOffset = +10;

        if(i == 0) cartas = jogador.baralhoJogador->prim->info;
        if(i == 1) cartas = jogador.baralhoJogador->prim->prox->info;
        if(i == 2) cartas = jogador.baralhoJogador->prim->prox->prox->info;

        DesenharCartaUnica(cartas.naipe, cartas.valor, (Vector2){xOffset + 755 + 50 * i, 490+yOffset}, 1, WHITE);
        DrawText(TextFormat("%d. ", i+1), xOffset + 765 + 50 * i, 585+yOffset, 15, DARKGREEN); 
    }
}

void DesenharPontuacao(Jogador jogadores[4]){
    
    DrawText(TextFormat("%d PTS.", jogadores[0].pontos), 845, 646, 20, (Color){143, 27, 27, 255}); 
    DrawText(TextFormat("%d PTS.", jogadores[1].pontos), 845, 148, 20, (Color){143, 27, 27, 255}); 
    DrawText(TextFormat("%d PTS.", jogadores[3].pontos), 280, 646, 20, (Color){143, 27, 27, 255}); 
    DrawText(TextFormat("%d PTS.", jogadores[2].pontos), 280, 148, 20, (Color){143, 27, 27, 255}); 

}

void DesenharTemporizador(){

    //if(!isOnTrucoScreen) return;

    DrawRectangle(222, 600, 777, 5, (Color){54, 54,54, 255});
    DrawRectangle(222, 600, 300, 5, (Color){255, 0,0, 200});

}

void DesenharVez(Jogador jogadorAtual, Jogador vencedor){

    if(isOnWinnerScreen) return;

    int textSize = MeasureText("Sua Vez!", 15);
    if(jogadorAtual.id == 0){
        DrawText("Sua Vez!", 597 - textSize/2, 320, 15, WHITE); 
        return;
    }

    textSize = MeasureText(TextFormat("Vez de: %s", jogadorAtual.nome), 15);   
    DrawText(TextFormat("Vez de: %s", jogadorAtual.nome), 597 - textSize/2, 320, 15, WHITE); 
}

void DesenharTelaVencedor(Jogador vencedor){
    if(!isOnWinnerScreen) return;
    int textSize = MeasureText(TextFormat("%s GANHOU A RODADA", vencedor.nome), 20);   
    DrawText(TextFormat("%s GANHOU A RODADA", vencedor.nome), 597 - textSize/2, 320, 20, GOLD);
}

void DesenharTurnoRound(int turno, int round, char trucoStatus, Jogador *trucado){
    int textSize = MeasureText(TextFormat("TURNO: %d", turno+1), 30);   
    DrawText(TextFormat("TURNO: %d", turno+1), 597 - textSize/2, 40-15, 30, GREEN);

    textSize = MeasureText(TextFormat("RODADA: %d", round), 18);   
    DrawText(TextFormat("RODADA: %d", round), 597 - textSize/2, 70-15, 18, GREEN);

    textSize = MeasureText(TextFormat("VALOR RODADA: %d", valorPontoRodada), 18);   
    DrawText(TextFormat("VALOR RODADA: %d", valorPontoRodada), 597 - textSize/2, 740, 18, GREEN);

    if(trucoStatus == 'A'){
        textSize = MeasureText(TextFormat("[ %s ACEITOU o Truco ]", trucado->nome), 18);   
        DrawText(TextFormat("[ %s ACEITOU o Truco ]", trucado->nome), 597 - textSize/2, 760, 18, GREEN);
    }
    else if(trucoStatus == 'R'){
        textSize = MeasureText(TextFormat("[ %s RECUSOU o Truco ]", trucado->nome), 18);   
        DrawText(TextFormat("[ %s RECUSOU o Truco ]", trucado->nome), 597 - textSize/2, 760, 18, GREEN);
    }
}

void DesenharTelaFinal(Jogador jogadores[4]){

    int textSize;
    if((jogadores[0].pontos + jogadores[2].pontos) >=  MAX_POINTS_TO_WIN){
        DrawTexture(assets[ASSET_BACKGROUND_WINNERS], 0, 0, WHITE);
        textSize = MeasureText(TextFormat("Você E Prof. Dr. Thiago GANHARAM!"), 30);  
        DrawText(TextFormat("Você E Prof. Dr. Thiago GANHARAM!"), 595 - textSize/2, 350, 30, GOLD);
    }
    else if((jogadores[1].pontos + jogadores[3].pontos) >= MAX_POINTS_TO_WIN){
        DrawTexture(assets[ASSET_BACKGROUND_WINNERS], 0, 0, WHITE);
        textSize = MeasureText(TextFormat("Amanda e Rebeca GANHARAM!"), 30);  
        DrawText(TextFormat("Amanda e Rebeca GANHARAM!"), 595 - textSize/2, 350, 30, GOLD);
    }

}


void DesenharTrucoScreen(Jogador* trucou, Jogador* trucado, int timePassed){

    if(!isOnTrucoScreen) return;

    int textSize = 0;

    if((trucado)->id == 0 || (trucado)->id == 2){
        DrawTexture(assets[ASSET_TRUCOTELA], 0, 0, WHITE);
        textSize = MeasureText(TextFormat("A EQUIPE ADVERSÁRIA PEDIU TRUCO!"), 20);  
        DrawText(TextFormat("A EQUIPE ADVERSÁRIA PEDIU TRUCO!"), 595 - textSize/2, 320, 20, GREEN);
        return;
    }

    DrawTexture(assets[ASSET_TRUCOTELA_SOLO], 0, 0, WHITE);
    textSize = MeasureText(TextFormat("A SUA EQUIPE PEDIU TRUCO!"), 30);  
    DrawText(TextFormat("A SUA EQUIPE PEDIU TRUCO!"), 595 - textSize/2, 350, 30, GREEN);


} 

void DesenharMenuPrincipal(){

	// Atualiza o botão selecionado e toca o efeito sonoro caso clique na setas do teclado
	if(IsKeyPressed(KEY_RIGHT)){
		menuCurrentSelectedOption++;
		if(menuCurrentSelectedOption == 4) menuCurrentSelectedOption = 0;
		PlaySound(gameSound[SFX_MENU_BUTTON]);

	}

	// Atualiza o botão selecionado e toca o efeito sonoro caso clique na setas do teclado
	if(IsKeyPressed(KEY_LEFT)){
		menuCurrentSelectedOption--;
		if(menuCurrentSelectedOption == -1){
			menuCurrentSelectedOption = 3;
		}
		PlaySound(gameSound[SFX_MENU_BUTTON]);
	}

	// Verifica qual botão o jogador selecionou e clicou
	if(IsKeyPressed(KEY_ENTER)){
		if(menuCurrentSelectedOption == OPTION_SAIR) CloseWindow();
		else if(menuCurrentSelectedOption == OPTION_START) startGame(true);
		PlaySound(gameSound[SFX_MENU_BUTTON]);
	}

    if(menuCurrentSelectedOption == OPTION_START) DrawTexture(assets[TRUCO_MAINMENU_INICIAR], 0, 0, WHITE);
    if(menuCurrentSelectedOption == OPTION_SAIR) DrawTexture(assets[TRUCO_MAINMENU_SAIR], 0, 0, WHITE);
    if(menuCurrentSelectedOption == OPTION_SCOREBOARD) DrawTexture(assets[TRUCO_MAINMENU_SCOREBOARD], 0, 0, WHITE);
    if(menuCurrentSelectedOption == OPTION_LOAD) DrawTexture(assets[TRUCO_MAINMENU_CARREGAR], 0, 0, WHITE);

}
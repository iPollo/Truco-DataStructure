// ===========================================================================
//			
//		Truco (Desenvolvido em C, usando Raylib)
//		Por: Henrique Selau de Oliveira (338301) e Thec Maci Ivane Makosso (290771)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Estrutura de Dados - Prof. Dr. Thiago L. T. da Silveira 
//
// ===========================================================================

// ===========================================================================
// 		Imports e Includes Globas
// ===========================================================================

// Bibliotecas Nativas e Raylib
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "stdbool.h"
#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
 
// ===========================================================================
// 		Variáveis Globais/Constantes
// ===========================================================================

// Defines
#define FRAME_SECOND 60
#define CHANCE_OF_TRUCO 25
#define MAX_TRUCO_TIME_DELAY 5
#define MAX_POINTS_TO_WIN 6

// Globais constantes
const int SCREEN_WIDTH = 1200;  
const int SCREEN_HEIGHT = 800;
const int START_SCREEN_DIMENSION = 650;
const int TILE_SIZE = 50;
const int TILE_LINES = SCREEN_HEIGHT/TILE_SIZE;
const int TILE_ROWS = SCREEN_WIDTH/TILE_SIZE;
char MAP[16][24];
    
// Globais de gerenciamento do game loop
bool isGameRunning = false;
bool isGameOver = false;
bool isOnFinalScreen = false;
bool isOnWinnerScreen = false;
bool isOnTrucoScreen = false;
bool canTruco = true;
bool isFinalEffectPlayed = false;
int valorPontoRodada = 1;


// Declaração das Funções principais
int startGame(bool startRealGame);
int finishGame();
void gameUpdate();
void updateGameCardStat();

// ===========================================================================
// 		Dependencias do jogo (Módulos)
// ===========================================================================

// Includes
#include   "gameAudio/gameAudioCore.c"
#include   "gameData/Carta/Carta.h"
#include   "gameData/Carta/Carta.c"
#include   "gameData/Baralho/Baralho.h"
#include   "gameData/Baralho/Baralho.c"
#include   "gameData/BaralhoJogador/BaralhoJogador.h"
#include   "gameData/BaralhoJogador/BaralhoJogador.c"
#include   "gameData/Jogador/Jogador.h"
#include   "gameData/Jogador/Jogador.c"
#include   "gameData/ListaCircular/ListaCircular.h"
#include   "gameData/ListaCircular/ListaCircular.c"
#include   "gameLogic/gameLogic.c"
#include   "gameTextures/gameTextures.c"

// ===========================================================================
// 		Core
// ===========================================================================

// Main Data (Usado na inicialização dos valores dos jogos)
Baralho* novoBaralho;
Baralho* cartasJogadas;
Carta manilha;
Carta textureInfoCartasJogadas[4];
Jogador jogadores[4];
Jogador ganhador;
Jogador *trucado;
Jogador *trucou;
ListaCircular listaCircularJogadores;

int contadorDeCartas = 0;
int contadorDeRodadas = 1;
int contadorTurno = 0;
int globalFrameCounter = 0;

char trucoStatus = 'O';

int main(void){
	
	// Inicializa a janela (Raylib)
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Truco - Estrutura de Dados");
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, (GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2)+ 50);
	
	// Inicializa o dispositivo de áudio (Raylib)
	InitAudioDevice(); 

	// Inicializa os efeitos sonoros 
	gameAudioInit();

	// Define o FPS para 60 (Raylib)
	SetTargetFPS(60);

	// Inicializa as texturas (assets/sfx etc.)
	InicializarAssets();

	// Chama a funçao mas não inicializa o jogo, apenas para setar algumas variáveis
	startGame(false);

	// Game Loop principal
    while (!WindowShouldClose()) 
    {
    	// Raylib (Desenha e atualiza as variáveis do jogo)
        BeginDrawing();

		// Atualiza os efeitos sonoros
		gameAudioUpdate();

		// Manutenção da contagem de frame (para timers)
		globalFrameCounter++;

		// Atualiza a lógica principal do jogo
		gameUpdate();

		// Finaliza o drawning
        EndDrawing();
    }

    // Finaliza o dispositivo de áudio (Raylib)
    CloseAudioDevice(); 
    
}

// Inicia o jogo
int startGame(bool startRealGame){

	// Centraliza a janela
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2);

	setMenuMusicPlaying(true);

	novoBaralho = criarBaralho();
	cartasJogadas = criarBaralho();

	// Atualiza o status do jogo
	isGameRunning = false;
	isGameOver = false;
	isOnFinalScreen = false;
	isFinalEffectPlayed = false;

	baralhoGerarTruco(novoBaralho);
	manilha = logicEscolherManilha(novoBaralho);

	listaCircularJogadores.prim = &jogadores[0];

	logicInicializarJogadores(jogadores);

	if(startRealGame){
		setMenuMusicPlaying(false);
		setGameMusicPlaying(true);
		logicDistribuirCartas(novoBaralho, jogadores);
		isGameRunning = true;
	}

	contadorDeCartas = 0;
	contadorDeRodadas = 1;
	contadorTurno = 0;
	globalFrameCounter = 0;
	trucoStatus = 'O';
	isOnWinnerScreen = false;
	isOnTrucoScreen = false;
	canTruco = true;
	valorPontoRodada = 1;


	//baralhoImprimir(novoBaralho);
	//TraceLog(LOG_INFO, "=========== TAMANHO ============ %d",baralhoTamanho(novoBaralho));

	return 1;

}

void gameUpdate(){

	// Primeira verifica se há ganhadores na rodada
	if(!logicVerificarGanhadores(jogadores) && isGameRunning){	
		
		// Atualiza a referência do jogador principal baseado na lista circular de jogadores
		Jogador jogadorAtual = *(listaCircularJogadores.prim);

		// Automação para RNG de jogadas da IA
		if((globalFrameCounter >= FRAME_SECOND * 3) && !isOnWinnerScreen && !isOnTrucoScreen){

			if(jogadorAtual.id != 0){

				// Decição para solicitar truco e/ou jogar uma carta
				int amount = GetRandomValue(0, 100);
				if(amount < CHANCE_OF_TRUCO && contadorDeCartas < 3 && canTruco){
					isOnTrucoScreen = true;
					trucou = (listaCircularJogadores.prim);
					trucado = listaCircularJogadores.prim->prox;
					globalFrameCounter = 0;
					valorPontoRodada = 3;
					PlaySound(gameSound[SFX_TRUCO]);
				}
				else{
					logicJogarCarta(listaCircularJogadores.prim, jogadorAtual.baralhoJogador->prim->info, cartasJogadas, &listaCircularJogadores, contadorDeCartas, textureInfoCartasJogadas);
					logicImprimirTodasInformacoes(jogadores, novoBaralho, *listaCircularJogadores.prim, manilha, cartasJogadas, contadorDeRodadas);
					contadorDeCartas++;

					updateGameCardStat();
				}

			}

			globalFrameCounter = 0;

		}

		// Controle e automação da tela de truco para ambos os lados
		// Isto é, caso a sua equipe receba o truco ou ela o solicite
		if(isOnTrucoScreen){
			
			if((trucado)->id == 0 || (trucado)->id == 2){
				if(IsKeyPressed(KEY_A)){
					isOnTrucoScreen = false;
					canTruco = false;
					trucoStatus = 'A';
					PlaySound(gameSound[SFX_MENU_BUTTON]);
					PlaySound(gameSound[SFX_ACCEPT]);
				}

				if(IsKeyPressed(KEY_D)){
					valorPontoRodada += 3;			
					trucou = trucado;
					trucado = trucado->prox;
					trucoStatus = 'D';
					PlaySound(gameSound[SFX_MENU_BUTTON]);
				}

				if(IsKeyPressed(KEY_R)){
					trucou->pontos++;
					valorPontoRodada = 1;
					isOnTrucoScreen = false;
					canTruco = false;
					trucoStatus = 'R';
					PlaySound(gameSound[SFX_MENU_BUTTON]);
					PlaySound(gameSound[SFX_REJECT]);
				}
				globalFrameCounter = 0;
			}
			else{
				if(globalFrameCounter > FRAME_SECOND*MAX_TRUCO_TIME_DELAY){
					
					int value = GetRandomValue(0, 100);
					
					if(value < 10){
						valorPontoRodada += 3;
						trucou = trucado;
						trucado = trucado->prox;
						trucoStatus = 'D';
						
					}
					else if(value >= 10 && value < 50){
						isOnTrucoScreen = false;
						canTruco = false;
						trucoStatus = 'A';
						PlaySound(gameSound[SFX_ACCEPT]);
					}
					else{

						trucou->pontos++;
						valorPontoRodada = 1;
						isOnTrucoScreen = false;
						canTruco = false;
						trucoStatus = 'R';
						PlaySound(gameSound[SFX_REJECT]);
					}

					globalFrameCounter = 0;

				}


			}


			globalFrameCounter++;
		}

		// Automação para ir para próxima rodada
		if(IsKeyPressed(KEY_ENTER) && isOnWinnerScreen && !isOnTrucoScreen){
			updateGameCardStat();
			globalFrameCounter = 0;
		}

		// Comandos do jogador (para jogar carta)
		if(jogadorAtual.id == 0 && !isOnWinnerScreen && !isOnTrucoScreen){
			if(IsKeyPressed(KEY_KP_1)){
				logicJogarCarta(listaCircularJogadores.prim, jogadorAtual.baralhoJogador->prim->info, cartasJogadas, &listaCircularJogadores, contadorDeCartas, textureInfoCartasJogadas);
				logicImprimirTodasInformacoes(jogadores, novoBaralho, *listaCircularJogadores.prim, manilha, cartasJogadas, contadorDeRodadas);
				contadorDeCartas++;
				globalFrameCounter = 0;
				updateGameCardStat();
			}
			else if(IsKeyPressed(KEY_KP_2) && baralhoJogadorTamanho(jogadorAtual.baralhoJogador) >= 2){
				logicJogarCarta(listaCircularJogadores.prim, jogadorAtual.baralhoJogador->prim->prox->info, cartasJogadas, &listaCircularJogadores, contadorDeCartas, textureInfoCartasJogadas);
				logicImprimirTodasInformacoes(jogadores, novoBaralho, *listaCircularJogadores.prim, manilha, cartasJogadas, contadorDeRodadas);
				contadorDeCartas++;
				globalFrameCounter = 0;
				updateGameCardStat();
			}
			else if(IsKeyPressed(KEY_KP_3) && baralhoJogadorTamanho(jogadorAtual.baralhoJogador) >= 3){
				logicJogarCarta(listaCircularJogadores.prim, jogadorAtual.baralhoJogador->prim->prox->prox->info, cartasJogadas, &listaCircularJogadores, contadorDeCartas, textureInfoCartasJogadas);
				logicImprimirTodasInformacoes(jogadores, novoBaralho, *listaCircularJogadores.prim, manilha, cartasJogadas, contadorDeRodadas);
				contadorDeCartas++;
				globalFrameCounter = 0;
				updateGameCardStat();
			}
			else if(IsKeyPressed(KEY_T) && canTruco){
				isOnTrucoScreen = true;
				trucou = (listaCircularJogadores.prim);
				trucado = listaCircularJogadores.prim->prox;
				globalFrameCounter = 0;
				valorPontoRodada = 3;
				PlaySound(gameSound[SFX_TRUCO]);
			}
		}

		// Funções de desenho para texturas e assets
		DesenharTelaDeFundo();
		DesenharCartas(jogadores);
		DesenharCartasJogadas(cartasJogadas, textureInfoCartasJogadas);
		DesenharCartasJogador(baralhoJogadorTamanho(jogadores[0].baralhoJogador), jogadores[0]);
		DesenharPontuacao(jogadores);
		DesenharVez(jogadorAtual, ganhador);
		DesenharTelaVencedor(ganhador);
		DesenharTurnoRound(contadorTurno, contadorDeRodadas, trucoStatus, trucado);
		DesenharTrucoScreen(trucou, trucado, 0);
	}

	// Menu principal e tela final (ganhador/perdedor)
	else{
		
		if(isOnFinalScreen){
			if(!isFinalEffectPlayed){
				PlaySound(gameSound[SFX_LEVELUP]);
				setGameMusicPlaying(false);
			}
			isFinalEffectPlayed = true;
			DesenharTelaFinal(jogadores);
		}
		else DesenharMenuPrincipal();

		if(IsKeyPressed(KEY_ENTER) && isOnFinalScreen){
			isGameRunning = false;
			isOnFinalScreen = false;
			setMenuMusicPlaying(true);
		}
		
	}
}

// Atualiza o status das cartas jogadas e das rodadas/turnos
void updateGameCardStat(){
	if(contadorDeCartas == 4 && !isOnWinnerScreen){
		ganhador = logicVerificarGanhador(jogadores, cartasJogadas);
		listaCircularJogadores.prim = &ganhador;
		isOnWinnerScreen = true;
	}
	else if(contadorDeCartas == 4 && isOnWinnerScreen){
		contadorDeRodadas++;
		contadorDeCartas = 0;
		isOnWinnerScreen = false;
		canTruco = true;
		valorPontoRodada = 1;
		trucoStatus = 'O';
		baralhoLimpar(cartasJogadas);
		if(contadorDeRodadas == 4){
			// Redistribuir cartas
			TraceLog(LOG_INFO, "RODADAS ENCERRADAS");
			contadorDeRodadas = 1;
			contadorDeCartas = 0;
			contadorTurno++;
			if(baralhoTamanho(novoBaralho) < 12){
				baralhoLimpar(novoBaralho);
				baralhoGerarTruco(novoBaralho);

			}
			
			logicDistribuirCartas(novoBaralho, jogadores);


		}
	}
}
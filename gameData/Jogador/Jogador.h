typedef struct Jogador
{
    struct Jogador* prox;
    BaralhoJogador* baralhoJogador;
    char nome[20];
    int id;
    int pontos;

}Jogador;

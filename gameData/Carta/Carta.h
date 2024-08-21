
// Enum dos tipos de naipes
enum{
    NAIPE_OURO = 0,
    NAIPE_ESPADA,
    NAIPE_COPAS,
    NAIPE_PAUS,
};

// Enum dos tipos de cartas disponíveis no baralho do truco
enum{
    VALOR_4 = 0,
    VALOR_5,
    VALOR_6,
    VALOR_7,
    VALOR_Q,
    VALOR_J,
    VALOR_K,
    VALOR_A,
    VALOR_2,
    VALOR_3,
};

typedef struct Carta
{
    int naipe;
    int valor;
    int jogadorQueJogou;
    
}Carta;

void cartaImprimir(Carta carta);

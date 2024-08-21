void cartaImprimir(Carta carta){

    char cartaValor = '4';
    
    // Enum dos tipos de cartas disponíveis no baralho do truco
    switch(carta.valor){
        case VALOR_4: cartaValor = '4'; break;
        case VALOR_5: cartaValor = '5'; break;
        case VALOR_6: cartaValor = '6'; break;
        case VALOR_7: cartaValor = '7'; break;
        case VALOR_Q: cartaValor = 'Q'; break;
        case VALOR_J: cartaValor = 'J'; break;
        case VALOR_K: cartaValor = 'K'; break;
        case VALOR_A: cartaValor = 'A'; break;
        case VALOR_2: cartaValor = '2'; break;
        case VALOR_3: cartaValor = '3'; break;
    }
   
    switch(carta.naipe){
        case NAIPE_OURO: TraceLog(LOG_WARNING, "%c de OURO", cartaValor); break;
        case NAIPE_ESPADA: TraceLog(LOG_WARNING, "%c de ESPADA", cartaValor); break;
        case NAIPE_COPAS: TraceLog(LOG_WARNING, "%c de COPAS", cartaValor); break;
        case NAIPE_PAUS: TraceLog(LOG_WARNING, "%c de PAUS", cartaValor); break;
    };

};
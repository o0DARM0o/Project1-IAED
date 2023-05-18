/* iaed-23 - ist1102760 - projeto1 */
/* 
 * autor: Diogo Marques 102760
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cabecalho.h"


int numCarreiras = 0;
int numParagens = 0;

/* FUNÇÕES DE LEITURA*/

/* funçao que lê o nome da paregem entre aspas, retorna 0 em
caso de uma leitura bem sucedida e -1 se o nome passar dos limites*/
int leNomeParagem(char str[]){
    int estado = DENTRO, i = 0;
    char c = getchar();

    while(estado == DENTRO){ /* enquanto estiver entre as aspas guarda o nome no vetor */
        str[i++] = c;
        c = getchar();
        if(c == '"'){
            str[i] = '\0';
            estado = FORA;
        }
    }
    return 0;
}

/* função que lê a proxima palavra dada no input até encontrar um espaço 
ou até encontrar aspas retorna true em caso de ter chegado ao fim da linha*/
int lePalavra(char str[]){
    char c = getchar();
    int i = 0;
    while(c == ' ' || c == '\t'){
        c = getchar();
    }
    while(c != ' ' && c != '\n'){ /* lê palavra até encontrar espaço branco ou fim de linha*/
            str[i] = c;
        if(c == '"'){ /* se encontrar aspas significa que temos um nome de paragem com espaços brancos*/
            leNomeParagem(str);
            c = getchar();
            return (c == '\n');
        }else{
            i++;
            c = getchar();
        }
    }
    str[i] = '\0';

    return (c == '\n'); 
}

/* lê o input até ao fim sem guardar nada*/
void leAteAoFim(){
    char c = getchar();
    while(c != '\n'){
        c = getchar();
    }
}
 /* lê palavra(s) até ao fim da linha e guarda*/
void leFimLinha(char str[]){
    char c = getchar();
	int i = 0;
	while (c != '\n') {
		str[i++] = c;
		c = getchar();
	}
	str[i] = '\0';
}

/* FUNÇÕES DO COMANDO 'c' */


/* função lista todas as carreiraS do sistema, uma por linha*/
void listaTodasAsCarreiras(){
    int i;
    for(i = 0; i< numCarreiras; i++){
        if(_carreiras[i].numParagens == 0){ /* caso a carreira não tenha nenhuma paragem ignorasse os campos com os nomes das paragens*/
            printf("%s %d %.2f %.2f\n", _carreiras[i].nome,
            _carreiras[i].numParagens, _carreiras[i].custo, 
            _carreiras[i].duracao);
        }else{
            printf("%s %s %s %d %.2f %.2f\n", _carreiras[i].nome, 
            _paragens[_carreiras[i].paragens[0]].nome , 
            _paragens[_carreiras[i].paragens[_carreiras[i].numParagens-1]].nome,
            _carreiras[i].numParagens, _carreiras[i].custo, 
            _carreiras[i].duracao);
        }
    }
}

/* função lista todos os nomes das paregens de uma determinada carreira
com indice ind por ordem de  origem -> destino*/ 
void listaParagensCarreira(int ind){
    int i;
    for(i = 0; i< _carreiras[ind].numParagens; i++){
        printf("%s", _paragens[_carreiras[ind].paragens[i]].nome);
        if(i != _carreiras[ind].numParagens-1){
            printf(", ");
        }else{
            putchar('\n'); /* caso seja a  ultima paragem da carreira, muda de linha*/
        }
    }

}

/* função verifica se uma determinada carreira com nome str pertence ao sistema, 
retornado o  indice da mesmo caso exista*/
int procuraCarreira(char str[]){
    int i;

    for(i = 0; i < numCarreiras; i++){
        if(strcmp(str, _carreiras[i].nome) == 0){
            return i; /* indice da carreira no vetor global*/    
        }
    }

    return NAO_EXISTE;
}

/* função adiciona a carreira crr ao sistema*/
void adicionaCarreira(Carreira crr){

    /* inicializa  a carreira no vetor global de carreiras*/
    strcpy(_carreiras[numCarreiras].nome, crr.nome);
    _carreiras[numCarreiras].numLigacoes = 0;
    _carreiras[numCarreiras].numParagens = 0;
    _carreiras[numCarreiras].custo = 0;
    _carreiras[numCarreiras].duracao = 0;
    numCarreiras++;

}

/* função lista as paragens de uma carreira por ordem inversa destino -> origem*/
void mostraInverso(char str[]){
    int i, indC = procuraCarreira(str);
    for(i = _carreiras[indC].numParagens-1; i >= 0; i--){ /* começando no ultimo indice do vetor lista de tras para frente*/
        printf("%s", _paragens[_carreiras[indC].paragens[i]].nome);
        if(i != 0){
            printf(", ");
        }else{
            putchar('\n'); /* caso seja o nome da ultima paragem*/
        }
    }
}

/* função verifica se o terceiro argumento do comando 'c' está nas condições 
para listar paragens  no sentido inverso*/
int condicaoInverso(char str[], char nome[]){
    /* verifica todas as possibilidades para prefixos da palavra inverso, caso alguma se verifica mostra o as paragens em sentido inverso*/
    if(strcmp(str, "inverso") == 0){
        mostraInverso(nome);
    }else if(strcmp(str, "inv") == 0){
        mostraInverso(nome);
    }else if(strcmp(str, "inve") == 0){
        mostraInverso(nome);
    }else if(strcmp(str, "inver") == 0){
        mostraInverso(nome);
    }else if(strcmp(str, "invers") == 0){
        mostraInverso(nome);
    }else{
        return FALSE;
    }
    return TRUE;
}

/* função principal do comando 'c' que distribui diferentes funções para diferentes inputs*/
void commandCarreira(){
    Carreira crr;
    char  resto[MAX_BYTES_CARREIRA];
    int ind, palavra;

    palavra = lePalavra(crr.nome); /* lê nome da carreira */
    if(strlen(crr.nome) == 0){ /* se não se nenhum nome de carreira, então lista-se todas as carreiras do sistema*/
        listaTodasAsCarreiras();
    }else{
        ind = procuraCarreira(crr.nome);
        if(palavra == ERRO){
            return;
        }
        if(!palavra){ /* se o nome da carreira não for o ultimo argumeto então verifica-se se tem uma sort option valida*/
            if(ind !=NAO_EXISTE){
                leFimLinha(resto);
                if(!condicaoInverso(resto, crr.nome)){
                    printf("incorrect sort option.\n");
                    return;
                }
            }
        }else{
            if(ind != NAO_EXISTE){ /* se o indice da paragem existir, então escrevemos  todas as paragens da carreira (origem -> destino)*/
                listaParagensCarreira(ind);
            }else{
                if(numCarreiras < MAX_CARREIRAS){; /* se não existir. adicionamos uma nova carreira*/
                    adicionaCarreira(crr);
                }else{ /* caso o numero de carreiras do sistema tenha atingido o maximo*/
                    printf("Número máximo de Carreiras atingido\n");
                    }
                }
        }
    }
}

/* FUNÇÕES DO COMANDO 'p' */

/* função verifica se uma determinada paragem com nome str pertence ao sistema, 
retornado o  indice da mesmo caso exista*/
int procuraParagem(char str[]){
    int i;

    for(i = 0; i < numParagens; i++){
        if(strcmp(str, _paragens[i].nome) == 0){
            return i; /* indice da paragem no vetor global*/
        }
    }

    return NAO_EXISTE;
}

/* função dá print do nome da paragem com a sua longitude e latitude */
void mostraParagem(int paragem){
    printf("%s: %16.12f %16.12f %d\n", _paragens[paragem].nome,
     _paragens[paragem].lat,
     _paragens[paragem].longe, _paragens[paragem].nCarreiras);
}

/* função adiciona a paragem com o nome str ao sistema */
void adicionaParagem(char str[]){
    Paragem paragem;
    double longe, lat;
    strcpy(paragem.nome, str);
    strcpy(_paragens[numParagens].nome, paragem.nome);
    memset(str, 0, MAX_BYTES_PARAGEM);
    lePalavra(str); /* lê e converte para float a latitude da paragem*/ 
    lat = atof(str);
    memset(str, 0, MAX_BYTES_PARAGEM); /* reseta o vetor str*/
    lePalavra(str); /* lê e converte para float a longitude da paragem*/ 
    longe = atof(str);
    /* inicializa  a paragem  str no vetor global*/
    paragem.lat = lat;
    paragem.longe = longe;
    paragem.nCarreiras = 0;
    _paragens[numParagens].lat = lat;
    _paragens[numParagens].longe = longe;
    _paragens[numParagens].nCarreiras = 0;
    numParagens++; 
}

/* função lista todas as parages do sistema, uma por linha*/
void listaTodasAsParagens(){
    int i;
    for(i = 0; i < numParagens; i++){
        mostraParagem(i);
    }
}

/* função principal do comando 'p' que distribui diferentes funções para diferentes inputs
e no caso de haver alguma irregularidade dá print do erro*/
void commandParagem(){
    Paragem paragem;
    int palavra, ind;

    palavra = lePalavra(paragem.nome); /* lê argumento destinado ao nome da paragem*/
    if(strlen(paragem.nome)== 0){
        listaTodasAsParagens();  /* lista todas as paragens do sistema se não for verificado nenhum nome de paragem*/
    }else{
        ind = procuraParagem(paragem.nome);
        if(!palavra){ /* caso o nome da paragem não seja o ultimo argumento*/
            if(ind == NAO_EXISTE){
                if(numParagens < MAX_PARAGENS){ /* se o indice não existir e existir espaço para uma nova paragem, então adiciona-se*/
                    adicionaParagem(paragem.nome);
                }else{
                    printf("Número máximo de paragens atingido\n");
                    leAteAoFim();
                }
            }else{ /* se o indice já existir então lança-se um erro*/
                printf("%s: stop already exists.\n", paragem.nome);
                leAteAoFim();
            }
        }else if(ind != NAO_EXISTE){ /* caso o nome da paragem seja o ultimo argumento, entao escreve-se a latitude e longitude da paragem*/
            printf("%16.12f %16.12f\n", _paragens[ind].lat, _paragens[ind].longe);
        }else{ /* caso a  paragem não existir no sistema*/
            printf("%s: no such stop.\n", paragem.nome);
        }
    }
}

/* FUNÇÕES DO COMANDO 'l' */

/* função verifica os três primeiros argumentos do input e lança os erros caso 
algo de errado se verifique */  
int verificaArgumentosLigacoes(Carreira carr, Paragem paraO, Paragem paraD){
    int crr  = procuraCarreira(carr.nome);
    if(crr == NAO_EXISTE){ /* não existe a carreira no sistema*/
        printf("%s: no such line.\n", carr.nome);
        leAteAoFim();
    }else if(procuraParagem(paraO.nome) == NAO_EXISTE){ /* não existe a paragem no sistema*/
        printf("%s: no such stop.\n", paraO.nome);
        leAteAoFim();
    }else if(procuraParagem(paraD.nome) == NAO_EXISTE){
        printf("%s: no such stop.\n", paraD.nome);
        leAteAoFim();
    }else if(_carreiras[crr].numParagens >= 2){ 
        if(strcmp(paraO.nome, 
        _paragens[_carreiras[crr].paragens[_carreiras[crr].numParagens-1]]
        .nome) == 0 ||
        strcmp(paraD.nome, _paragens[_carreiras[crr].paragens[0]].nome) == 0){  /* a paragem de destino da ligação tem de corresponder à origem
                                    da carreira ou a paragem de origem da ligação tem de ser a paragem  de destino final da carreira */
            return TRUE;                                                                    
        }
        printf("link cannot be associated with bus line.\n");
        leAteAoFim();
        return FALSE;
    }else{
        return TRUE;
    }
    return FALSE;
}

/* função verifica se a paragem prg já existe na carreira de indice indC */
int procuraParagemCarreira(Paragem prg, int indC){
    int i;
    for(i = 0; i <= _carreiras[indC].numParagens-1; i++){
        if(strcmp(_paragens[_carreiras[indC].paragens[i]].nome,
         prg.nome) == 0){
            return 0; 
        }
    }
    return NAO_EXISTE;
}

/* função atualiza o número de carreiras da paragem e adiciona o novo indica da nova carreira da paragem */
void atualizaParagem(Paragem prg, int indC){
    int ind;
    if(procuraParagemCarreira(prg, indC) != NAO_EXISTE){
        return;
    }
    ind = procuraParagem(prg.nome);
    _paragens[ind].nCarreiras++;
    _paragens[ind].indexCrr[_paragens[ind].nCarreiras-1] = indC; /* adiciona a nova carreira à paragem*/
}

/* função ordena o vetor de indices de carreiras pela ordem alfabética de nomes*/
void ordenaNomesCarreiras(int index){
    int i, j, aux;
    for(i = 0; i < _paragens[index].nCarreiras; i++){
        for(j = i+1; j < _paragens[index].nCarreiras; j++){
            if(strcmp(_carreiras[_paragens[index].indexCrr[i]].nome,
            _carreiras[_paragens[index].indexCrr[j]].nome) > 0){
                aux = _paragens[index].indexCrr[i];
                _paragens[index].indexCrr[i] = _paragens[index].indexCrr[j];
                _paragens[index].indexCrr[j] = aux;
            }
        }
    }
}

/* função adiciona uma nova origem à carreira indC*/
void adicionaNovaOrigem(int indC, int indO){
    int i;
    for(i = _carreiras[indC].numParagens; i >= 1; i--){
        _carreiras[indC].paragens[i] = _carreiras[indC].paragens[i-1];
    } /* muda todos os elementos do vetor para o indice da direita*/
    _carreiras[indC].paragens[i] = indO; /* adiciona a nova origem da carreira*/
    _carreiras[indC].numParagens++;
    ordenaNomesCarreiras(indO); /* ordena por ordem alfabetica os nomes das carreiras*/
}

/* função adiciona um novo destino final à carreira indC*/
void adicionaNovoDestino(int indC, int indD){
        _carreiras[indC].paragens[_carreiras[indC].numParagens] = indD; /* adciona novo destino à carreira*/
        _carreiras[indC].numParagens++;
        ordenaNomesCarreiras(indD);  /* ordena por ordem alfabetica os nomes das carreiras*/
}

/* função adiciona origem e destino a um carreira, caso esta não tenha nenhuma paragem ainda */
void adicionaOrigemEDestino(int indC, int indO, int indD){
    int numP = _carreiras[indC].numParagens;
    /* adiciona  origem e destino à carreira*/
    _carreiras[indC].paragens[numP] = indO;
    numP++;
    _carreiras[indC].paragens[numP] = indD;
    _carreiras[indC].numParagens += 2;
    ordenaNomesCarreiras(indO); /* ordena por ordem alfabetica os nomes das carreiras*/
    ordenaNomesCarreiras(indD);
}

/* função adiciona nova ligação à carreira crr, adicionando nova paragem(s) */
void adicionaLigacao(Carreira crr, Paragem paraO, Paragem paraD){
    int indC= procuraCarreira(crr.nome), 
    numP= _carreiras[indC].numParagens, indO= procuraParagem(paraO.nome), 
    indD= procuraParagem(paraD.nome);
    if(_carreiras[indC].numLigacoes == MAX_LIGACOES){ /* verifica se o  maximo de ligações do sistema foi atingido*/
        printf("LIMITE ATINGIDO\n");
        return;
    }else if(_carreiras[indC].numLigacoes == 0){ /* se a carreira não tiver nenhuma ligação então adiciona nova o rigem e destino*/
        atualizaParagem(paraD, indC);
        atualizaParagem(paraO, indC);
        adicionaOrigemEDestino(indC, indO, indD);
    }else if(strcmp(paraO.nome, 
        _paragens[_carreiras[indC].paragens[numP-1]].nome) == 0){ /* se a paragem de origem da ligação for igual à paragem de destino da carreira então
                                                        adiciona novo destino final à carreira*/
        atualizaParagem(paraD, indC);
        adicionaNovoDestino(indC, indD);
    }else if(strcmp(paraD.nome,
        _paragens[_carreiras[indC].paragens[0]].nome) == 0){ /* se a paragem de destino da ligação for igual à paragem de origem da carreira então
                                                        adiciona nova origem à carreira*/
        atualizaParagem(paraO, indC);
        adicionaNovaOrigem(indC, indO);
    }
    _carreiras[indC].custo += crr.custo;    /* incrementa custo e duração da carreira*/
    _carreiras[indC].duracao += crr.duracao;
    _carreiras[indC].numLigacoes++;
}

/* função principal do comando 'l' que verifica todos os argumentos do input e adciona nova ligação*/
void commandLigacoes(){
    Carreira carreira;
    Paragem paragemO, paragemD;
    float dur, vlr;
    char str[MAX_NUM_FLOAT];
    lePalavra(carreira.nome);
    lePalavra(paragemO.nome);
    lePalavra(paragemD.nome);

    if(strlen(carreira.nome) != 0){
        if((verificaArgumentosLigacoes(carreira, paragemO, paragemD))){ /* verifica  os argumentos  das paragens e carreira do input*/
            lePalavra(str); /* lê o valor da ligação e converte para float*/
            vlr = atof(str);
            memset(str, 0, MAX_NUM_FLOAT); /* reseta o vetor str*/
            lePalavra(str); /* lê a duração da ligação e converte para float*/
            dur = atof(str);
            if(vlr >= 0 && dur >= 0){ /* se a duração e o valor da ligação não forem negativos, adciona nova ligação*/
                carreira.custo = vlr;
                carreira.duracao = dur;
                adicionaLigacao(carreira, paragemO, paragemD);
            }else{
                printf("negative cost or duration.\n");
            }
        }

    }
}


/* FUNÇÃO DO COMANDO 'i' */

/* função lista todas as paragens (uma por linha), com os nomes de todas as carreiras que fazem intersecao
nessa mesma paragem por ordem alfabética*/
void commandInterseccoes(){
    int i, j;
    leAteAoFim();
    for(i = 0; i < numParagens; i++){
        if(_paragens[i].nCarreiras > 1){ /* se o numero de carreiras que passam na paragem é maior que 1 então entra na condição de intersecao*/
            printf("%s %d: ", _paragens[i].nome, _paragens[i].nCarreiras);
            for(j = 0; j < _paragens[i].nCarreiras; j++){ /* ciclo para escrever os nomes das carreiras*/
                printf("%s", _carreiras[_paragens[i].indexCrr[j]].nome);
                if(j < _paragens[i].nCarreiras-1){
                    printf(" ");
                }else{
                    putchar('\n'); /* caso seja a ultima carreira do vetor */
                }
            }
        }
    }
}
    

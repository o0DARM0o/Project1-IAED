
#ifndef CABECALHO_H
#define CABECALHO_H

#define MAX_CARREIRAS 200
#define MAX_PARAGENS 10000
#define MAX_LIGACOES 30000

#define MAX_BYTES_CARREIRA 21
#define MAX_BYTES_PARAGEM 51

#define MAX_NUM_FLOAT 100

#define NAO_EXISTE -1

#define TRUE 1
#define FALSE 0
#define DENTRO 1
#define FORA 0

#define ERRO -1

typedef struct{
    double longe;
    double lat;
    int intersecao;
    int nCarreiras;
    char nome[MAX_BYTES_PARAGEM];
    /*char carreias[MAX_CARREIRAS][MAX_BYTES_CARREIRA];*/
    int indexCrr[MAX_CARREIRAS+1];

    
} Paragem;

typedef struct{
    char nome[MAX_BYTES_CARREIRA];
    int paragens[MAX_PARAGENS];
    int numLigacoes;
    int numParagens;
    float custo;
    float duracao;


} Carreira;


int numCarreiras;
Carreira _carreiras[MAX_CARREIRAS];

int numParagens;
Paragem _paragens[MAX_PARAGENS];

int lePalavra(char str[]);
void leAteAoFim();
void listaTodasAsCarreiras();
void listaParagensCarreira(int ind);
int procuraCarreira(char str[]);
void adicionaCarreira(Carreira crr);
void commandCarreira();

int procuraParagem(char str[]);
void mostraParagem(int paragem);
void adicionaParagem(char str[]);
void listaTodasAsParagens();
void commandParagem();

int verificaArgumentosLigacoes(Carreira carr, Paragem paraO, Paragem paraD);
void adicionaNovaOrigem(int indC, int indO);
void atualizaParagem(Paragem prg, int indC);
void adicionaLigacao(Carreira crr, Paragem paraO, Paragem paraD);
void adicionaOrigemEDestino(int indC, int indO, int indD);
void adicionaNovoDestino(int indC, int indD);
void commandLigacoes();

void commandInterseccoes();

#endif

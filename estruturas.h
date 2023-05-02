#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#ifndef estruturas
#define estruturas .h

typedef struct TipoCelula *TipoApontador; 

typedef struct TipoItem { 
	int numero;
}TipoItem;

typedef struct TipoCelula {
	TipoItem Item;
	TipoApontador Prox;
} TipoCelula; 

// Fila dinamica
typedef struct TipoFila {
	TipoApontador Frente, Tras;
}TipoFila;

void FFVazia(TipoFila *Fila ) { 
	Fila ->Frente = (TipoApontador)malloc(sizeof(TipoCelula )); 
	Fila ->Tras = Fila ->Frente; 
	Fila ->Frente ->Prox = NULL; 
}

int Vazia(TipoFila Fila ) { 
	return (Fila.Frente == Fila.Tras);
}

void Enfileira (TipoItem x, TipoFila *Fila ) { 
	Fila ->Tras ->Prox = (TipoApontador)malloc(sizeof(TipoCelula )); 
	Fila ->Tras = Fila ->Tras ->Prox;
	Fila ->Tras ->Item = x; 
	Fila ->Tras ->Prox = NULL; 
}

void Desenfileira(TipoFila *Fila , TipoItem *Item) { 
	TipoApontador q; 
	if (Vazia( *Fila ) ) { 
	//	printf ( "Erro fila esta vazia\n" ) ; return;
	} 
	q = Fila ->Frente; 
	Fila ->Frente = Fila ->Frente ->Prox; 
	*Item = Fila ->Frente ->Item; 
	free(q); 
}

// Pilha dinamica
typedef struct { 
	TipoApontador  Fundo, Topo; 
	int Tamanho; 
} TipoPilha;

void FPVazia(TipoPilha *Pilha) { 
	Pilha ->Topo=(TipoApontador) malloc(sizeof(TipoCelula)); 
	Pilha ->Fundo = Pilha ->Topo; 
	Pilha ->Topo->Prox = NULL; 
	Pilha ->Tamanho = 0; 
}

int PVazia(TipoPilha Pilha) {
	return ( Pilha .Topo == Pilha .Fundo) ; 
}

void Empilha(TipoItem x, TipoPilha *Pilha) { 
	TipoApontador Aux; 
	Aux = (TipoApontador) malloc(sizeof(TipoCelula)); 
	Pilha ->Topo->Item = x; 
	Aux->Prox = Pilha ->Topo; 
	Pilha ->Topo = Aux; 	
	Pilha ->Tamanho++; 
}

void Desempilha(TipoPilha *Pilha , TipoItem *Item) {
	TipoApontador q; 
	if (PVazia( *Pilha ) ) { 
		//printf ( "Erro : lista vazia\n" ) ; 	return; 
	} 
	q = Pilha ->Topo; 
	Pilha ->Topo = q ->Prox; 
	*Item = q ->Prox->Item; 
	free(q) ;
	Pilha ->Tamanho--; 
}

int Tamanho(TipoPilha Pilha) { 
	return ( Pilha .Tamanho) ; 
}

#endif

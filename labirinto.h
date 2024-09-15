#ifndef __LABIRINTO_H__
#define __LABIRINTO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VOID -1

typedef struct Node {
    int x, y;
    char *path; 
    struct Node *next;
} Node;

typedef struct {
    Node *ini, *fim;
} Fila;

Fila *criaFila();
/*
Função:             criaFila
Descrição:          Aloca dinamicamente e inicializa uma estrutura Fila.
Entrada:            Nenhuma
Saída:              Ponteiro para a estrutura Fila alocada dinamicamente
*/

int eVazio(Fila *q);
/*
Função:             eVazio
Descrição:          Verifica se a fila está vazia.
Entrada:
q:                  Ponteiro para a estrutura Fila que será verificada.
Saída:              Retorna 1 se a fila estiver vazia, caso contrário, retorna 0.
*/

void enfileirar(Fila *q, int x, int y, const char *path);
/*
Função:             enfileirar
Descrição:          Adiciona um novo elemento à fila.
Entrada:
q:                  Ponteiro para a estrutura Fila onde o elemento será adicionado.
int x:              Coordenada x do novo elemento.
int y:              Coordenada y do novo elemento.
const char *path:   String que representa o caminho associado ao novo elemento.
Saída:              Nenhuma
*/

Node *desenfileirar(Fila *q);
/*
Função:             desenfileirar
Descrição:          Remove e retorna o elemento que está no início da fila.
Entrada:
q:                  Ponteiro para a estrutura Fila de onde o elemento será removido.
Saída:              Ponteiro para o Node removido da fila.
*/

void calcularDistanciaMinimaBestantes(int n, int m, char **labirinto, int **distanciaBestantes);
/*
Função:             calcularDistanciaMinimaBestantes
Descrição:          Calcula a distância mínima dos pontos do labirinto até as melhores distâncias.
Entrada:
n:                  Número de linhas do labirinto.
m:                  Número de colunas do labirinto.
labirinto:          Matriz que representa o labirinto.
distanciaBestantes: Matriz onde serão armazenadas as distâncias mínimas.
Saída:              Nenhuma
*/

void encontrarCaminhoTributo(int n, int m, char **labirinto, int **distanciaBestantes, int inicioX, int inicioY);
/*
Função:             encontrarCaminhoTributo
Descrição:          Encontra o caminho para o tributo no labirinto, utilizando as distâncias calculadas.
Entrada:
n:                  Número de linhas do labirinto.
m:                  Número de colunas do labirinto.
labirinto:          Matriz que representa o labirinto.
distanciaBestantes: Matriz com as distâncias mínimas calculadas.
inicioX:            Coordenada x do ponto inicial.
inicioY:            Coordenada y do ponto inicial.
Saída:              Nenhuma
*/

#endif

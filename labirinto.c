#include "labirinto.h"

Fila *criaFila() {
    Fila *novaFila = (Fila *)calloc(1, sizeof(Fila));
    if (!novaFila) { 
        printf("ERRO: Falha ao alocar memoria na fila.\n"); 
        exit(1); 
    }
    return novaFila;
}

// Função para verificar se a fila está vazia
int eVazio(Fila *q) {
    return (q->ini == NULL);
}

// Função para adicionar um elemento na fila
void enfileirar(Fila *q, int x, int y, const char *path) {
    Node *novo = (Node *)calloc(1, sizeof(Node));
    if (!novo) { 
        printf("ERRO: Falha ao alocar memoria no\n"); 
        exit(1); 
    }
    novo->x = x;
    novo->y = y;
    novo->path = strdup(path);  // Aloca e copia o caminho

    if (q->fim) q->fim->next = novo;
    else q->ini = novo;
    q->fim = novo;
}

// Função para remover um elemento da fila
Node *desenfileirar(Fila *q) {
    if (eVazio(q)) return NULL;
    Node *aux = q->ini;
    q->ini = aux->next;
    if (!q->ini) q->fim = NULL;
    return aux;
}

// Movimentos possíveis e suas respectivas direções
int movimentos[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}}; // Uma matriz de 4 linhas e 2 colunas
char direcoes[4] = {'D', 'U', 'L', 'R'}; // Um vetor de caracteres

// Função para calcular a distância mínima dos bestantes a todas as células
void calcularDistanciaMinimaBestantes(int n, int m, char **labirinto, int **distanciaBestantes) {
    Fila *filaBestantes = criaFila();

    // Inicializa distâncias e fila de Busca em Largura a partir dos bestantes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            distanciaBestantes[i][j] = VOID;
            if (labirinto[i][j] == 'M') {
                distanciaBestantes[i][j] = 0;
                enfileirar(filaBestantes, i, j, "");
            }
        }
    }

    // Busca em Largura para calcular distâncias mínimas dos bestantes
    while (!eVazio(filaBestantes)) {
        Node *atual = desenfileirar(filaBestantes);
        int x = atual->x, y = atual->y;
        free(atual->path);  // Libera o caminho antigo para evitar vazamento de memória
        free(atual);

        for (int i = 0; i < 4; i++) {
            int nx = x + movimentos[i][0], ny = y + movimentos[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && distanciaBestantes[nx][ny] == VOID) {
                if(labirinto[nx][ny] == '.' || labirinto[nx][ny] == 'A'){
                    distanciaBestantes[nx][ny] = distanciaBestantes[x][y] + 1;
                    enfileirar(filaBestantes, nx, ny, "");
                }
            }
        }
    }
    free(filaBestantes);
}

// Função para encontrar o caminho do tributo até uma borda do labirinto
void encontrarCaminhoTributo(int n, int m, char **labirinto, int **distanciaBestantes, int inicioX, int inicioY) {
    Fila *filaTributo = criaFila();
    int **visitado = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        visitado[i] = (int *)calloc(m, sizeof(int)); 
    }

    // Inicializa Busca em Largura do tributo
    visitado[inicioX][inicioY] = 1;
    enfileirar(filaTributo, inicioX, inicioY, "");

    while (!eVazio(filaTributo)) {
        Node *atual = desenfileirar(filaTributo);
        int x = atual->x, y = atual->y;
        char *caminho = atual->path;

        // Verifica se está na borda do labirinto
        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            printf("YES\n");
            printf("%d\n", (int)strlen(caminho));
            printf("%s\n", caminho);
            free(caminho);  // Libera o caminho
            free(atual);
            free(filaTributo);

            for (int i = 0; i < n; i++) {
                free(visitado[i]);
            }
            free(visitado);
            return;
        }

        // Movimentação do tributo
        for (int i = 0; i < 4; i++) {
            int nx = x + movimentos[i][0], ny = y + movimentos[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visitado[nx][ny] && labirinto[nx][ny] == '.') {
                if (distanciaBestantes[nx][ny] > (int)strlen(caminho) + 1 || distanciaBestantes[nx][ny] == VOID) {
                    visitado[nx][ny] = 1;
                    char *novoCaminho = (char *)malloc(strlen(caminho) + 2);
                    if (!novoCaminho) {
                        printf("ERRO: Falha ao alocar memória para novo caminho\n");
                        exit(1);
                    }
                    strcpy(novoCaminho, caminho);
                    novoCaminho[strlen(caminho)] = direcoes[i];
                    novoCaminho[strlen(caminho) + 1] = '\0';
                    enfileirar(filaTributo, nx, ny, novoCaminho);
                    free(novoCaminho); // Libera o caminho temporário após enfileirar
                }
            }
        }
        free(caminho);  // Libera o caminho antigo
        free(atual);
    }

    // Se não encontrar caminho para a borda
    printf("NO\n");
    free(filaTributo);

    for (int i = 0; i < n; i++) {
        free(visitado[i]);
    }
    free(visitado);
}
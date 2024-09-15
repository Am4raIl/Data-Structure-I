#include "labirinto.h"

int main(void) {
    int n, m;  
    scanf("%d %d", &n, &m);

    if (n <= 0 || m <= 0 || n > 1000 || m > 1000) { 
        printf("ERRO: Dimensões de labirinto invalidas\n");
        return 1;
    }

    char **labirinto = (char **)malloc(n * sizeof(char *));
    int **distanciaBestantes = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        labirinto[i] = (char *)malloc(m * sizeof(char) + 1);
        distanciaBestantes[i] = (int *)malloc(m * sizeof(int));
    }

    int inicioX = -1, inicioY = -1; // Indice do Tributo

    // Leitura do labirinto
    for (int i = 0; i < n; i++) {
        scanf("%s", labirinto[i]);
        for (int j = 0; j < m; j++) {
            if (labirinto[i][j] == 'A') {
                inicioX = i;
                inicioY = j;
            }
        }
    }

    // Verifique se a posição do tributo foi encontrada
    if (inicioX == -1 || inicioY == -1) {
        printf("NO\n");
        return 0;
    }

    // Calcular distâncias mínimas até os bestantes
    calcularDistanciaMinimaBestantes(n, m, labirinto, distanciaBestantes);

    // Encontrar caminho de fuga para o tributo
    encontrarCaminhoTributo(n, m, labirinto, distanciaBestantes, inicioX, inicioY);

    // Liberar memória alocada
    for (int i = 0; i < n; i++) {
        free(labirinto[i]);
        free(distanciaBestantes[i]);
    }
    free(labirinto);
    free(distanciaBestantes);

    return 0;
}

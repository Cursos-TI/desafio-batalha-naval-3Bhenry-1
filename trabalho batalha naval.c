// batalha_naval_habilidades.c
#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0) e navios (3)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    // Exemplo: posicionar navios
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[3][2] = 3;
    tabuleiro[6][6] = 3;
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Cria matriz Cone (aponta para baixo)
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE / 2) - i && j <= (TAM_HABILIDADE / 2) + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Cria matriz Cruz
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Cria matriz Octaedro (losango)
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(centro - i) + abs(centro - j) <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Sobrepõe a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linhaTab = origemLinha - centro + i;
            int colunaTab = origemColuna - centro + j;

            if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                colunaTab >= 0 && colunaTab < TAM_TABULEIRO &&
                habilidade[i][j] == 1) {
                if (tabuleiro[linhaTab][colunaTab] != 3) {
                    tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 6, 6);
    aplicarHabilidade(tabuleiro, octaedro, 4, 4);

    printf("Tabuleiro com habilidades aplicadas:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}

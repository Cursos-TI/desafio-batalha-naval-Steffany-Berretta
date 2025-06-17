#include <stdio.h>

#define TAMANHO 10             // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3        // Cada navio ocupa 3 posições
#define NAVIO 3                // Valor que representa um navio no tabuleiro
#define AGUA 0                 // Valor que representa água
#define HABILIDADE 5           // Valor que representa área afetada por habilidade

// Função que verifica se um navio pode ser posicionado (sem sair dos limites e sem sobrepor outro)
int pode_posicionar(int tabuleiro[TAMANHO][TAMANHO], int posicoes[][2], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];

        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
            return 0; // Está fora do tabuleiro
        }

        if (tabuleiro[linha][coluna] != AGUA) {
            return 0; // Já há um navio nesta posição
        }
    }
    return 1;
}

// Função que posiciona o navio no tabuleiro
void posicionar(int tabuleiro[TAMANHO][TAMANHO], int posicoes[][2], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];
        tabuleiro[linha][coluna] = NAVIO;
        printf("(%d, %d)\n", linha, coluna); // Exibe coordenadas do navio
    }
}

// Função que cria coordenadas para um navio com base na direção desejada
void criar_navio(int posicoes[][2], int linha_inicial, int coluna_inicial, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        switch (direcao) {
            case 'H': posicoes[i][0] = linha_inicial;     posicoes[i][1] = coluna_inicial + i; break;
            case 'V': posicoes[i][0] = linha_inicial + i; posicoes[i][1] = coluna_inicial;     break;
            case 'D': posicoes[i][0] = linha_inicial + i; posicoes[i][1] = coluna_inicial + i; break;
            case 'E': posicoes[i][0] = linha_inicial + i; posicoes[i][1] = coluna_inicial - i; break;
        }
    }
}

// Função para sobrepor uma matriz de habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[][5], int origem_linha, int origem_coluna) {
    int centro = 2; // centro da matriz 5x5
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha_tab = origem_linha - centro + i;
            int coluna_tab = origem_coluna - centro + j;

            if (linha_tab >= 0 && linha_tab < TAMANHO && coluna_tab >= 0 && coluna_tab < TAMANHO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] == AGUA) {
                    tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                }
            }
        }
    }
}

// Função para construir matriz em forma de cone (ponta para cima)
void construir_cone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (i >= j - 2 && i >= 2 - j && i <= 4); // forma de V invertido
        }
    }
}

// Função para construir matriz em forma de cruz
void construir_cruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (i == 2 || j == 2);
        }
    }
}

// Função para construir matriz em forma de octaedro (losango)
void construir_octaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (abs(i - 2) + abs(j - 2) <= 2);
        }
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro (0 = água | 3 = navio | 5 = habilidade):\n\n");
    printf("    ");
    for (int j = 0; j < TAMANHO; j++) printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    printf(">>> Nível MESTRE - Tabuleiro com habilidades especiais\n\n");

    // Criar e posicionar os navios
    int navio_horizontal[TAMANHO_NAVIO][2], navio_vertical[TAMANHO_NAVIO][2];
    int navio_diag_direita[TAMANHO_NAVIO][2], navio_diag_esquerda[TAMANHO_NAVIO][2];

    criar_navio(navio_horizontal, 2, 4, 'H');
    criar_navio(navio_vertical, 6, 1, 'V');
    criar_navio(navio_diag_direita, 0, 0, 'D');
    criar_navio(navio_diag_esquerda, 0, 9, 'E');

    if (pode_posicionar(tabuleiro, navio_horizontal, TAMANHO_NAVIO)) posicionar(tabuleiro, navio_horizontal, TAMANHO_NAVIO);
    if (pode_posicionar(tabuleiro, navio_vertical, TAMANHO_NAVIO)) posicionar(tabuleiro, navio_vertical, TAMANHO_NAVIO);
    if (pode_posicionar(tabuleiro, navio_diag_direita, TAMANHO_NAVIO)) posicionar(tabuleiro, navio_diag_direita, TAMANHO_NAVIO);
    if (pode_posicionar(tabuleiro, navio_diag_esquerda, TAMANHO_NAVIO)) posicionar(tabuleiro, navio_diag_esquerda, TAMANHO_NAVIO);

    // Criar habilidades e aplicar no tabuleiro
    int cone[5][5], cruz[5][5], octaedro[5][5];
    construir_cone(cone);
    construir_cruz(cruz);
    construir_octaedro(octaedro);

    aplicar_habilidade(tabuleiro, cone, 5, 5);      // Aplica cone no centro do tabuleiro
    aplicar_habilidade(tabuleiro, cruz, 8, 8);      // Aplica cruz no canto inferior direito
    aplicar_habilidade(tabuleiro, octaedro, 3, 3);  // Aplica octaedro na parte superior esquerda

    // Exibir tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}

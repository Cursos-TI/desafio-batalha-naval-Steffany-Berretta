#include <stdio.h>

// Tamanho do tabuleiro (10x10)
#define TAMANHO 10

// Tamanho fixo dos navios (3 células)
#define TAMANHO_NAVIO 3

// Valor usado para representar um navio no tabuleiro
#define NAVIO 3

// Valor que representa água (espaço vazio)
#define AGUA 0

// Função para verificar se um navio pode ser colocado nas posições informadas
int pode_posicionar(int tabuleiro[TAMANHO][TAMANHO], int posicoes[][2], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];

        // Verifica se está fora do tabuleiro
        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
            return 0; // Não pode posicionar
        }

        // Verifica se já tem outro navio na posição
        if (tabuleiro[linha][coluna] != AGUA) {
            return 0;
        }
    }

    return 1; // Está tudo certo, pode posicionar
}

// Função que posiciona um navio no tabuleiro e imprime suas coordenadas
void posicionar(int tabuleiro[TAMANHO][TAMANHO], int posicoes[][2], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];

        tabuleiro[linha][coluna] = NAVIO;

        // Mostra onde foi colocado
        printf("(%d, %d)\n", linha, coluna);
    }
}

int main() {
    // Cria o tabuleiro todo cheio de água (0)
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    printf(">>> Nível AVENTUREIRO - Posicionando 4 navios\n\n");

    // ==============================
    // 1. Navio na horizontal (→)
    // ==============================
    int navio_horizontal[TAMANHO_NAVIO][2] = {
        {2, 4}, {2, 5}, {2, 6}
    };

    if (pode_posicionar(tabuleiro, navio_horizontal, TAMANHO_NAVIO)) {
        printf("Navio HORIZONTAL:\n");
        posicionar(tabuleiro, navio_horizontal, TAMANHO_NAVIO);
    } else {
        printf("Erro: não foi possível posicionar o navio horizontal.\n");
        return 1;
    }

    // ==============================
    // 2. Navio na vertical (↓)
    // ==============================
    int navio_vertical[TAMANHO_NAVIO][2] = {
        {6, 1}, {7, 1}, {8, 1}
    };

    if (pode_posicionar(tabuleiro, navio_vertical, TAMANHO_NAVIO)) {
        printf("\nNavio VERTICAL:\n");
        posicionar(tabuleiro, navio_vertical, TAMANHO_NAVIO);
    } else {
        printf("Erro: não foi possível posicionar o navio vertical.\n");
        return 1;
    }

    // ==============================
    // 3. Navio na diagonal ↘
    // ==============================
    int navio_diagonal_direita[TAMANHO_NAVIO][2] = {
        {0, 0}, {1, 1}, {2, 2}
    };

    if (pode_posicionar(tabuleiro, navio_diagonal_direita, TAMANHO_NAVIO)) {
        printf("\nNavio DIAGONAL ↘:\n");
        posicionar(tabuleiro, navio_diagonal_direita, TAMANHO_NAVIO);
    } else {
        printf("Erro: não foi possível posicionar o navio diagonal ↘.\n");
        return 1;
    }

    // ==============================
    // 4. Navio na diagonal ↙
    // ==============================
    int navio_diagonal_esquerda[TAMANHO_NAVIO][2] = {
        {0, 9}, {1, 8}, {2, 7}
    };

    if (pode_posicionar(tabuleiro, navio_diagonal_esquerda, TAMANHO_NAVIO)) {
        printf("\nNavio DIAGONAL ↙:\n");
        posicionar(tabuleiro, navio_diagonal_esquerda, TAMANHO_NAVIO);
    } else {
        printf("Erro: não foi possível posicionar o navio diagonal ↙.\n");
        return 1;
    }

    // ==============================
    // Exibir o tabuleiro completo
    // ==============================
    printf("\nTabuleiro final (0 = água | 3 = navio):\n\n");

    for (int linha = 0; linha < TAMANHO; linha++) {
        for (int coluna = 0; coluna < TAMANHO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}

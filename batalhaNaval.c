#include <stdio.h>

#define TAMANHO 10             // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3        // Cada navio ocupa 3 posições
#define NAVIO 3                // Valor que representa um navio no tabuleiro
#define AGUA 0                 // Valor que representa água

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
// Direções: 'H' = horizontal, 'V' = vertical, 'D' = diagonal ↘, 'E' = diagonal ↙
void criar_navio(int posicoes[][2], int linha_inicial, int coluna_inicial, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        switch (direcao) {
            case 'H':
                posicoes[i][0] = linha_inicial;
                posicoes[i][1] = coluna_inicial + i;
                break;
            case 'V':
                posicoes[i][0] = linha_inicial + i;
                posicoes[i][1] = coluna_inicial;
                break;
            case 'D':
                posicoes[i][0] = linha_inicial + i;
                posicoes[i][1] = coluna_inicial + i;
                break;
            case 'E':
                posicoes[i][0] = linha_inicial + i;
                posicoes[i][1] = coluna_inicial - i;
                break;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0}; // Inicializa o tabuleiro com água (0)

    printf(">>> Nível AVENTUREIRO - Posicionando 4 navios\n\n");

    // Definição dos navios com coordenadas geradas por função
    int navio_horizontal[TAMANHO_NAVIO][2];
    int navio_vertical[TAMANHO_NAVIO][2];
    int navio_diag_direita[TAMANHO_NAVIO][2];
    int navio_diag_esquerda[TAMANHO_NAVIO][2];

    criar_navio(navio_horizontal, 2, 4, 'H');     // (2,4) até (2,6)
    criar_navio(navio_vertical, 6, 1, 'V');       // (6,1) até (8,1)
    criar_navio(navio_diag_direita, 0, 0, 'D');   // (0,0) até (2,2)
    criar_navio(navio_diag_esquerda, 0, 9, 'E');  // (0,9) até (2,7)

    // Posicionamento com validação
    if (pode_posicionar(tabuleiro, navio_horizontal, TAMANHO_NAVIO)) {
        printf("Navio HORIZONTAL:\n");
        posicionar(tabuleiro, navio_horizontal, TAMANHO_NAVIO);
    } else {
        printf("Erro: navio horizontal inválido.\n");
    }

    if (pode_posicionar(tabuleiro, navio_vertical, TAMANHO_NAVIO)) {
        printf("\nNavio VERTICAL:\n");
        posicionar(tabuleiro, navio_vertical, TAMANHO_NAVIO);
    } else {
        printf("Erro: navio vertical inválido.\n");
    }

    if (pode_posicionar(tabuleiro, navio_diag_direita, TAMANHO_NAVIO)) {
        printf("\nNavio DIAGONAL ↘:\n");
        posicionar(tabuleiro, navio_diag_direita, TAMANHO_NAVIO);
    } else {
        printf("Erro: navio diagonal ↘ inválido.\n");
    }

    if (pode_posicionar(tabuleiro, navio_diag_esquerda, TAMANHO_NAVIO)) {
        printf("\nNavio DIAGONAL ↙:\n");
        posicionar(tabuleiro, navio_diag_esquerda, TAMANHO_NAVIO);
    } else {
        printf("Erro: navio diagonal ↙ inválido.\n");
    }

    // Exibir o tabuleiro com coordenadas
    printf("\nTabuleiro final (0 = água | 3 = navio):\n\n");

    // Cabeçalho das colunas
    printf("    ");
    for (int j = 0; j < TAMANHO; j++) printf("%2d ", j);
    printf("\n");

    // Conteúdo do tabuleiro
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // Total de partes ocupadas por navios
    int total_navios = 0;
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            if (tabuleiro[i][j] == NAVIO)
                total_navios++;

    printf("\nTotal de partes de navios no tabuleiro: %d\n", total_navios);

    return 0;
}

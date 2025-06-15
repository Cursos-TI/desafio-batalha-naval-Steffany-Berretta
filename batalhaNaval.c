#include <stdio.h>

// Definições de constantes para facilitar manutenção e compreensão
#define TAMANHO 10         // Tamanho do tabuleiro: 10x10
#define TAMANHO_NAVIO 3    // Tamanho fixo dos navios (3 posições)
#define NAVIO 3            // Valor usado para representar a presença de um navio no tabuleiro
#define AGUA 0             // Valor padrão do tabuleiro (representa água)

int main() {
    // Declaração e inicialização do tabuleiro 10x10 com água (0 em todas as posições)
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Coordenadas iniciais do navio horizontal (linha, coluna)
    // O navio será colocado da esquerda para a direita
    int linha_horizontal = 2;
    int coluna_horizontal = 5;

    // Coordenadas iniciais do navio vertical (linha, coluna)
    // O navio será colocado de cima para baixo
    int linha_vertical = 6;
    int coluna_vertical = 3;

    // Mensagem inicial indicando início do processo de posicionamento
    printf(">>> Posicionando navios no nível NOVATO (tabuleiro 10x10)\n\n");

    // ============================ //
    // POSICIONAMENTO DO NAVIO HORIZONTAL
    // ============================ //

    // Verifica se o navio horizontal cabe na linha escolhida sem ultrapassar os limites da matriz
    if (coluna_horizontal + TAMANHO_NAVIO <= TAMANHO) {
        printf("Coordenadas do navio HORIZONTAL:\n");

        // Laço que percorre as 3 posições do navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Marca a célula como ocupada por um navio (valor 3)
            tabuleiro[linha_horizontal][coluna_horizontal + i] = NAVIO;

            // Exibe as coordenadas ocupadas
            printf("(%d, %d)\n", linha_horizontal, coluna_horizontal + i);
        }
    } else {
        // Mensagem de erro se o navio não couber
        printf("Erro: navio horizontal não cabe no tabuleiro.\n");
        return 1; // Encerra o programa com erro
    }

    // ============================ //
    // POSICIONAMENTO DO NAVIO VERTICAL
    // ============================ //

    // Verifica se o navio vertical cabe na coluna escolhida sem ultrapassar os limites da matriz
    if (linha_vertical + TAMANHO_NAVIO <= TAMANHO) {
        int sobreposicao = 0; // Variável para verificar se há colisão com outro navio

        // Verifica se alguma das posições já está ocupada
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_vertical + i][coluna_vertical] != AGUA) {
                sobreposicao = 1;
                break; // Interrompe o laço se encontrar sobreposição
            }
        }

        // Se não há sobreposição, posiciona o navio vertical
        if (!sobreposicao) {
            printf("\nCoordenadas do navio VERTICAL:\n");

            // Posiciona o navio vertical ocupando 3 linhas
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_vertical + i][coluna_vertical] = NAVIO;
                printf("(%d, %d)\n", linha_vertical + i, coluna_vertical);
            }
        } else {
            // Mensagem de erro se houver colisão com outro navio
            printf("Erro: sobreposição entre navios detectada.\n");
            return 1;
        }
    } else {
        // Mensagem de erro se o navio não couber
        printf("Erro: navio vertical não cabe no tabuleiro.\n");
        return 1;
    }

    // ============================ //
    // EXIBIÇÃO DO TABULEIRO FINAL
    // ============================ //

    printf("\nTabuleiro final (0 = água | 3 = navio):\n\n");

    // Laço externo percorre as linhas
    for (int i = 0; i < TAMANHO; i++) {
        // Laço interno percorre as colunas
        for (int j = 0; j < TAMANHO; j++) {
            // Exibe o conteúdo da célula: 0 (água) ou 3 (navio)
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Quebra de linha ao final de cada linha da matriz
    }

    // Fim da execução
    return 0;
}

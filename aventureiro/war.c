#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==============================
// 🧩 Estrutura de Dados
// ==============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==============================
// 📦 Funções do Sistema
// ==============================

// Cadastra os territórios dinamicamente
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o buffer
    }
}

// Exibe o estado atual do mapa
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] %s\n", i + 1, mapa[i].nome);
        printf("   Cor: %s\n", mapa[i].cor);
        printf("   Tropas: %d\n", mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n⚔️  %s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Rolagem dos dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("🎲 Dado do Atacante: %d\n", dadoAtacante);
    printf("🛡️  Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("🔥 Ataque bem-sucedido!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
        printf("🏳️ %s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);
    } else {
        printf("💥 O ataque falhou! %s perdeu uma tropa.\n", atacante->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Libera a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}

// ==============================
// 🚀 Função Principal
// ==============================
int main() {
    srand(time(NULL)); // inicializa aleatoriedade

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar(); // limpa o buffer

    // Alocação dinâmica
    Territorio* mapa = (Territorio*)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        exibirMapa(mapa, qtd);

        printf("\nDeseja simular um ataque? (1 - Sim | 0 - Sair): ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int iAtacante, iDefensor;
            printf("Escolha o território atacante (1-%d): ", qtd);
            scanf("%d", &iAtacante);
            getchar();

            printf("Escolha o território defensor (1-%d): ", qtd);
            scanf("%d", &iDefensor);
            getchar();

            // Valida índices e se é possível atacar
            if (iAtacante < 1 || iAtacante > qtd || iDefensor < 1 || iDefensor > qtd) {
                printf("❌ Índice inválido!\n");
                continue;
            }
            if (strcmp(mapa[iAtacante - 1].cor, mapa[iDefensor - 1].cor) == 0) {
                printf("⚠️  Você não pode atacar um território da mesma cor!\n");
                continue;
            }

            atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

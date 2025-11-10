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
// ⚙️ Protótipos das Funções
// ==============================
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirMapa(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char* missaoJogador1, char* missaoJogador2);

void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(const char* missao);

// ==============================
// 🗺️ Cadastro dos Territórios
// ==============================
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
        getchar();
    }
}

// ==============================
// 🗺️ Exibir o Estado Atual do Mapa
// ==============================
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\n[%d] %s\n", i + 1, mapa[i].nome);
        printf("   Cor: %s\n", mapa[i].cor);
        printf("   Tropas: %d\n", mapa[i].tropas);
    }
}

// ==============================
// ⚔️ Função de Ataque
// ==============================
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n⚔️  %s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

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

// ==============================
// 🎯 Atribuição de Missão
// ==============================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// ==============================
// 🔍 Verificação de Missão
// ==============================
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // ⚠️ Versão simples de lógica de vitória
    // Pode ser expandida conforme o jogo evolui.
    if (strstr(missao, "conquistar") != NULL) {
        // Verifica se jogador possui mais da metade dos territórios
        int contDominio = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                contDominio++;
        }
        if (contDominio >= tamanho / 2)
            return 1;
    } else if (strstr(missao, "eliminar") != NULL) {
        // Verifica se cor vermelha ainda existe
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
                return 0;
        }
        return 1;
    }
    return 0;
}

// ==============================
// 👁️ Exibir Missão (uma vez)
// ==============================
void exibirMissao(const char* missao) {
    printf("\n🎯 Sua missão secreta é:\n%s\n", missao);
}

// ==============================
// 🧹 Liberação de Memória
// ==============================
void liberarMemoria(Territorio* mapa, char* missaoJogador1, char* missaoJogador2) {
    free(mapa);
    free(missaoJogador1);
    free(missaoJogador2);
    printf("\nMemória liberada com sucesso.\n");
}

// ==============================
// 🚀 Função Principal
// ==============================
int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar();

    Territorio* mapa = (Territorio*)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    // 🎯 Vetor de Missões
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor Vermelha",
        "Controlar metade do mapa",
        "Ter mais de 20 tropas no total",
        "Conquistar dois territórios da cor Verde"
    };
    int totalMissoes = 5;

    // 🎮 Alocação dinâmica das missões dos jogadores
    char* missaoJogador1 = (char*)malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*)malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n=== JOGO INICIADO ===\n");
    printf("\n🔵 Jogador 1 (Azul)");
    exibirMissao(missaoJogador1);

    printf("\n🔴 Jogador 2 (Vermelho)");
    exibirMissao(missaoJogador2);

    int turno = 1, opcao;
    do {
        exibirMapa(mapa, qtd);

        printf("\n--- TURNO %d ---\n", turno);
        printf("Deseja simular um ataque? (1 - Sim | 0 - Sair): ");
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

            if (iAtacante < 1 || iAtacante > qtd || iDefensor < 1 || iDefensor > qtd) {
                printf("❌ Índice inválido!\n");
                continue;
            }

            if (strcmp(mapa[iAtacante - 1].cor, mapa[iDefensor - 1].cor) == 0) {
                printf("⚠️  Você não pode atacar um território da mesma cor!\n");
                continue;
            }

            atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);

            // ✅ Verifica se algum jogador cumpriu sua missão
            if (verificarMissao(missaoJogador1, mapa, qtd)) {
                printf("\n🏆 Jogador 1 (Azul) completou sua missão e venceu o jogo!\n");
                break;
            }
            if (verificarMissao(missaoJogador2, mapa, qtd)) {
                printf("\n🏆 Jogador 2 (Vermelho) completou sua missão e venceu o jogo!\n");
                break;
            }
        }

        turno++;
    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    return 0;
}

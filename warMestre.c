#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define NUM_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 15
#define MAX_MISSAO 100

// --- Definição das Estruturas ---
struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
void esperarEnter();
void exibirMenu();
void cadastrarTerritorios(struct Territorio *mapa, int quantidade);
void exibirMapa(const struct Territorio *mapa, int quantidade);
void realizarAtaque(struct Territorio *mapa, int quantidade, const char *minhaCor);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void verificarMissaoJogador(const char *minhaMissao, struct Territorio *mapa, int tamanho, int *jogoAtivo);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
void exibirMissaoJogador(const char *corJogador, const char *missao);
int verificarMissao(const char *missao, struct Territorio *mapa, int tamanho);
void liberarMemoria(struct Territorio *mapa, char *missao);

// --- Função Principal ---
int main() {
    srand(time(NULL));

    struct Territorio *mapa = (struct Territorio *) calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    char *minhaMissao = (char *) malloc(MAX_MISSAO * sizeof(char));

    if (mapa == NULL || minhaMissao == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    printf("Vamos cadastrar os %d territorios do nosso mundo!\n\n", NUM_TERRITORIOS);
    cadastrarTerritorios(mapa, NUM_TERRITORIOS);

    // Missões possíveis
    char *missoes[] = {
        "Destruir o exercito Verde.",
        "Conquistar 3 territorios.",
        "Eliminar o exercito Vermelho.",
        "Dominar todos os territorios com mais de 2 tropas.",
        "Controlar 2 territorios seguidos."
    };
    int totalMissoes = 5;

    atribuirMissao(minhaMissao, missoes, totalMissoes);
    char minhaCor[] = "Azul";

    int opcao;
    int jogoAtivo = 1;

    do {
        exibirMapa(mapa, NUM_TERRITORIOS);
        exibirMissaoJogador(minhaCor, minhaMissao);
        exibirMenu();

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: // ATACAR
                realizarAtaque(mapa, NUM_TERRITORIOS, minhaCor);
                break;

            case 2: // VERIFICAR MISSAO
                verificarMissaoJogador(minhaMissao, mapa, NUM_TERRITORIOS, &jogoAtivo);
                break;

            case 0: // SAIR
                printf("\nSaindo do jogo...\n");
                break;

            default: // OPÇÃO INVÁLIDA
                printf("\nOpcao invalida! Tente novamente.\n");
                esperarEnter();
                break;
        }
    } while (opcao != 0 && jogoAtivo);

    liberarMemoria(mapa, minhaMissao);
    printf("\nJogo encerrado. Obrigado por jogar!\n");
    return 0;
}

// --- Implementação das Funções ---

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void esperarEnter() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void exibirMenu() {
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha sua acao: ");
}

/**
 * @brief Cadastra os territórios do mapa.
 * @param mapa Array de territórios (modificável).
 * @param quantidade Número de territórios a cadastrar.
 */
void cadastrarTerritorios(struct Territorio *mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

/**
 * @brief Exibe o estado atual do mapa.
 * @param mapa Array de territórios (leitura).
 * @param quantidade Número de territórios.
 */
void exibirMapa(const struct Territorio *mapa, int quantidade) {
    printf("\n================= MAPA DO MUNDO =================\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %-10s (Exercito: %-8s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=================================================\n");
}

/**
 * @brief Realiza a fase de ataque entre territórios.
 * @param mapa Array de territórios (modificável).
 * @param quantidade Número de territórios.
 * @param minhaCor Cor do exército do jogador.
 */
void realizarAtaque(struct Territorio *mapa, int quantidade, const char *minhaCor) {
    int atacante, defensor;
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (1 a %d): ", quantidade);
    scanf("%d", &atacante);
    printf("Escolha o territorio defensor (1 a %d): ", quantidade);
    scanf("%d", &defensor);
    limparBufferEntrada();

    if (atacante < 1 || defensor < 1 || 
        atacante > quantidade || defensor > quantidade || 
        atacante == defensor) {
        printf("Escolha invalida!\n");
    } else if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
        printf("Nao pode atacar territorios do mesmo exercito!\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
    }
    esperarEnter();
}

/**
 * @brief Executa a batalha entre atacante e defensor.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atacante->nome, dadoAtacante,
           defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", 
                   defensor->nome, defensor->cor);
        }
    } else if (dadoAtacante == dadoDefensor) {
        printf("EMPATE! O defensor manteve o controle do territorio.\n");
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}

/**
 * @brief Verifica se o jogador cumpriu sua missão.
 * @param minhaMissao String com a missão do jogador.
 * @param mapa Array de territórios.
 * @param tamanho Número de territórios.
 * @param jogoAtivo Ponteiro para controlar se o jogo continua.
 */
void verificarMissaoJogador(const char *minhaMissao, struct Territorio *mapa, int tamanho, int *jogoAtivo) {
    if (verificarMissao(minhaMissao, mapa, tamanho)) {
        printf("\nPARABENS! Voce cumpriu sua missao!\n");
        *jogoAtivo = 0;
    } else {
        printf("\nMissao ainda nao concluida.\n");
    }
    esperarEnter();
}

/**
 * @brief Atribui uma missão aleatória ao jogador.
 * @param destino String onde a missão será armazenada.
 * @param missoes Array com as missões possíveis.
 * @param totalMissoes Número total de missões disponíveis.
 */
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/**
 * @brief Exibe a missão do jogador.
 * @param corJogador Cor do exército do jogador.
 * @param missao String com a missão.
 */
void exibirMissaoJogador(const char *corJogador, const char *missao) {
    printf("\n--- SUA MISSAO (Exercito %s) ---\n", corJogador);
    printf("%s\n", missao);
}

/**
 * @brief Verifica se uma missão específica foi cumprida.
 * @param missao String com a missão a verificar.
 * @param mapa Array de territórios.
 * @param tamanho Número de territórios.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(const char *missao, struct Territorio *mapa, int tamanho) {
    if (strstr(missao, "Destruir o exercito Verde") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Libera a memória alocada dinamicamente.
 * @param mapa Ponteiro para o array de territórios.
 * @param missao Ponteiro para a string de missão.
 */
void liberarMemoria(struct Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
    printf("Memoria liberada com sucesso.\n");
}
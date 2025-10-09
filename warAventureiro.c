#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define MAX_TERRITORIOS 50
#define TAM_STRING 30

// --- Definição da Estrutura ---
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {
    srand(time(NULL)); // inicializa os números aleatórios

    // 1. ALOCAÇÃO DINÂMICA DE MEMÓRIA
    struct Territorio *mapa;
    
    mapa = (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));
    
    // VERIFICAÇÃO: É crucial verificar se a alocação de memória deu certo.
    if (mapa == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }
    
    int numTerritorios = 5;
    int opcao;
    
    // CADASTRO INICIAL DOS TERRITÓRIOS
    printf("Vamos cadastrar os 5 territorios do nosso mundo!\n\n");
    
    for (int i = 0; i < numTerritorios; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        scanf("%s", mapa[i].nome);
        
        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", mapa[i].cor);
        
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
        
        printf("\n");
    }

    // LOOP DE TURNOS
    do {
        // EXIBIR MAPA ATUAL
        printf("===================================\n");
        printf("    MAPA DO MUNDO - ESTADO ATUAL   \n");
        printf("===================================\n");
        for (int i = 0; i < numTerritorios; i++) {
            printf("%d. %s (Exercito %s, Tropas: %d)\n", 
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        printf("\n");

        // FASE DE ATAQUE
        printf("--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", numTerritorios);
        scanf("%d", &opcao);
        limparBufferEntrada();
        
        if (opcao == 0) {
            break;
        }
        
        int atacante = opcao;
        int defensor;
        
        printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
        scanf("%d", &defensor);
        limparBufferEntrada();

        // VERIFICAÇÕES DE ERRO
        if (atacante == defensor || atacante < 1 || defensor < 1 || 
            atacante > numTerritorios || defensor > numTerritorios) {
            printf("Escolha invalida! Tente novamente.\n");
            printf("Pressione Enter para continuar para o proximo turno...");
            getchar();
            continue;
        }

        if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
            printf("Nao e possivel atacar um territorio do mesmo exercito!\n");
            printf("Pressione Enter para continuar para o proximo turno...");
            getchar();
            continue;
        }

        // REALIZA O ATAQUE
        int dadoAtacante = (rand() % 6) + 1;
        int dadoDefensor = (rand() % 6) + 1;

        printf("\n--- RESULTADO DA BATALHA ---\n");
        printf("O atacante %s rolou um dado e tirou: %d\n", 
               mapa[atacante - 1].nome, dadoAtacante);
        printf("O defensor %s rolou um dado e tirou: %d\n", 
               mapa[defensor - 1].nome, dadoDefensor);

        if (dadoAtacante > dadoDefensor) {
            printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
            mapa[defensor - 1].tropas--;

            if (mapa[defensor - 1].tropas <= 0) {
                strcpy(mapa[defensor - 1].cor, mapa[atacante - 1].cor);
                mapa[defensor - 1].tropas = 1;
                printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", 
                       mapa[defensor - 1].nome, mapa[defensor - 1].cor);
            }
        } else {
            if (dadoAtacante == dadoDefensor) {
                printf("EMPATE! O defensor manteve o controle do territorio.\n");
            } else {
                printf("DEFESA BEM-SUCEDIDA! O exercito defensor venceu o ataque.\n");
            }
            mapa[atacante - 1].tropas--;
            printf("O exercito atacante (%s) perdeu 1 tropa.\n", 
                   mapa[atacante - 1].nome);
        }

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar();
        
    } while (opcao != 0);

    // LIBERAR MEMÓRIA
    free(mapa);
    
    printf("\nJogo encerrado. Obrigado por jogar!\n");
    printf("Memoria liberada com sucesso.\n");
    
    return 0;
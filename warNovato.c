#include <stdio.h>

char nometerritorio1[50], nometerritorio2[50], nometerritorio3[50], nometerritorio4[50], nometerritorio5[50];
char corexercito1[20], corexercito2[20], corexercito3[20], corexercito4[20], corexercito5[20];
int numtropa1, numtropa2, numtropa3, numtropa4, numtropa5;

int main() {
    printf("Vamos cadastras os 5 territorios iniciais do nosso mundo.\n\n");
    // Territorio 1
    printf("--- Cadastrando Territorio 1 ---\n");
    printf("Nome do Territorio:  ", nometerritorio1);
    scanf("%s", &nometerritorio1);
    printf("Cor do Exercito(ex: Azul, Verde): ", nometerritorio1);
    scanf("%s", &corexercito1);
    printf("Numero de tropas: ", numtropa1);
    scanf("%d",&numtropa1);
    printf("\n");

    // Territorio 2
    printf("--- Cadastrando Territorio 2 ---\n");
    printf("Nome do Territorio:  ", nometerritorio2);
    scanf("%s", &nometerritorio2);
    printf("Cor do Exercito(ex: Azul, Verde): ", nometerritorio2);
    scanf("%s", &corexercito2);
    printf("Numero de tropas: ", numtropa2);
    scanf("%d",&numtropa2);
    printf("\n");

    // Territorio 3
    printf("--- Cadastrando Territorio 3 ---\n");
    printf("Nome do Territorio:  ", nometerritorio3);
    scanf("%s", &nometerritorio3);
    printf("Cor do Exercito(ex: Azul, Verde): ", nometerritorio3);
    scanf("%s", &corexercito3);
    printf("Numero de tropas: ", numtropa3);
    scanf("%d",&numtropa3);
    printf("\n");

    // Territorio 4
    printf("--- Cadastrando Territorio 4 ---\n");
    printf("Nome do Territorio: ", nometerritorio4);
    scanf("%s", &nometerritorio4);
    printf("Cor do Exercito(ex: Azul, Verde): ", nometerritorio4);
    scanf("%s", &corexercito4);
    printf("Numero de tropas: ", numtropa4);
    scanf("%d",&numtropa4);
    printf("\n");

    // Territorio 5
     printf("--- Cadastrando Territorio 5 ---\n");
    printf("Nome do Territorio:  ", nometerritorio5);
    scanf("%s", &nometerritorio5);
    printf("Cor do Exercito(ex: Azul, Verde): ", nometerritorio5);
    scanf("%s", &corexercito5);
    printf("Numero de tropas: ", numtropa5);
    scanf("%d",&numtropa5);
    printf("\n");

    // Mostrando Resultados

    printf("===================================\n");
    printf("    MAPA DO MUNDO ATUAL     \n");
    printf("===================================\n");
    printf("\n");

    printf("TERRITORIO 1:\n");
    printf("- Nome: %s\n", nometerritorio1);
    printf("- Dominado por: Exercito %s\n", corexercito1);
    printf("- Tropas: %d\n", numtropa1);
    printf("\n");

    printf("TERRITORIO 2:\n");
    printf("  - Nome: %s\n", nometerritorio2);
    printf("  - Dominado por: Exercito %s\n", corexercito2);
    printf("  - Tropas: %d\n", numtropa2);
    printf("\n");

    printf("TERRITORIO 3:\n");
    printf("  - Nome: %s\n", nometerritorio3);
    printf("  - Dominado por: Exercito %s\n", corexercito3);
    printf("  - Tropas: %d\n", numtropa3);
    printf("\n");

    printf("TERRITORIO 4:\n");
    printf("  - Nome: %s\n", nometerritorio4);
    printf("  - Dominado por: Exercito %s\n", corexercito4);
    printf("  - Tropas: %d\n", numtropa4);
    printf("\n");

    printf("TERRITORIO 5:\n");
    printf("  - Nome: %s\n", nometerritorio5);
    printf("  - Dominado por: Exercito %s\n", corexercito5);
    printf("  - Tropas: %d\n", numtropa5);
     printf("\n");

    return 0;
}


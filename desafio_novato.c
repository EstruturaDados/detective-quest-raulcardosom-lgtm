//Desafio detetive novato

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



struct Sala {
    
    char nome [60];
    struct Sala *esquerda;
    struct Sala *direita;
};



struct Sala* criarSala(char* nome) {

    struct Sala* nova_sala = (struct Sala*) malloc (sizeof(struct Sala));



    strcpy(nova_sala -> nome, nome);



    nova_sala->esquerda = NULL;

    nova_sala->direita = NULL;



    return nova_sala;

};



int main() {

    struct Sala* raiz = criarSala("Hall de Entrada");



    printf ("Conectando Hall de entrada -> Sala de Jantar (Esquerda)\n");

    raiz->esquerda = criarSala("Sala de Jantar");



    printf ("Hall de entrada -> Biblioteca (Direita)\n");

    raiz->direita = criarSala("Biblioteca");



    printf ("Conectando Sala de Jantar -> Cozinha (Esquerda)\n");

    raiz->direita->esquerda = criarSala("Cozinha");



    printf ("Conectando Biblioteca -> Escritorio (Esquerda)\n");

    raiz->direita->esquerda = criarSala("Escritorio");



    printf ("Conectando Biblioteca -> Jardim (Direita)\n");

    raiz->direita->direita = criarSala("Jardim");



    printf("\nMansao construida com sucesso!\n");


    return 0;
}

void explorarSalas(struct Sala* sala_atual) {
    char escolha;

    while (sala_atual->esquerda !=NULL || sala_atual->direita !=NULL) {
        printf("\nVoce esta em: %s\n", sala_atual->nome);
        printf("Para onde voce quer ir? (e --> esquerda, d --> direita, s --> sair)");
        scanf("%c", &escolha);

        if (escolha == 'e') {
            if (sala_atual->esquerda != NULL) {
                sala_atual = sala_atual->esquerda;
            } else {
                printf (">> PAREDE! Nao ha caminho para a direita <<\n");
            }
        }
        else if (escolha == 'd') {
            if (sala_atual->direita != NULL) {
                sala_atual = sala_atual->direita; 
            } else {
                printf (">> PAREDE! Nao ha caminho para a direita.\n");
            }
        }
        else if (escolha == 's') {
            printf("Voce decidiu para a exploracao.\n");
            return;
        } else {
            printf("Comando invalido!\n");
        }
    }

    printf("\nVoce chegou em: %s\n", sala_atual->nome);
    printf("Fim do caminho! Este e um beco sem saida.\n");
}
// Desafio detetive novato 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
};

struct Sala* criarSala(char* nome);
void explorarSalas(struct Sala* sala_inicial);
void liberarMapa(struct Sala* sala_atual);

int main() {
    struct Sala* raiz = criarSala("Hall de Entrada");
    raiz->esquerda = criarSala("Sala de Jantar");
    raiz->direita = criarSala("Biblioteca");
    raiz->esquerda->esquerda = criarSala("Cozinha");
    raiz->direita->direita = criarSala("Jardim");
    raiz->direita->esquerda = criarSala("Escritorio");

    printf("=============================================\n");
    printf("         Bem-vindo ao Detective Quest!       \n");
    printf("=============================================\n");
    printf("--- MAPA DA MANSAO ---\n\n");
    printf("                       [Hall de Entrada]\n");
    printf("                      /                 \\\n");
    printf("           [Sala de Jantar]           [Biblioteca]\n");
    printf("           /                           /          \\\n");
    printf("       [Cozinha]                   [Escritorio]   [Jardim]\n\n");
    
    explorarSalas(raiz);

    printf("\nObrigado por jogar!\n");
    
    liberarMapa(raiz);
    
    return 0;
}

struct Sala* criarSala(char* nome) {
    struct Sala* nova_sala = (struct Sala*) malloc(sizeof(struct Sala));
    strcpy(nova_sala->nome, nome);
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
}

void explorarSalas(struct Sala* sala_atual) {
    char escolha;

    while (1) {
        printf("\n---------------------------------------------\n");
        printf("Voce esta em: %s\n", sala_atual->nome);

        if (sala_atual->esquerda == NULL && sala_atual->direita == NULL) {
            printf("Fim do caminho! Este e um beco sem saida.\n");
            printf("Fim da exploracao.\n");
            break;
        }

        printf("Para onde voce quer ir? (e -> esquerda, d -> direita, s -> sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (sala_atual->esquerda != NULL) {
                sala_atual = sala_atual->esquerda;
            } else {
                printf(">> PAREDE! Nao ha caminho para a esquerda.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (sala_atual->direita != NULL) {
                sala_atual = sala_atual->direita;
            } else {
                printf(">> PAREDE! Nao ha caminho para a direita.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("Voce decidiu parar a exploracao.\n");
            return;
        } else {
            printf("Comando invalido!\n");
        }
    }
}

void liberarMapa(struct Sala* sala_atual) {
    if (sala_atual == NULL) {
        return;
    }
    liberarMapa(sala_atual->esquerda);
    liberarMapa(sala_atual->direita);
    free(sala_atual);
}
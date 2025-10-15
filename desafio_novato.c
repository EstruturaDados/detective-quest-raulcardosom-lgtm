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

    printf ("conectando Sala de Jantar -> Cozinha (esquerda)\n");
    raiz->direita->
}
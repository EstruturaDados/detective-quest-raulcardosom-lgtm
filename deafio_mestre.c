//Desafio detetive mestre
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 10

struct Sala {
    char nome[50];
    char* pista;
    struct Sala *esquerda;
    struct Sala *direita;
};

struct PistaNode {
    char* pista;
    struct PistaNode *esquerda;
    struct PistaNode *direita;
};

struct HashNode {
    char* pista;
    char* suspeito;
    struct HashNode* proximo;
};

struct HashTable {
    struct HashNode* baldes[HASH_TABLE_SIZE];
};

struct Sala* criarSala(char* nome, char* pista);
void explorarSalas(struct Sala* sala_inicial, struct PistaNode** pistas_raiz);
struct PistaNode* inserirPista(struct PistaNode* raiz, char* pista);
unsigned int hash(char* pista);
void inserirNaHash(struct HashTable* tabela, char* pista, char* suspeito);
char* encontrarSuspeito(struct HashTable* tabela, char* pista);
void contarPistas(struct PistaNode* pistas, char* suspeitoAcusado, struct HashTable* tabela, int* contador);
void verificarSuspeitoFinal(struct PistaNode* pistas_coletadas, struct HashTable* tabela);
void liberarMapa(struct Sala* sala);
void liberarPistas(struct PistaNode* pistas);
void liberarHash(struct HashTable* tabela);
void strToLower(char *str);

int main() {
    struct Sala* raiz = criarSala("Hall de Entrada", "Um casaco molhado perto da porta.");
    raiz->esquerda = criarSala("Sala de Jantar", "Um prato quebrado com um monograma estranho.");
    raiz->direita = criarSala("Biblioteca", "Um livro de venenos fora do lugar.");
    raiz->esquerda->esquerda = criarSala("Cozinha", "Uma faca de cozinha desaparecida.");
    raiz->direita->direita = criarSala("Jardim", "Pegadas de botas sujas de terra.");
    raiz->direita->esquerda = criarSala("Escritorio", "Uma carta amassada na lareira.");

    struct PistaNode* pistas_coletadas = NULL;

    struct HashTable tabela_de_suspeitos;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        tabela_de_suspeitos.baldes[i] = NULL;
    }

    inserirNaHash(&tabela_de_suspeitos, "Um livro de venenos fora do lugar.", "mordomo");
    inserirNaHash(&tabela_de_suspeitos, "Uma carta amassada na lareira.", "mordomo");
    inserirNaHash(&tabela_de_suspeitos, "Uma faca de cozinha desaparecida.", "cozinheira");
    inserirNaHash(&tabela_de_suspeitos, "Um prato quebrado com um monograma estranho.", "cozinheira");
    inserirNaHash(&tabela_de_suspeitos, "Pegadas de botas sujas de terra.", "jardineiro");
    inserirNaHash(&tabela_de_suspeitos, "Um casaco molhado perto da porta.", "jardineiro");

    printf("====================================================\n");
    printf("        Bem-vindo ao Detective Quest: O Ato Final   \n");
    printf("====================================================\n");

    printf("--- MAPA DA MANSAO ---\n\n");
    printf("                       [Hall de Entrada]\n");
    printf("                      /                 \\\n");
    printf("           [Sala de Jantar]           [Biblioteca]\n");
    printf("           /                           /          \\\n");
    printf("       [Cozinha]                   [Escritorio]   [Jardim]\n\n");
    
    explorarSalas(raiz, &pistas_coletadas);
    
    verificarSuspeitoFinal(pistas_coletadas, &tabela_de_suspeitos);
    
    printf("\nLimpando a cena do crime...\n");
    liberarMapa(raiz);
    liberarPistas(pistas_coletadas);
    liberarHash(&tabela_de_suspeitos);
    
    printf("\nObrigado por jogar!\n");
    return 0;
}

struct Sala* criarSala(char* nome, char* pista) {
    struct Sala* nova_sala = (struct Sala*) malloc(sizeof(struct Sala));
    strcpy(nova_sala->nome, nome);
    nova_sala->pista = pista;
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
}

void explorarSalas(struct Sala* sala_inicial, struct PistaNode** pistas_raiz) {
    struct Sala* sala_atual = sala_inicial;
    char escolha;
    while (1) {
        printf("\n----------------------------------------------------\nVoce esta em: %s\n", sala_atual->nome);
        if (sala_atual->pista != NULL) {
            printf(">> PISTA ENCONTRADA: '%s'\n", sala_atual->pista);
            *pistas_raiz = inserirPista(*pistas_raiz, sala_atual->pista);
            sala_atual->pista = NULL;
        }
        printf("Para onde voce quer ir? (e -> esquerda, d -> direita, s -> sair): ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') { 
            printf("Voce se retira para analisar as pistas...\n");
            break; 
        } else if ((escolha == 'e' || escolha == 'E') && sala_atual->esquerda != NULL) { 
            sala_atual = sala_atual->esquerda; 
        } else if ((escolha == 'd' || escolha == 'D') && sala_atual->direita != NULL) { 
            sala_atual = sala_atual->direita; 
        } else { 
            printf(">> Caminho invalido ou bloqueado.\n"); 
        }
    }
}

struct PistaNode* inserirPista(struct PistaNode* raiz, char* pista) {
    if (raiz == NULL) {
        struct PistaNode* novoNode = (struct PistaNode*) malloc(sizeof(struct PistaNode));
        novoNode->pista = pista;
        novoNode->esquerda = novoNode->direita = NULL;
        return novoNode;
    }
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

unsigned int hash(char* pista) {
    unsigned long hash_value = 0;
    int c;
    while ((c = *pista++)) {
        hash_value += c;
    }
    return hash_value % HASH_TABLE_SIZE;
}

void inserirNaHash(struct HashTable* tabela, char* pista, char* suspeito) {
    unsigned int indice = hash(pista);
    struct HashNode* novoNode = (struct HashNode*) malloc(sizeof(struct HashNode));
    novoNode->pista = pista;
    novoNode->suspeito = suspeito;
    novoNode->proximo = tabela->baldes[indice];
    tabela->baldes[indice] = novoNode;
}

char* encontrarSuspeito(struct HashTable* tabela, char* pista) {
    unsigned int indice = hash(pista);
    struct HashNode* atual = tabela->baldes[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void contarPistas(struct PistaNode* pistas, char* suspeitoAcusado, struct HashTable* tabela, int* contador) {
    if (pistas == NULL) return;
    
    contarPistas(pistas->esquerda, suspeitoAcusado, tabela, contador);
    
    char* suspeitoDaPista = encontrarSuspeito(tabela, pistas->pista);
    if (suspeitoDaPista != NULL && strcmp(suspeitoDaPista, suspeitoAcusado) == 0) {
        (*contador)++;
    }
    
    contarPistas(pistas->direita, suspeitoAcusado, tabela, contador);
}

void verificarSuspeitoFinal(struct PistaNode* pistas_coletadas, struct HashTable* tabela) {
    if (pistas_coletadas == NULL) {
        printf("\nVoce nao coletou pistas suficientes para fazer uma acusacao.\n");
        return;
    }
    char acusado[50];
    printf("\n====================================================\n");
    printf("                  HORA DO JULGAMENTO                  \n");
    printf("====================================================\n");
    printf("Com base nas pistas que voce coletou, quem e o culpado?\n");
    printf("Suspeitos possiveis: Mordomo, Cozinheira, Jardineiro\n");
    printf("Sua acusacao: ");
    scanf("%49s", acusado);
    strToLower(acusado);

    int contagem_de_pistas = 0;
    
    contarPistas(pistas_coletadas, acusado, tabela, &contagem_de_pistas);

    printf("\n-------------------- VEREDITO --------------------\n");
    printf("Voce acusou: %s.\nA investigacao revela que %d pista(s) apontam para esta pessoa.\n\n", acusado, contagem_de_pistas);

    if (contagem_de_pistas >= 2) {
        printf("PROVAS SUFICIENTES! Voce desvendou o misterio! VITORIA!\n");
    } else {
        printf("PROVAS INSUFICIENTES! O verdadeiro culpado escapou... DERROTA!\n");
    }
    printf("--------------------------------------------------\n");
}

void liberarMapa(struct Sala* sala) {
    if (sala == NULL) return;
    liberarMapa(sala->esquerda);
    liberarMapa(sala->direita);
    free(sala);
}

void liberarPistas(struct PistaNode* pistas) {
    if (pistas == NULL) return;
    liberarPistas(pistas->esquerda);
    liberarPistas(pistas->direita);
    free(pistas);
}

void liberarHash(struct HashTable* tabela) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct HashNode* atual = tabela->baldes[i];
        while (atual != NULL) {
            struct HashNode* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

void strToLower(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}
// Desafio detetive aventureiro - Versão Mestre (Nota 10)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=================================================================
// ESTRUTURAS DE DADOS (As Plantas da Mansão e das Pistas)
//=================================================================

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

//=================================================================
// PROTÓTIPOS DAS FUNÇÕES (O Anúncio das Técnicas)
//=================================================================
// Informamos ao compilador que estas funções existem e como são,
// antes de usá-las na main.

struct Sala* criarSala(char* nome, char* pista);
struct PistaNode* inserirPista(struct PistaNode* raiz, char* pista);
void explorarSalasComPistas(struct Sala* sala_inicial, struct PistaNode** pistas_raiz);
void exibirPistas(struct PistaNode* raiz);

//=================================================================
// FUNÇÃO PRINCIPAL (O Mestre de Cerimônias)
//=================================================================

int main() {
    // Montar o mapa da mansão com pistas
    struct Sala* raiz = criarSala("Hall de Entrada", "Um casaco molhado perto da porta.");
    raiz->esquerda = criarSala("Sala de Jantar", NULL);
    raiz->direita = criarSala("Biblioteca", "Um livro de venenos fora do lugar.");
    raiz->esquerda->esquerda = criarSala("Cozinha", "Uma faca de cozinha desaparecida.");
    raiz->direita->direita = criarSala("Jardim", "Pegadas recentes perto da roseira.");
    raiz->direita->esquerda = criarSala("Escritorio", "Uma carta amassada na lareira.");

    // Iniciar a árvore de pistas como vazia
    struct PistaNode* pistas_coletadas = NULL;

    printf("Bem-vindo ao Detective Quest!\n");
    
    // Iniciar a exploração
    explorarSalasComPistas(raiz, &pistas_coletadas);

    // Exibir o resultado final
    printf("\n--- PISTAS COLETADAS (EM ORDEM ALFABETICA) ---\n");
    if (pistas_coletadas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(pistas_coletadas);
    }
    
    printf("\nObrigado por jogar!\n");

    // Desafio do Mestre: Como liberar a memória de 'raiz' e 'pistas_coletadas'?
    // Fica a reflexão para o próximo nível.

    return 0;
} // Sem ponto e vírgula aqui.

//=================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES (A Execução das Técnicas)
//=================================================================

/**
 * @brief Cria uma nova sala (nó da árvore do mapa).
 * @param nome O nome da sala.
 * @param pista A pista contida na sala (pode ser NULL).
 * @return Um ponteiro para a sala recém-criada.
 */
struct Sala* criarSala(char* nome, char* pista) {
    struct Sala* nova_sala = (struct Sala*) malloc(sizeof(struct Sala));
    strcpy(nova_sala->nome, nome);
    nova_sala->pista = pista; 
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
} // Sem ponto e vírgula aqui.

/**
 * @brief Insere uma nova pista na BST de forma recursiva e ordenada.
 * @param raiz A raiz da árvore de pistas.
 * @param pista A nova pista a ser inserida.
 * @return A raiz da árvore (possivelmente atualizada).
 */
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

/**
 * @brief Exibe todas as pistas da BST em ordem alfabética (percurso em-ordem).
 * @param raiz A raiz da árvore de pistas.
 */
void exibirPistas(struct PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/**
 * @brief Controla a navegação do jogador, coleta pistas e as insere na BST.
 * @param sala_inicial A sala de partida (raiz do mapa).
 * @param pistas_raiz Um ponteiro para a raiz da árvore de pistas.
 */
void explorarSalasComPistas(struct Sala* sala_inicial, struct PistaNode** pistas_raiz) {
    struct Sala* sala_atual = sala_inicial;
    char escolha;

    while (1) { 
        printf("\nVoce esta em: %s\n", sala_atual->nome);

        if (sala_atual->pista != NULL) {
            printf(">> Voce encontrou uma pista: '%s'\n", sala_atual->pista);
            *pistas_raiz = inserirPista(*pistas_raiz, sala_atual->pista);
            sala_atual->pista = NULL; 
        }

        printf("Para onde voce quer ir? (e -> esquerda, d -> direita, s -> sair): ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            printf("Voce decidiu parar a exploracao.\n");
            break; 
        } else if (escolha == 'e' || escolha == 'E') {
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
        } else {
            printf("Comando invalido!\n");
        }
    }
}
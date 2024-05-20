#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore binária
typedef struct NoArvore {
    char nome[100];
    int ra;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

// Função para criar um novo nó
NoArvore* criarNo(char *nome, int ra) {
    NoArvore *novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    strcpy(novoNo->nome, nome);
    novoNo->ra = ra;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore ordenada por RA
NoArvore* inserirPorRA(NoArvore *raiz, char *nome, int ra) {
    if (raiz == NULL)
        return criarNo(nome, ra);
    if (ra < raiz->ra)
        raiz->esquerda = inserirPorRA(raiz->esquerda, nome, ra);
    else
        raiz->direita = inserirPorRA(raiz->direita, nome, ra);
    return raiz;
}

// Função para inserir um nó na árvore ordenada por nome
NoArvore* inserirPorNome(NoArvore *raiz, char *nome, int ra) {
    if (raiz == NULL)
        return criarNo(nome, ra);
    if (strcmp(nome, raiz->nome) < 0)
        raiz->esquerda = inserirPorNome(raiz->esquerda, nome, ra);
    else
        raiz->direita = inserirPorNome(raiz->direita, nome, ra);
    return raiz;
}

// Função para imprimir a árvore em ordem
void imprimirEmOrdem(NoArvore *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d, %s\n", raiz->ra, raiz->nome);
        imprimirEmOrdem(raiz->direita);
    }
}

// Função para imprimir a árvore em ordem reversa
void imprimirEmOrdemReversa(NoArvore *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdemReversa(raiz->direita);
        printf("%d, %s\n", raiz->ra, raiz->nome);
        imprimirEmOrdemReversa(raiz->esquerda);
    }
}

// Função para buscar um nó na árvore por RA
NoArvore* buscarPorRA(NoArvore *raiz, int ra) {
    if (raiz == NULL || raiz->ra == ra)
        return raiz;
    if (ra < raiz->ra)
        return buscarPorRA(raiz->esquerda, ra);
    return buscarPorRA(raiz->direita, ra);
}

// Função para buscar um nó na árvore por nome
NoArvore* buscarPorNome(NoArvore *raiz, char *nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
        return raiz;
    if (strcmp(nome, raiz->nome) < 0)
        return buscarPorNome(raiz->esquerda, nome);
    return buscarPorNome(raiz->direita, nome);
}

// Função para carregar dados do arquivo CSV
void carregarDados(char *nomeArquivo, NoArvore **raizRA, NoArvore **raizNome) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[150];
    char nome[100];
    int ra;

    // Ignora a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove nova linha, se presente
        linha[strcspn(linha, "\r\n")] = 0;
        sscanf(linha, "%d,%[^\n]", &ra, nome);
        *raizRA = inserirPorRA(*raizRA, nome, ra);
        *raizNome = inserirPorNome(*raizNome, nome, ra);
    }

    fclose(arquivo);
}

int main() {
    int escolha, ra;
    char nome[100];
    NoArvore *raizRA = NULL, *raizNome = NULL, *resultado = NULL;

    // Carregar dados e construir as duas árvores
    carregarDados("nome_RA.csv", &raizRA, &raizNome);

    do {
        printf("\nMenu:\n");
        printf("1. Imprimir a Arvore ordenada por RA em ordem\n");
        printf("2. Imprimir a Arvore ordenada por RA em ordem reversa\n");
        printf("3. Imprimir a Arvore ordenada por Nome em ordem\n");
        printf("4. Imprimir a Arvore ordenada por Nome em ordem reversa\n");
        printf("5. Buscar por RA\n");
        printf("6. Buscar por Nome\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                imprimirEmOrdem(raizRA);
                break;
            case 2:
                imprimirEmOrdemReversa(raizRA);
                break;
            case 3:
                imprimirEmOrdem(raizNome);
                break;
            case 4:
                imprimirEmOrdemReversa(raizNome);
                break;
            case 5:
                printf("Digite o RA a ser buscado: ");
                scanf("%d", &ra);
                resultado = buscarPorRA(raizRA, ra);
                if (resultado)
                    printf("Encontrado: %d, %s\n", resultado->ra, resultado->nome);
                else
                    printf("RA não encontrado.\n");
                break;
            case 6:
                printf("Digite o nome a ser buscado: ");
                scanf(" %[^\n]", nome);
                resultado = buscarPorNome(raizNome, nome);
                if (resultado)
                    printf("Encontrado: %d, %s\n", resultado->ra, resultado->nome);
                else
                    printf("Nome não encontrado.\n");
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 7);

    return 0;
}

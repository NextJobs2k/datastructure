#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore binária
typedef struct TreeNode {
    char name[100];
    int ra;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Função para criar um novo nó
TreeNode* createNode(char *name, int ra) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    newNode->ra = ra;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore ordenada por RA
TreeNode* insertByRA(TreeNode *root, char *name, int ra) {
    if (root == NULL)
        return createNode(name, ra);
    if (ra < root->ra)
        root->left = insertByRA(root->left, name, ra);
    else
        root->right = insertByRA(root->right, name, ra);
    return root;
}

// Função para inserir um nó na árvore ordenada por nome
TreeNode* insertByName(TreeNode *root, char *name, int ra) {
    if (root == NULL)
        return createNode(name, ra);
    if (strcmp(name, root->name) < 0)
        root->left = insertByName(root->left, name, ra);
    else
        root->right = insertByName(root->right, name, ra);
    return root;
}

// Função para imprimir a árvore em ordem
void inorder(TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d, %s\n", root->ra, root->name);
        inorder(root->right);
    }
}

// Função para imprimir a árvore em ordem reversa
void reverseOrder(TreeNode *root) {
    if (root != NULL) {
        reverseOrder(root->right);
        printf("%d, %s\n", root->ra, root->name);
        reverseOrder(root->left);
    }
}

// Função para buscar um nó na árvore por RA
TreeNode* searchByRA(TreeNode *root, int ra) {
    if (root == NULL || root->ra == ra)
        return root;
    if (ra < root->ra)
        return searchByRA(root->left, ra);
    return searchByRA(root->right, ra);
}

// Função para buscar um nó na árvore por nome
TreeNode* searchByName(TreeNode *root, char *name) {
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;
    if (strcmp(name, root->name) < 0)
        return searchByName(root->left, name);
    return searchByName(root->right, name);
}

// Função para carregar dados do arquivo CSV
TreeNode* loadData(char *filename, int orderBy) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    TreeNode *root = NULL;
    char line[150];
    char name[100];
    int ra;

    // Ignora a primeira linha (cabeçalho)
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        // Remove nova linha, se presente
        line[strcspn(line, "\r\n")] = 0;
        sscanf(line, "%d,%[^\n]", &ra, name);
        if (orderBy == 1)
            root = insertByName(root, name, ra);
        else
            root = insertByRA(root, name, ra);
    }

    fclose(file);
    return root;
}

int main() {
    int choice, ra, orderBy;
    char name[100];
    TreeNode *root = NULL, *result = NULL;

    printf("Escolha o critério de ordenamento da árvore:\n");
    printf("1. Alfabética por nome\n");
    printf("2. Crescente por RA\n");
    scanf("%d", &orderBy);

    root = loadData("nome_RA.csv", orderBy);

    do {
        printf("\nMenu:\n");
        printf("1. Imprimir a árvore em ordem\n");
        printf("2. Imprimir a árvore em ordem reversa\n");
        printf("3. Buscar por RA\n");
        printf("4. Buscar por nome\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inorder(root);
                break;
            case 2:
                reverseOrder(root);
                break;
            case 3:
                printf("Digite o RA a ser buscado: ");
                scanf("%d", &ra);
                result = searchByRA(root, ra);
                if (result)
                    printf("Encontrado: %d, %s\n", result->ra, result->name);
                else
                    printf("RA não encontrado.\n");
                break;
            case 4:
                printf("Digite o nome a ser buscado: ");
                scanf(" %[^\n]", name);
                result = searchByName(root, name);
                if (result)
                    printf("Encontrado: %d, %s\n", result->ra, result->name);
                else
                    printf("Nome não encontrado.\n");
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (choice != 5);

    return 0;
}

/*
Daniel Martins de Carvalho, 2321386
Pedro Henrique Dos Santos, 2368030
AP - Atividade Pratica - ED1 - 20/11/2023 - Prof(a). Dr(a). Tamara Angélica Baldo 
*/

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//----------- Argc argv -------------------//


// Struct para representar um funcionário //obs: Prefirimos não usar typedef para as structs
 struct Funcionarios {
    char nome[100];
    char endereco[100];
    char aniversario[20];
    int numEndereco;
    float salario;
    struct Funcionarios* prox;
    struct Funcionarios* anterior;
};

//Struct para AVL
struct AVLno {
    struct Funcionarios* Funcionarios;
    struct AVLno* Esq;
    struct AVLno* dir;
    int altura;
};

//pesquisa funcionários por intervalo salarial
void pesquisa_salario(struct Funcionarios* head, float valormin, float valormax) {
    struct Funcionarios* Atual = head;

    printf("Funcionarios com salario no intervalo de %.2f a %.2f:\n", valormin, valormax);  

    while (Atual != NULL) {
        if (Atual->salario >= valormin && Atual->salario <= valormax) {
            printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: %.2f\n",
                   Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        }
        Atual = Atual->prox;
    }
}


//insere um funcionário de forma ordenada na lista
void inserirFuncionarios(struct Funcionarios** head, struct Funcionarios* novoFuncionario) {
    struct Funcionarios* Atual = *head;


    if (*head == NULL || strcmp(novoFuncionario->nome, Atual->nome) < 0) {
        novoFuncionario->prox = Atual;
        novoFuncionario->anterior = NULL;
        if (Atual != NULL) {
            Atual->anterior = novoFuncionario;
        }
        *head = novoFuncionario;
    } else {
        while (Atual->prox != NULL && strcmp(novoFuncionario->nome, Atual->prox->nome) > 0) {
            Atual = Atual->prox;
        }

        novoFuncionario->prox = Atual->prox;
        novoFuncionario->anterior = Atual;
        if (Atual->prox != NULL) {
            Atual->prox->anterior = novoFuncionario;
        }
        Atual->prox = novoFuncionario;
    }
}

// Função para exibir a lista de funcionários
void exibeFuncionarios(struct Funcionarios* head) {
    struct Funcionarios* Atual = head;
    

    printf("Lista de funcionarios ordenada por nome:\n");
    while (Atual != NULL) {

        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: %.2f\n",

               Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        Atual = Atual->prox;
    }
}

//exibe a lista de funcionários ordenada por nome (A a Z)
void exibeFuncionariosOrdemNome(struct Funcionarios* head) {
    struct Funcionarios* Atual = head;

    printf("Lista de funcionarios ordenada por nome (A a Z):\n");
    while (Atual != NULL) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",

               Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        Atual = Atual->prox;
    }
}

//exibe a lista de funcionários ordenada por nome (Z a A)
void exibeFuncionariosOrdemNomeContrario(struct Funcionarios* head) {
    struct Funcionarios* Atual = head;

    //Vá para o final da lista
    while (Atual != NULL && Atual->prox != NULL) {
        Atual = Atual->prox;
    }

    printf("Lista de funcionarios ordenada por nome (Z a A): \n");
    while (Atual != NULL) {

        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",

               Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        Atual = Atual->anterior;
    }
}

//Função auxiliar para calcular a altura de um nó
int Altura(struct AVLno* no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

//Função auxiliar para calcular o fator de balanciamento de um nó
int fatorbalanciamento(struct AVLno* no) {
    if (no == NULL) {
        return 0;
    }
    return Altura(no->Esq) - Altura(no->dir);
}

//Função auxiliar para criar um novo nó AVL
struct AVLno* criarNoAVL(struct Funcionarios* Funcionarios) {
    struct AVLno* novoNo = (struct AVLno*)malloc(sizeof(struct AVLno));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no AVL");
        exit(EXIT_FAILURE);
    }
    novoNo->Funcionarios = Funcionarios;
    novoNo->Esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1;
    return novoNo;
}

//Função auxiliar para realizar uma rotação simples para a direita
struct AVLno* rotacaoDir(struct AVLno* y) {
    struct AVLno* x = y->Esq;
    struct AVLno* T2 = x->dir;

    //Realiza a rotação
    x->dir = y;
    y->Esq = T2;

    //Atualiza alturas
    y->altura = 1 + fmax(Altura(y->Esq), Altura(y->dir)); //?????????????????O que é fmax????????????
    x->altura = 1 + fmax(Altura(x->Esq), Altura(x->dir));

    return x;
}

//Função auxiliar para realizar uma rotação simples para a esquerda
struct AVLno* rotacaoEsq(struct AVLno* x) {
    struct AVLno* y = x->dir;
    struct AVLno* T2 = y->Esq;

    //Realiza a rotação
    y->Esq = x;
    x->dir = T2;

    //Atualiza as alturas
    x->altura = 1 + fmax(Altura(x->Esq), Altura(x->dir));
    y->altura = 1 + fmax(Altura(y->Esq), Altura(y->dir));

    return y;
}

//insere um funcionário na árvore AVL
struct AVLno* inserirAVL(struct AVLno* raiz, struct Funcionarios* Funcionarios) {
    // Passo 1: Inserção normal da ABB
    if (raiz == NULL) {
        return criarNoAVL(Funcionarios);
    }

    if (strcmp(Funcionarios->nome, raiz->Funcionarios->nome) < 0) {
        raiz->Esq = inserirAVL(raiz->Esq, Funcionarios);
    } else if (strcmp(Funcionarios->nome, raiz->Funcionarios->nome) > 0) {
        raiz->dir = inserirAVL(raiz->dir, Funcionarios);
    } else {
        //Ignora os funcionários com o mesmo nome
        return raiz;
    }

    //Passo 2: Atualiza a altura do nó atual
    raiz->altura = 1 + fmax(Altura(raiz->Esq), Altura(raiz->dir));

    //Passo 3: Obtém o fator de balanciamento deste nó para verificar se é necessário reequilibrar
    int balanciamento = fatorbalanciamento(raiz);

    //Passo 4: 4 casos de desequilíbrio que precisam ser tratados

    // Caso da rotação simples à direita
    if (balanciamento > 1 && strcmp(Funcionarios->nome, raiz->Esq->Funcionarios->nome) < 0) {
        return rotacaoDir(raiz);
    }

    // Caso da rotação simples à esquerda
    if (balanciamento < -1 && strcmp(Funcionarios->nome, raiz->dir->Funcionarios->nome) > 0) {
        return rotacaoEsq(raiz);
    }

    // Caso da rotação dupla à direita (rotação à esquerda seguida de rotação à direita)
    if (balanciamento > 1 && strcmp(Funcionarios->nome, raiz->Esq->Funcionarios->nome) > 0) {
        raiz->Esq = rotacaoEsq(raiz->Esq);
        return rotacaoDir(raiz);
    }

    // Caso da rotação dupla à esquerda (rotação à direita seguida de rotação à esquerda)
    if (balanciamento < -1 && strcmp(Funcionarios->nome, raiz->dir->Funcionarios->nome) < 0) {
        raiz->dir = rotacaoDir(raiz->dir);
        return rotacaoEsq(raiz);
    }

    return raiz;
}

//transforma uma lista duplamente encadeada em uma árvore AVL
struct AVLno* converteListaParaAVL(struct Funcionarios* head) {
    struct AVLno* raiz = NULL;
    struct Funcionarios* Atual = head;

    while (Atual != NULL) {
        raiz = inserirAVL(raiz, Atual);
        Atual = Atual->prox;
    }

    return raiz;
}
//exibe a árvore AVL em ordem
void exibeAVL(struct AVLno* raiz) {

    if (raiz != NULL) {
        exibeAVL(raiz->Esq);
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               raiz->Funcionarios->nome, raiz->Funcionarios->endereco, raiz->Funcionarios->aniversario, raiz->Funcionarios->salario);
        exibeAVL(raiz->dir);
    }
}

//libera a memória alocada para a árvore AVL
void freeAVL(struct AVLno* raiz) {
    if (raiz != NULL) {
        freeAVL(raiz->Esq);
        freeAVL(raiz->dir);
        free(raiz);
    }
}

//pesquisa funcionários por intervalo salarial em uma árvore AVL
void pesquisa_salarioAVL(struct AVLno* raiz, float valormin, float valormax) {
    if (raiz == NULL) {
        return;
    }

    pesquisa_salarioAVL(raiz->Esq, valormin, valormax);

    if (raiz->Funcionarios->salario >= valormin && raiz->Funcionarios->salario <= valormax) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               raiz->Funcionarios->nome, raiz->Funcionarios->endereco, raiz->Funcionarios->aniversario, raiz->Funcionarios->salario);
    }

    pesquisa_salarioAVL(raiz->dir, valormin, valormax);
}


/*---------------MODIFICAR AQUI (GPT DE MAIS SLC)----------------*/
//Função auxiliar para calcular a idade com base na data de nascimento
int calculateAge(const char* aniversario) {
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);

    struct tm tm_aniversario;
    sscanf(aniversario, "%d/%d/%d", &tm_aniversario.tm_mday, &tm_aniversario.tm_mon, &tm_aniversario.tm_year);
    tm_aniversario.tm_year -= 1900; // Ajuste do ano (começa em 1900)
    tm_aniversario.tm_mon -= 1;     // Ajuste do mês (0-11)

    int age = tm_now->tm_year - tm_aniversario.tm_year;

    //Verifica se o aniversário já ocorreu este ano
    if (tm_now->tm_mon < tm_aniversario.tm_mon || (tm_now->tm_mon == tm_aniversario.tm_mon && tm_now->tm_mday < tm_aniversario.tm_mday)) {
        age--;
    }

    return age;
}

/*---------------MODIFICAR AQUI (GPT DE MAIS SLC)----------------*/
//compara funcionários com base na idade para a ordenação
int compareByAge(const void* a, const void* b) {
    struct Funcionarios* FuncionariosA = *((struct Funcionarios**)a);
    struct Funcionarios* FuncionariosB = *((struct Funcionarios**)b);

    int ageA = calculateAge(FuncionariosA->aniversario);
    int ageB = calculateAge(FuncionariosB->aniversario);

    return ageA - ageB;
}

//imprime a lista de funcionários ordenada por idade
void exibeFuncionariosOrdemIdade(struct Funcionarios* head) {
    //Conta o número de funcionários na lista
    int cont = 0;
    struct Funcionarios* Atual = head;
    while (Atual != NULL) {
        cont++;
        Atual = Atual->prox;
    }

    //Aloca um vetor de ponteiros para funcionários
    struct Funcionarios** vetorFuncionarios = (struct Funcionarios**)malloc(cont * sizeof(struct Funcionarios*));
    if (vetorFuncionarios == NULL) {
        perror("Erro ao alocar memoria para o array de funcionarios");
        exit(EXIT_FAILURE);
    }

    // Preenche o vetor de ponteiros
    Atual = head;
    for (int i = 0; i < cont; i++) {
        vetorFuncionarios[i] = Atual;
        Atual = Atual->prox;
    }

    // Ordena o vetor de ponteiros com base na idade
    qsort(vetorFuncionarios, cont, sizeof(struct Funcionarios*), compareByAge); // ---------MUDAR O NOME------------

    // Imprime a lista ordenada por idade
    printf("Lista de funcionarios ordenada por idade (do mais novo para o mais velho):\n");
    for (int i = 0; i < cont; i++) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               vetorFuncionarios[i]->nome, vetorFuncionarios[i]->endereco, vetorFuncionarios[i]->aniversario, vetorFuncionarios[i]->salario);
    }

    // Libera a memória alocada para o vetor de ponteiros
    free(vetorFuncionarios);
}

/*---------------MODIFICAR AQUI (GPT DE MAIS SLC)----------------*/
//compara funcionários com base na idade para a ordenação (do mais velho para o mais novo)
int comparaIdadeContrario(const void* a, const void* b) {
    struct Funcionarios* FuncionariosA = *((struct Funcionarios**)a);
    struct Funcionarios* FuncionariosB = *((struct Funcionarios**)b);

    int ageA = calculateAge(FuncionariosA->aniversario);
    int ageB = calculateAge(FuncionariosB->aniversario);

    return ageB - ageA;
}

//imprime a lista de funcionários ordenada por idade (do mais velho para o mais novo)
void exibeFuncionariosOrdemIdadeContrario(struct Funcionarios* head) {
    //Conta o número de funcionários na lista
    int cont = 0;
    struct Funcionarios* Atual = head;
    while (Atual != NULL) {
        cont++;
        Atual = Atual->prox;
    }

    //Aloca um vetor de ponteiros para funcionários
    struct Funcionarios** vetorFuncionarios = (struct Funcionarios**)malloc(cont * sizeof(struct Funcionarios*));
    if (vetorFuncionarios == NULL) {
        perror("Erro ao alocar memoria para o array de funcionarios");
        exit(EXIT_FAILURE);
    }

    //Preenche o vetor de ponteiros
    Atual = head;
    for (int i = 0; i < cont; i++) {
        vetorFuncionarios[i] = Atual;
        Atual = Atual->prox;
    }

    //Ordena o vetor de ponteiros com base na idade (do mais velho para o mais novo)
    qsort(vetorFuncionarios, cont, sizeof(struct Funcionarios*), comparaIdadeContrario);

    //Imprime a lista ordenada por idade (do mais velho para o mais novo)
    printf("Lista de funcionarios ordenada por idade (do mais velho para o mais novo):\n");
    for (int i = 0; i < cont; i++) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               vetorFuncionarios[i]->nome, vetorFuncionarios[i]->endereco, vetorFuncionarios[i]->aniversario, vetorFuncionarios[i]->salario);
    }

    //Libera a memória alocada para o vetor de ponteiros
    free(vetorFuncionarios);
}

// Função para exibir um menu
int exibeMenu() {
    int opcao;
    printf("\n   |Menu Principal|");
    printf("\n1 - Intervalo Salarial\n");
    printf("2 - Exibir os funcionarios de A-Z\n");
    printf("3 - Exibir os funcionarios de Z-A\n");
    printf("4 - Transformar em AVL\n");
    printf("5 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

void auxiliarAVLOpcao(struct Funcionarios** head, struct AVLno** avlraiz, int avlopcao) {
    float valormin, valormax; // Mova as declarações para fora do bloco switch

    switch (avlopcao) {
        case 1:
            // Código para a opção 1 (Intervalo Salarial)
            printf("\nDigite o valor minimo do intervalo salarial: ");
            scanf("%f", &valormin);
            printf("Digite o valor maximo do intervalo salarial: ");
            scanf("%f", &valormax);
            pesquisa_salarioAVL(*avlraiz, valormin, valormax);
            break;
        case 2:
            // Código para a opção 2 (IDADE maior para menor)
            exibeFuncionariosOrdemIdadeContrario(*head);
            break;
        case 3:
            // Código para a opção 3 (IDADE menor para maior)
            exibeFuncionariosOrdemIdade(*head);
            break;
        case 4:
            // Volta ao menu principal
            break;
        default:
            printf("\nOpcao invalida. Digite novamente.\n");
            break;
    }
}

void auxiliarOpcao(struct Funcionarios* head, struct AVLno* avlraiz, int opcao) {

    switch (opcao) {
        case 1:
            system ("cls");
            float valormin, valormax;
            printf("Digite o valor minimo do intervalo salarial: ");
            scanf("%f", &valormin);
            printf("Digite o valor maximo do intervalo salarial: ");
            scanf("%f", &valormax);
            pesquisa_salario(head, valormin, valormax);
            break;

        case 2:
            system ("cls");
            printf ("\n\nFUNCIONARIOS EM ORDEM ALFABETICA \n \n");
            exibeFuncionariosOrdemNome(head);
            break;

        case 3:
            system ("cls");
            printf ("\n\n FUNCIONARIOS EM ORDEM ALFABETICA Z - A\n \n");
            exibeFuncionariosOrdemNomeContrario(head); // Exibe a lista de funcionários de Z a A
            break;

        case 4:
            // Código para a opção 4 (Transformar em AVL)
            {
            int avlopcao;
            printf("\nTransformando em AVL....\nFinalizado!!!");
            do {
                printf("\n\n   |MENU AVL|");
                printf("\n 1- Intervalo Salarial");
                printf("\n 2- Exibir da maior idade para a menor");
                printf("\n 3- Exibir da menor idade para a maior");
                printf("\n 4- Voltar");
                printf("\n\n DIGITE: ");
                scanf("%d", &avlopcao);

                if (avlopcao != 1 && avlopcao != 2 && avlopcao != 3 && avlopcao != 4) {
                    printf("\n OPCAO INVALIDA DIGITE NOVAMENTE: ");
                }

                auxiliarAVLOpcao(&head, &avlraiz, avlopcao);

            } while (avlopcao != 4);

            break;
        }

        case 5:
            // Libera a memória antes de sair
            system ("cls");
            printf ("\n\n Processos Finalizados!!! =)\n \n");
            exit(0);
            break;

        default:
            printf("\nOpcao invalida. Digite novamente.\n");
    }
}

/*---------------MODIFICAR AQUI (GPT DE MAIS SLC)----------------*/
// Função para ler o arquivo e criar a lista de funcionários
struct Funcionarios* leituraArqFuncionarios(const char* arqNome) {
    FILE* file = fopen(arqNome, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    struct Funcionarios* head = NULL;
    char linha[256];

    fgets(linha, sizeof(linha), file); // Ignora a primeira linha

    while (fgets(linha, sizeof(linha), file)) {
        struct Funcionarios* novoFuncionario = (struct Funcionarios*)malloc(sizeof(struct Funcionarios));
        if (novoFuncionario == NULL) {
            perror("Erro ao alocar memória para o funcionário");
            exit(EXIT_FAILURE);
        }

        sscanf(linha, "%99[^,],%99[^,],%19[^,],%d,\"R$ %f\"", //Pega 99 espaços até encontrar a vigula. Salvando na variavel
               novoFuncionario->nome, novoFuncionario->aniversario, novoFuncionario->endereco, &novoFuncionario->numEndereco, &novoFuncionario->salario);
        novoFuncionario->salario *= 1000; // Multiplicação para lidar com o padrao americano de pontuacao
        novoFuncionario->prox = NULL;
        novoFuncionario->anterior = NULL;

        inserirFuncionarios(&head, novoFuncionario);
    }

    fclose(file);
    return head;
}

int main() {

    struct Funcionarios* head = leituraArqFuncionarios("Dados_Funcionarios.csv");
    struct AVLno* avlraiz = converteListaParaAVL(head);

    for (;;) { //For infinito :)
        int opcao = exibeMenu(); //Finaliza o loop dentro da função
        auxiliarOpcao(head, avlraiz, opcao);
    }

    return 0;
}
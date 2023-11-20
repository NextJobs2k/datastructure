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

//Struct para representar um funcionário //obs: Prefirimos não usar typedef para as structs
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
void pesquisa_salario(struct Funcionarios* topo, float valormin, float valormax) {
    //Inicializa um ponteiro para o nó atual como o topo da lista.
    struct Funcionarios* Atual = topo;

    printf("Funcionarios com salario no intervalo de %.2f a %.2f:\n", valormin, valormax);

    //Percorre a lista e exibe os funcionários cujos salários estão no intervalo especificado.
    while (Atual != NULL) {
        if (Atual->salario >= valormin && Atual->salario <= valormax) {
            printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: %.2f\n",
                   Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        }
        Atual = Atual->prox;
    }
}


//insere um funcionário de forma ordenada na lista
void inserirFuncionarios(struct Funcionarios** topo, struct Funcionarios* novoFuncionario) {
    //Inicializa um ponteiro para o nó atual como o topo da lista.
    struct Funcionarios* Atual = *topo;

    //Caso a lista esteja vazia ou o novo funcionário tem um nome menor que o primeiro funcionário da lista.
    if (*topo == NULL || strcmp(novoFuncionario->nome, Atual->nome) < 0) {
        novoFuncionario->prox = Atual; //O próximo do novo funcionário aponta para o atual topo.
        novoFuncionario->anterior = NULL; //O anterior do novo funcionário é nulo, indicando o início da lista.
        if (Atual != NULL) {
            Atual->anterior = novoFuncionario; //Se a lista não estiver vazia, o anterior do atual topo aponta para o novo funcionário.
        }
        *topo = novoFuncionario; //Atualiza o topo da lista para o novo funcionário.
    } else {
        //Percorre a lista até encontrar a posição correta para inserir o novo funcionário.
        while (Atual->prox != NULL && strcmp(novoFuncionario->nome, Atual->prox->nome) > 0) {
            Atual = Atual->prox;
        }
        //Insere o novo funcionário na posição correta.
        novoFuncionario->prox = Atual->prox;
        novoFuncionario->anterior = Atual;

        if (Atual->prox != NULL) {
            Atual->prox->anterior = novoFuncionario; //Atualiza o anterior do próximo nó na lista.
        }
        Atual->prox = novoFuncionario; //Atualiza o próximo do nó atual para o novo funcionário.
    }
}

//exibe a lista de funcionários ordenada por nome (A a Z)
void exibeFuncionariosOrdemNome(struct Funcionarios* topo) {
    //Inicializa o ponteiro para o nó atual como o topo da lista.
    struct Funcionarios* Atual = topo;

    printf("Lista de funcionarios ordenada por nome (A a Z):\n");

    //Percorre a lista e exibe os dados dos funcionários em ordem crescente de nome.
    while (Atual != NULL) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
            Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        Atual = Atual->prox; //Move para o próximo nó na lista.
    }
}

//Função que exibe a lista de funcionários ordenada por nome de forma contrária (Z a A).
void exibeFuncionariosOrdemNomeContrario(struct Funcionarios* topo) {
    //Inicializa o ponteiro para o nó atual como o topo da lista.
    struct Funcionarios* Atual = topo;

    //Vai para o final da lista
    while (Atual != NULL && Atual->prox != NULL) {
        Atual = Atual->prox;
    }

    printf("Lista de funcionarios ordenada por nome (Z a A): \n");

    //Percorre a lista de trás para frente e exibe os dados dos funcionários.
    while (Atual != NULL) {

        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
            Atual->nome, Atual->endereco, Atual->aniversario, Atual->salario);
        Atual = Atual->anterior;//Move para o nó anterior na lista.
    }
}

//Função auxiliar para calcular a altura de um nó
int Altura(struct AVLno* no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

//Função auxiliar para calcular o fator de balanciamento de um nó em uma árvore AVL.
//Recebe o ponteiro para o nó que o fator de balanciamento será calculado.
//Retorna o valor do fator de balanciamento: Altura(No->Esq) - Altura(No->dir).
//Se o nó for nulo, retorna 0.
int fatorbalanciamento(struct AVLno* no) {
    if (no == NULL) {
        return 0;
    }
    return Altura(no->Esq) - Altura(no->dir);
}

//Função auxiliar para criar um novo nó em uma árvore AVL.
//Recebe o ponteiro para a estrutura Funcionarios, que contém os dados do funcionário.
//Retorna o ponteiro para o novo nó criado.
struct AVLno* criarNoAVL(struct Funcionarios* Funcionarios) {
    //Aloca memória para o novo nó AVL.
    struct AVLno* novoNo = (struct AVLno*)malloc(sizeof(struct AVLno));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no AVL"); //Mensagem de erro
        exit(EXIT_FAILURE);
    }
    //Inicializa os campos do novo nó com os dados fornecidos.
    novoNo->Funcionarios = Funcionarios;
    novoNo->Esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1;
    // Retorna o ponteiro para o novo nó.
    return novoNo;
}

//Função auxiliar para realizar uma rotação simples para a direita em uma árvore AVL.
//Recebe o ponteiro para o nó a ser rotacionado para a direita (y).
//Retorna o ponteiro para o novo nó que assume a posição superior após a rotação (x).
struct AVLno* rotacaoDir(struct AVLno* y) {
    //Armazena o ponteiro para o filho à esquerda do nó que será rotacionado.
    struct AVLno* x = y->Esq;
    //Armazena o ponteiro para a subárvore direita do filho à esquerda.   
    struct AVLno* T2 = x->dir;

    //Realiza a rotação para a direita
    x->dir = y;
    y->Esq = T2;

    //Atualiza as alturas dos nós y e x após a rotação.
    y->altura = 1 + fmax(Altura(y->Esq), Altura(y->dir)); //fmax retorna o valor máximo entre dois números.
    x->altura = 1 + fmax(Altura(x->Esq), Altura(x->dir));
    /*fmax é usado para calcular a altura máxima entre as subárvores esquerda (Esq) e direita (dir) dos nós y e x.
    A altura é então incrementada em 1, por causa da altura atualizada do nó após a rotação.*/

    return x; //Retorna o novo nó que se torna a raiz da subárvore rotacionada
}

//Função auxiliar para realizar uma rotação simples para a esquerda em uma árvore AVL.
//Recebe o ponteiro para o nó a ser rotacionado para a esquerda (x).
//Retorna o ponteiro para o novo nó que assume a posição superior após a rotação (y).
struct AVLno* rotacaoEsq(struct AVLno* x) {
    //Armazena o ponteiro para o nó da direita de x em y.
    struct AVLno* y = x->dir;
    //Armazena o ponteiro para a subárvore esquerda de y em T2.
    struct AVLno* T2 = y->Esq;

    //Realiza a rotação para esquerda
    y->Esq = x;
    x->dir = T2;

    //Atualiza as alturas dos nós x e y após a rotação.
    x->altura = 1 + fmax(Altura(x->Esq), Altura(x->dir));
    y->altura = 1 + fmax(Altura(y->Esq), Altura(y->dir));

     //Retorna o ponteiro para o novo nó que assume a posição superior após a rotação.
    return y;
}

//insere um funcionário na árvore AVL
struct AVLno* inserirAVL(struct AVLno* raiz, struct Funcionarios* Funcionarios) {
    //Passo 1: Inserção normal da ABB
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

    //Caso da rotação simples à direita
    if (balanciamento > 1 && strcmp(Funcionarios->nome, raiz->Esq->Funcionarios->nome) < 0) {
        return rotacaoDir(raiz);
    }

    //Caso da rotação simples à esquerda
    if (balanciamento < -1 && strcmp(Funcionarios->nome, raiz->dir->Funcionarios->nome) > 0) {
        return rotacaoEsq(raiz);
    }

    //Caso da rotação dupla à direita (rotação à esquerda seguida de rotação à direita)
    if (balanciamento > 1 && strcmp(Funcionarios->nome, raiz->Esq->Funcionarios->nome) > 0) {
        raiz->Esq = rotacaoEsq(raiz->Esq);
        return rotacaoDir(raiz);
    }

    //Caso da rotação dupla à esquerda (rotação à direita seguida de rotação à esquerda)
    if (balanciamento < -1 && strcmp(Funcionarios->nome, raiz->dir->Funcionarios->nome) < 0) {
        raiz->dir = rotacaoDir(raiz->dir);
        return rotacaoEsq(raiz);
    }

    return raiz;
}

//transforma uma lista duplamente encadeada em uma árvore AVL
struct AVLno* converteListaParaAVL(struct Funcionarios* topo) {
    struct AVLno* raiz = NULL;
    struct Funcionarios* Atual = topo;

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
    //Verifica se a raiz da árvore é nula (caso base da recursão)
    if (raiz == NULL) {
        return;
    }
    //Realiza a pesquisa na subárvore esquerda (recursao)
    pesquisa_salarioAVL(raiz->Esq, valormin, valormax);

    //Verifica se o salário do funcionário atual está dentro do intervalo especificado
    if (raiz->Funcionarios->salario >= valormin && raiz->Funcionarios->salario <= valormax) {
        //Imprime os dados do funcionário que atende ao critério de salário
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               raiz->Funcionarios->nome, raiz->Funcionarios->endereco, raiz->Funcionarios->aniversario, raiz->Funcionarios->salario);
    }
    //Realiza a pesquisa na subárvore direita (recusao)
    pesquisa_salarioAVL(raiz->dir, valormin, valormax);
}

//Função auxiliar para calcular a idade com base na data de nascimento
int CalculaIdade(char* aniversario) {
    time_t now = time(NULL); //Obtém o tempo atual em segundos
    struct tm* tm_now = localtime(&now); //Converte o tempo atual para uma estrutura tm representando a data e hora local.

    struct tm tm_aniversario;  //Cria uma estrutura tm para armazenar a data de aniversário fornecida.
    //Lê os componentes do dia, mês e ano da string aniversario e os armazena na estrutura tm_aniversario.
    sscanf(aniversario, "%d/%d/%d", &tm_aniversario.tm_mday, &tm_aniversario.tm_mon, &tm_aniversario.tm_year);
    tm_aniversario.tm_year -= 1900; //Ajusta o ano subtraindo 1900, pois a contidadem dos anos em tm começa em 1900.
    tm_aniversario.tm_mon -= 1;     //Ajusta o mês subtraindo 1, pois a contidadem dos meses em tm vai de 0 a 11.

    int idade = tm_now->tm_year - tm_aniversario.tm_year; //Calcula a idade subtraindo o ano de nascimento do ano atual.

    //Verifica se o aniversário já ocorreu este ano
    if (tm_now->tm_mon < tm_aniversario.tm_mon || (tm_now->tm_mon == tm_aniversario.tm_mon && tm_now->tm_mday < tm_aniversario.tm_mday)) {
        idade--;
    }/*Se o mês atual for menor que o mês de aniversário ou se estivermos no mesmo mês,
    mas o dia atual for menor que o dia de aniversário, decrementamos a idade, 
    pois o aniversário ainda não ocorreu este ano.
    */
    return idade;  //Retorna a idade calculada.
}

/*---------------MODIFICAR AQUI (GPT DE MAIS SLC)----------------*/
//compara funcionários com base na idade para a ordenação
int ComprararIdadeCrescente(const void* a, const void* b) { //obs: declaramos como const void* para poder usar no qsort.
    //Converte os ponteiros void* de a e b para ponteiros de struct Funcionarios* para acessar os dados dos funcionários.
    struct Funcionarios* FuncionariosA = *((struct Funcionarios**)a);
    struct Funcionarios* FuncionariosB = *((struct Funcionarios**)b);

    //Calcula as idades dos funcionários A e B usando a função auxiliar CalculaIdade.
    int idadeA = CalculaIdade(FuncionariosA->aniversario);
    int idadeB = CalculaIdade(FuncionariosB->aniversario);

    //Retorna a diferença entre as idades, resultando em uma ordenação em ordem crescente.
    return idadeA - idadeB;
}

//imprime a lista de funcionários ordenada por idade
void exibeFuncionariosOrdemIdade(struct Funcionarios* topo) {
    //Conta o número de funcionários na lista
    int cont = 0;
    struct Funcionarios* Atual = topo;
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
    Atual = topo;
    for (int i = 0; i < cont; i++) {
        vetorFuncionarios[i] = Atual;
        Atual = Atual->prox;
    }

    //Ordena o vetor de ponteiros com base na idade
    qsort(vetorFuncionarios, cont, sizeof(struct Funcionarios*), ComprararIdadeCrescente);

    //Imprime a lista ordenada por idade
    printf("Lista de funcionarios ordenada por idade (do mais novo para o mais velho):\n");
    for (int i = 0; i < cont; i++) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               vetorFuncionarios[i]->nome, vetorFuncionarios[i]->endereco, vetorFuncionarios[i]->aniversario, vetorFuncionarios[i]->salario);
    }

    //Libera a memória alocada para o vetor de ponteiros
    free(vetorFuncionarios);
}

//Função de comparação para qsort, ordena funcionários com base na idade (do mais velho para o mais novo)
int comparaIdadeDecrescente(const void* a, const void* b) { //obs: declaramos como const void* para poder usar no qsort.
    //Converte ponteiros genéricos para ponteiros de struct Funcionarios
    struct Funcionarios* FuncionariosA = *((struct Funcionarios**)a);
    struct Funcionarios* FuncionariosB = *((struct Funcionarios**)b);

    //Calcula a idade dos funcionários usando a função auxiliar CalculaIdade
    int idadeA = CalculaIdade(FuncionariosA->aniversario);
    int idadeB = CalculaIdade(FuncionariosB->aniversario);

    //Retorna a diferença entre as idades (ordem do mais velho para o mais novo)
    return idadeB - idadeA;
}

//imprime a lista de funcionários ordenada por idade (do mais velho para o mais novo)
void exibeFuncionariosOrdemIdadeDecrescente(struct Funcionarios* topo) {
    //Conta o número de funcionários na lista
    int cont = 0;
    struct Funcionarios* Atual = topo;
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
    Atual = topo;
    for (int i = 0; i < cont; i++) {
        vetorFuncionarios[i] = Atual;
        Atual = Atual->prox;
    }

    //Ordena o vetor de ponteiros com base na idade (do mais velho para o mais novo)
    qsort(vetorFuncionarios, cont, sizeof(struct Funcionarios*), comparaIdadeDecrescente);

    //Imprime a lista ordenada por idade (do mais velho para o mais novo)
    printf("Lista de funcionarios ordenada por idade (do mais velho para o mais novo):\n");
    for (int i = 0; i < cont; i++) {
        printf("Nome: %s, Endereco: %s, Data de Nascimento: %s, Salario: R$%.2f\n",
               vetorFuncionarios[i]->nome, vetorFuncionarios[i]->endereco, vetorFuncionarios[i]->aniversario, vetorFuncionarios[i]->salario);
    }

    //Libera a memória alocada para o vetor de ponteiros
    free(vetorFuncionarios);
}

//Função para exibir um menu
int exibeMenu() {
    int opcao;
    printf("\n   |Menu Principal|");
    printf("\n1 - Intervalo Salarial\n");
    printf("2 - Exibir os funcionarios de A-Z\n");
    printf("3 - Exibir os funcionarios de Z-A\n");
    printf("4 - Transformar em AVL\n");
    printf("5 - Sair\n");
    printf("\nDigite a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

void auxiliarAVLOpcao(struct Funcionarios** topo, struct AVLno** avlraiz, int avlopcao) {
    float valormin, valormax; //Mova as declarações para fora do bloco switch

    switch (avlopcao) {
        case 1:
            //Código para a opção 1 (Intervalo Salarial)
            printf("\nDigite o valor minimo do intervalo salarial: ");
            scanf("%f", &valormin);
            printf("Digite o valor maximo do intervalo salarial: ");
            scanf("%f", &valormax);
            pesquisa_salarioAVL(*avlraiz, valormin, valormax);
            break;
        case 2:
            //Código para a opção 2 (IDADE maior para menor)
            exibeFuncionariosOrdemIdadeDecrescente(*topo);
            break;
        case 3:
            //Código para a opção 3 (IDADE menor para maior)
            exibeFuncionariosOrdemIdade(*topo);
            break;
        case 4:
            //Volta ao menu principal
            break;
        default:
            printf("\nOpcao invalida. Digite novamente.\n");
            break;
    }
}

void auxiliarOpcao(struct Funcionarios* topo, struct AVLno* avlraiz, int opcao) {

    switch (opcao) {
        case 1:
            system ("cls");
            float valormin, valormax;
            printf("Digite o valor minimo do intervalo salarial: ");
            scanf("%f", &valormin);
            printf("Digite o valor maximo do intervalo salarial: ");
            scanf("%f", &valormax);
            pesquisa_salario(topo, valormin, valormax);
            break;

        case 2:
            system ("cls");
            printf ("\n\nFUNCIONARIOS EM ORDEM ALFABETICA \n \n");
            exibeFuncionariosOrdemNome(topo); //Exibe a lista de funcionários de A a Z
            break;

        case 3:
            system ("cls");
            printf ("\n\n FUNCIONARIOS EM ORDEM ALFABETICA Z - A\n \n");
            exibeFuncionariosOrdemNomeContrario(topo); //Exibe a lista de funcionários de Z a A
            break;

        case 4:
            //Código para a opção 4 (Transformar em AVL)
            {
            int avlopcao;
            printf("\nTransformando em AVL....\nFinalizado!!!");
            do {
                printf("\n\n   |MENU AVL|");
                printf("\n 1- Intervalo Salarial");
                printf("\n 2- Exibir funcionario ordenados pela idade (Decrescente)");
                printf("\n 3- Exibir funcionario ordenados pela idade (Crescente)");
                printf("\n 4- Voltar");
                printf("\n\n Digite a opcao desejada: ");
                scanf("%d", &avlopcao);

                if (avlopcao != 1 && avlopcao != 2 && avlopcao != 3 && avlopcao != 4) {
                    printf("\n OPCAO INVALIDA DIGITE NOVAMENTE: ");
                }

                auxiliarAVLOpcao(&topo, &avlraiz, avlopcao);

            } while (avlopcao != 4);

            break;
            }

        case 5:
            //Libera a memória antes de sair
            system ("cls");
            printf ("\n\n Processos Finalizados!!! =)\n \n");
            exit(0); //return 0;
            break;

        default:
            printf("\nOpcao invalida. Digite novamente.\n");
    }
}

//Função para ler o arquivo e criar a lista de funcionários
struct Funcionarios* leituraArqFuncionarios(char* arqNome) {
    FILE* file = fopen(arqNome, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo"); //mensagem de erro caso não seja possível abrir o arquivo
        exit(EXIT_FAILURE);
    }

    struct Funcionarios* topo = NULL; //topo da lista encadeada
    char linha[256];

    fgets(linha, sizeof(linha), file); //Ignora a primeira linha

    while (fgets(linha, sizeof(linha), file)) {
        //Aloca memória para um novo funcionário
        struct Funcionarios* novoFuncionario = (struct Funcionarios*)malloc(sizeof(struct Funcionarios));
        if (novoFuncionario == NULL) {
            perror("Erro ao alocar memória para o funcionário"); //mensagem de erro caso não seja possível alocar memória
            exit(EXIT_FAILURE);
        }

        //Lê os dados do arquivo CSV e armazena nas variáveis da struct Funcionarios
        sscanf(linha, "%99[^,],%99[^,],%19[^,],%d,\"R$ %f\"", //Pega 99 espaços até encontrar a vigula. Salvando na variavel
               novoFuncionario->nome, novoFuncionario->aniversario, novoFuncionario->endereco, &novoFuncionario->numEndereco, &novoFuncionario->salario);
        novoFuncionario->salario *= 1000; //Multiplicação para lidar com o padrao americano de pontuacao
        novoFuncionario->prox = NULL; //Inicializa próx como nulo
        novoFuncionario->anterior = NULL; //Inicializa anterior como nulo

        //Insere o novo funcionário na lista encadeada
        inserirFuncionarios(&topo, novoFuncionario);
    }

    fclose(file); //fecha o arquivo
    return topo; //Retorna o topo da lista encadeada de funcionários
}

int main(int argc, char *argv[]) {

    if (argc != 2) { //verifica se foi passado o numero certo de argumetos
        printf("Experado: %s / <arquivo_csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *arquivo = argv[1];
    struct Funcionarios *topo = leituraArqFuncionarios(arquivo);
    struct AVLno *avlraiz = converteListaParaAVL(topo);

    for (;;) {
        int opcao = exibeMenu();
        auxiliarOpcao(topo, avlraiz, opcao);
    }

    return EXIT_SUCCESS;
}
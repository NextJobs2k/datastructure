#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Estrutura para representar um funcionário
 struct Employee {
    char name[100];
    char address[100];
    char birthdate[20];
    int addressNumber;
    float salary;
    struct Employee* next;
    struct Employee* prev;
};


// Função para pesquisar funcionários por intervalo salarial
void searchBySalaryRange(struct Employee* head, float valormin, float valormax) {
    struct Employee* current = head;

    printf("Funcionários com salário no intervalo de %.2f a %.2f:\n", valormin, valormax);  

    while (current != NULL) {
        if (current->salary >= valormin && current->salary <= valormax) {
            printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",
                   current->name, current->address, current->birthdate, current->salary);
        }
        current = current->next;
    }
}


// Função para inserir um funcionário ordenadamente na lista
void insertEmployee(struct Employee** head, struct Employee* newEmployee) {
    struct Employee* current = *head;




    if (*head == NULL || strcmp(newEmployee->name, current->name) < 0) {
        newEmployee->next = current;
        newEmployee->prev = NULL;
        if (current != NULL) {
            current->prev = newEmployee;
        }
        *head = newEmployee;
    } else {
        while (current->next != NULL && strcmp(newEmployee->name, current->next->name) > 0) {
            current = current->next;
        }

        newEmployee->next = current->next;
        newEmployee->prev = current;
        if (current->next != NULL) {
            current->next->prev = newEmployee;
        }
        current->next = newEmployee;
    }
}

// Função para exibir a lista de funcionários
void salar (struct Employee* head) {
    struct Employee* current = head;
    

    printf("Lista de funcionários ordenada por nome:\n");
    while (current != NULL) {

        printf("Nome: %s, Endereço: %s, %d,  Data de Nascimento: %s, Salário: %.2f\n",current->name, current->address, current->addressNumber, current->birthdate, current->salary);

        current = current->next;
    }
}

// Função para exibir a lista de funcionários
void displayEmployees(struct Employee* head) {
    struct Employee* current = head;
    

    printf("Lista de funcionários ordenada por nome:\n");
    while (current != NULL) {

        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",

               current->name, current->address, current->birthdate, current->salary);
        current = current->next;
    }
}

// Função para exibir a lista de funcionários ordenada por nome de A a Z
void displayEmployeesSortedByName(struct Employee* head) {
    struct Employee* current = head;

    printf("Lista de funcionários ordenada por nome (A a Z):\n");
    while (current != NULL) {
        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %f\n",

               current->name, current->address, current->birthdate, current->salary);
        current = current->next;
    }
}

// Função para exibir a lista de funcionários ordenada por nome de Z a A
void displayEmployeesSortedByNameReverse(struct Employee* head) {
    struct Employee* current = head;

    // Vá para o final da lista
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }

    printf("Lista de funcionários ordenada por nome (Z a A): \n");
    while (current != NULL) {

        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",

               current->name, current->address, current->birthdate, current->salary);
        current = current->prev;
    }
}
struct AVLNode {
    struct Employee* employee;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Função auxiliar para calcular a altura de um nó
int getHeight(struct AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função auxiliar para calcular o fator de balanceamento de um nó
int getBalanceFactor(struct AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Função auxiliar para criar um novo nó AVL
struct AVLNode* createAVLNode(struct Employee* employee) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    if (newNode == NULL) {
        perror("Erro ao alocar memória para o nó AVL");
        exit(EXIT_FAILURE);
    }
    newNode->employee = employee;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Função auxiliar para realizar uma rotação simples para a direita
struct AVLNode* rotateRight(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza alturas
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));

    return x;
}

// Função auxiliar para realizar uma rotação simples para a esquerda
struct AVLNode* rotateLeft(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza alturas
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));

    return y;
}

// Função para inserir um funcionário em uma árvore AVL
struct AVLNode* insertAVL(struct AVLNode* root, struct Employee* employee) {
    // Passo 1: Inserção normal de um BST
    if (root == NULL) {
        return createAVLNode(employee);
    }

    if (strcmp(employee->name, root->employee->name) < 0) {
        root->left = insertAVL(root->left, employee);
    } else if (strcmp(employee->name, root->employee->name) > 0) {
        root->right = insertAVL(root->right, employee);
    } else {
        // Ignora funcionários com o mesmo nome (pode ser ajustado conforme necessário)
        return root;
    }

    // Passo 2: Atualiza a altura do nó atual
    root->height = 1 + fmax(getHeight(root->left), getHeight(root->right));

    // Passo 3: Obtém o fator de balanceamento deste nó para verificar se é necessário reequilibrar
    int balance = getBalanceFactor(root);

    // 4 casos de desequilíbrio que precisam ser tratados

    // Caso da rotação simples à direita
    if (balance > 1 && strcmp(employee->name, root->left->employee->name) < 0) {
        return rotateRight(root);
    }

    // Caso da rotação simples à esquerda
    if (balance < -1 && strcmp(employee->name, root->right->employee->name) > 0) {
        return rotateLeft(root);
    }

    // Caso da rotação dupla à direita (rotação à esquerda seguida de rotação à direita)
    if (balance > 1 && strcmp(employee->name, root->left->employee->name) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Caso da rotação dupla à esquerda (rotação à direita seguida de rotação à esquerda)
    if (balance < -1 && strcmp(employee->name, root->right->employee->name) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Função para transformar uma lista duplamente encadeada em uma árvore AVL
struct AVLNode* convertListToAVL(struct Employee* head) {
    struct AVLNode* root = NULL;
    struct Employee* current = head;

    while (current != NULL) {
        root = insertAVL(root, current);
        current = current->next;
    }

    return root;
}
// Função para exibir a árvore AVL em ordem
void displayAVL(struct AVLNode* root) {

    if (root != NULL) {
        displayAVL(root->left);
        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",
               root->employee->name, root->employee->address, root->employee->birthdate, root->employee->salary);
        displayAVL(root->right);
    }
}

// Função para liberar a memória alocada para a árvore AVL
void freeAVL(struct AVLNode* root) {
    if (root != NULL) {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
}

// Função para pesquisar funcionários por intervalo salarial em uma árvore AVL
void searchBySalaryRangeAVL(struct AVLNode* root, float valormin, float valormax) {
    if (root != NULL) {
        // Se o salário estiver dentro do intervalo, imprime as informações do funcionário
        if (root->employee->salary >= valormin && root->employee->salary <= valormax) {
            printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",
                   root->employee->name, root->employee->address, root->employee->birthdate, root->employee->salary);
        }

        // Se o salário mínimo for menor que o salário do nó atual, busca na subárvore esquerda
        if (valormin < root->employee->salary) {
            searchBySalaryRangeAVL(root->left, valormin, valormax);
        }

        // Se o salário máximo for maior que o salário do nó atual, busca na subárvore direita
        if (valormax > root->employee->salary) {
            searchBySalaryRangeAVL(root->right, valormin, valormax);
        }
    }
}

// Função auxiliar para calcular a idade com base na data de nascimento
// Função auxiliar para calcular a idade com base na data de nascimento
int calculateAge(const char* birthdate) {
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);

    struct tm tm_birthdate;
    sscanf(birthdate, "%d/%d/%d", &tm_birthdate.tm_mday, &tm_birthdate.tm_mon, &tm_birthdate.tm_year);
    tm_birthdate.tm_year -= 1900; // Ajuste do ano (começa em 1900)
    tm_birthdate.tm_mon -= 1;     // Ajuste do mês (0-11)

    int age = tm_now->tm_year - tm_birthdate.tm_year;

    // Verifica se o aniversário já ocorreu este ano
    if (tm_now->tm_mon < tm_birthdate.tm_mon || (tm_now->tm_mon == tm_birthdate.tm_mon && tm_now->tm_mday < tm_birthdate.tm_mday)) {
        age--;
    }

    return age;
}

// Função para comparar funcionários com base na idade para a ordenação
int compareByAge(const void* a, const void* b) {
    struct Employee* employeeA = *((struct Employee**)a);
    struct Employee* employeeB = *((struct Employee**)b);

    int ageA = calculateAge(employeeA->birthdate);
    int ageB = calculateAge(employeeB->birthdate);

    return ageA - ageB;
}

// Função para imprimir a lista de funcionários ordenada por idade
void displayEmployeesSortedByAge(struct Employee* head) {
    // Conta o número de funcionários na lista
    int count = 0;
    struct Employee* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Aloca um array de ponteiros para funcionários
    struct Employee** employeesArray = (struct Employee**)malloc(count * sizeof(struct Employee*));
    if (employeesArray == NULL) {
        perror("Erro ao alocar memória para o array de funcionários");
        exit(EXIT_FAILURE);
    }

    // Preenche o array de ponteiros
    current = head;
    for (int i = 0; i < count; i++) {
        employeesArray[i] = current;
        current = current->next;
    }

    // Ordena o array de ponteiros com base na idade
    qsort(employeesArray, count, sizeof(struct Employee*), compareByAge);

    // Imprime a lista ordenada por idade
    printf("Lista de funcionários ordenada por idade:\n");
    for (int i = 0; i < count; i++) {
        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",
               employeesArray[i]->name, employeesArray[i]->address, employeesArray[i]->birthdate, employeesArray[i]->salary);
    }

    // Libera a memória alocada para o array de ponteiros
    free(employeesArray);
}

// Função para comparar funcionários com base na idade para a ordenação (do mais velho para o mais novo)
int compareByAgeReverse(const void* a, const void* b) {
    struct Employee* employeeA = *((struct Employee**)a);
    struct Employee* employeeB = *((struct Employee**)b);

    int ageA = calculateAge(employeeA->birthdate);
    int ageB = calculateAge(employeeB->birthdate);

    return ageB - ageA;
}

// Função para imprimir a lista de funcionários ordenada por idade (do mais velho para o mais novo)
void displayEmployeesSortedByAgeReverse(struct Employee* head) {
    // Conta o número de funcionários na lista
    int count = 0;
    struct Employee* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Aloca um array de ponteiros para funcionários
    struct Employee** employeesArray = (struct Employee**)malloc(count * sizeof(struct Employee*));
    if (employeesArray == NULL) {
        perror("Erro ao alocar memória para o array de funcionários");
        exit(EXIT_FAILURE);
    }

    // Preenche o array de ponteiros
    current = head;
    for (int i = 0; i < count; i++) {
        employeesArray[i] = current;
        current = current->next;
    }

    // Ordena o array de ponteiros com base na idade (do mais velho para o mais novo)
    qsort(employeesArray, count, sizeof(struct Employee*), compareByAgeReverse);

    // Imprime a lista ordenada por idade (do mais velho para o mais novo)
    printf("Lista de funcionários ordenada por idade (do mais velho para o mais novo):\n");
    for (int i = 0; i < count; i++) {
        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",
               employeesArray[i]->name, employeesArray[i]->address, employeesArray[i]->birthdate, employeesArray[i]->salary);
    }

    // Libera a memória alocada para o array de ponteiros
    free(employeesArray);
}

int main() {

  
    FILE* file = fopen("Dados_Funcionarios.csv", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    struct Employee* head = NULL;
    char line[256];

   fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {

        

        struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
        sscanf(line, "%99[^,],%99[^,],%19[^,], %d, \"R$ %f\"", newEmployee->name, newEmployee->birthdate, newEmployee->address,  &newEmployee->addressNumber , &newEmployee->salary  );
              newEmployee->salary = newEmployee->salary * 1000;
        newEmployee->next = NULL; 
        newEmployee->prev = NULL;

        insertEmployee(&head, newEmployee);
    }
    struct AVLNode* avlRoot = convertListToAVL(head);

    fclose(file);

   // displayEmployees(head);


 system ("cls");
 int opcao;
  
     printf ("1 - Intervalo Salarial \n 2 - DE A-Z \n 3- DE Z-A \n 4- Transformar EM AVL \n 5- Sair \n DIGITE A OPCAO DESEJADA:");
 scanf ("%d", &opcao);

int x = 0;

for (;;)
{



if (x > 0)
{
     printf ("\n\n 1 - Intervalo Salarial \n 2 - DE A-Z \n 3- DE Z-A \n 4- Transformar EM AVL \n 5- Sair \n DIGITE A OPCAO DESEJADA:");
 scanf ("%d", &opcao);
}


while (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4  && opcao != 5)
{
   printf ("\n OPCAO INVALIDO DIGITE NOVAMENTE: ");
    scanf ("%d", &opcao);
}


 if (opcao == 1 )
 {
     system ("cls");

    x++;
            float valormin, valormax;
        
        //float valormin1, valormax1;
    printf("Digite o valor minimo do intervalo salarial: ");
    scanf("%f", &valormin);
     
    printf("Digite o valor maximo do intervalo salarial: ");
    scanf("%f", &valormax);
    

    searchBySalaryRange(head, valormin, valormax);

 }
 
 else if ( opcao == 2)
 {
     system ("cls");

      x++;
       printf ("\n\nFUNCIONARIOS EM ORDEM ALFABETICA \n \n");

       displayEmployeesSortedByName(head);
 }
 

 else if ( opcao == 3)
 {
     system ("cls");

x++;
    printf ("\n\n FUNCIONARIOS EM ORDEM ALFABETICA Z - A\n \n");

   displayEmployeesSortedByNameReverse(head); // Exibe a lista de funcionários de Z a A

}


    else if ( opcao == 4)
 {
    
     int y = 0;
     
    for (;;)
{


   
    int opc;
     printf("MENU AVL: \n 1- Intervalo Salarial \n 2- MAIS VELHO AO MAIS NOVO \n 3- MAIS NOVO AO MAIS VELHO \n DIGITE:");
     scanf ("%d", &opc);

if (y > 0)
{
           system ("cls");

     printf ("\n\n 1 - Intervalo Salarial \n 2 - DE A-Z \n 3- DE Z-A \n 4- Transformar EM AVL \n 5- Sair \n 6- Voltar \n DIGITE A OPCAO DESEJADA:");
 scanf ("%d", &opcao);
}

   while (opc != 1 && opc != 2 && opc != 3  && opc != 4  && opc != 6)
   {
            system ("cls");

       printf ("\n OPCAO INVALIDO DIGITE NOVAMENTE: ");
    scanf ("%d", &opc);
    
     }

   if (opc == 1)
   {
       system ("cls");
    float valormin, valormax;

printf("\nDigite o valor mínimo do intervalo salarial: ");
scanf("%f", &valormin);

printf("\nDigite o valor máximo do intervalo salarial: ");
scanf("%f", &valormax);

printf("\nFuncionários com salário no intervalo de %.2f a %.2f:\n", valormin, valormax);
searchBySalaryRangeAVL(avlRoot, valormin, valormax);
    y++;
   }

   else if (opc == 2)
   {
       system ("cls");
       printf("\n IDADE maior para menor\n ");
    displayEmployeesSortedByAge(head);

        y++;

   }

   else if (opc == 3)
   {
       system ("cls");
    displayEmployeesSortedByAgeReverse(head);
        y++;

   }

      else if (opc == 6)
   {
       y++;
       break;
       

   }
      break;
    
       if (opc == 4)
   {
    opcao = 5;
     break;
   }
   
    break;

    

        printf("\n Arvore AVL:\n");
   // displayAVL(avlRoot);

    //transformar em avl
}
 }


     else if ( opcao == 5) //sair
 {
     system ("cls");

       printf ("\n\n XAUUUUUU =)\n \n");

    break;
    }
}


//16;30
   


    // Libere a memória alocada para os funcionários (implementação de limpeza adequada deve ser feita)

    return 0;
}

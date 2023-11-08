#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura para representar um funcionário
 struct Employee {
    char name[100];
    char address[100];
    char birthdate[20];
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

        printf("Salário: %.2f\n",  current->salary);
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
        printf("Nome: %s, Endereço: %s, Data de Nascimento: %s, Salário: %.2f\n",

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



int main() {


    FILE* file = fopen("Dados_Funcionarios.csv", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    struct Employee* head = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
        sscanf(line, "\"%99[^\"]\",\"%11[^\"]\",\"%99[^\"]\",%d,\"%f\"", newEmployee->name, newEmployee->birthdate, newEmployee->address, &newEmployee->addressNumber, &newEmployee->salary);
        newEmployee->next = NULL;
        newEmployee->prev = NULL;

        insertEmployee(&head, newEmployee);
    }

    fclose(file);

   // displayEmployees(head);

   salar (head);


        float valormin, valormax;
    printf("Digite o valor minimo do intervalo salarial: ");
    scanf("%f", &valormin);
    printf("Digite o valor maximo do intervalo salarial: ");
    scanf("%f", &valormax);



    searchBySalaryRange(head, valormin, valormax);




    printf ("\n\nFUNCIONARIOS EM ORDEM ALFABETICA \n \n");

      //  displayEmployeesSortedByName(head);


   

    printf ("\n\n FUNCIONARIOS EM ORDEM ALFABETICA Z - A\n \n");

   //displayEmployeesSortedByNameReverse(head); // Exibe a lista de funcionários de Z a A

    // Libere a memória alocada para os funcionários (implementação de limpeza adequada deve ser feita)

    return 0;
}

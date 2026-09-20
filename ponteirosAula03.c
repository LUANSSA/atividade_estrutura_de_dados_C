#include <stdio.h>
#include <string.h>


// Criando estrutura sem apelido
struct Pessoa{
    char nome[30];
    int idade;
    char nacionalidade[50];
};

// Criando estrutura com apelido
typedef struct {
    char profissao[100];
    float salario;

} Profissao;


// Pessoa
void inserePessoa(struct Pessoa *ptr, char nome[], int idade, char nacionalidade[]);
void imprimePessoa(const struct Pessoa *ptr);

// Profissão
void insereProfissao(Profissao *ptr, char profissao[], float salario);
void imprimeProfissao(Profissao *ptr);


// Função principal
int main(){

    // Pessoa
    struct Pessoa pessoa1;
    inserePessoa(&pessoa1, "Luan Souza", 29, "Brasileiro");
    imprimePessoa(&pessoa1);

    // Profissão
    Profissao profissao1;
    insereProfissao(&profissao1, "Análise e Desenvolvimento de Sistemas", 4500.00);
    imprimeProfissao(&profissao1);
    
    // Testando
    printf("\n\n****Teste****\n");
    struct Pessoa *ptr = &pessoa1;
    printf("%p\n", ptr);
    printf("%s\n", ptr->nome);
    // Testando o ponteiro
    char produto[] = "Bicicleta";
    char *ptr_produto = produto;
    printf("%p\n", (void *)ptr_produto);
    printf("%p\n", &produto[0]);

}

// Inserindo pessoa
void inserePessoa(struct Pessoa *ptr, char nome[], int idade, char nacionalidade[]){
    // Nome
    strcpy(ptr->nome, nome);
    // Idade
    ptr->idade = idade;
    // Nacionalidade
    strcpy(ptr->nacionalidade, nacionalidade);
}

// Imprimindo pessoa
void imprimePessoa(const struct Pessoa *ptr){
    printf("Endereço de memória: %p\n", ptr);
    printf("Nome: %s\n", ptr->nome);
    printf("Idade : %d\n", ptr->idade);
    printf("Nacionalidade: %s\n", ptr->nacionalidade);
}

// Insere profissão
void insereProfissao(Profissao *ptr, char profissao[], float salario){
    // Profissão
    strcpy(ptr->profissao, profissao);
    // Salário
    ptr->salario = salario;
}

// Imprime profissão
void imprimeProfissao(Profissao *ptr){
    printf("Profissão: %s\n", ptr->profissao);
    printf("Salário : R$%.2f\n", ptr->salario);
}
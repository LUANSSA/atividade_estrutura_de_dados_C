#include <stdio.h>
#include <string.h>

// Estrutura
struct Estudante{
    int matricula;
    char nome[30];
    float valorMensalidade;
    char dataBacharelado[30];
};

// Monstrando dados da estutura
void exibindoEstrutura(const struct Estudante *ptr_estudante);

int main(){

    // Declara variável do tipo estrutura estudante
    struct Estudante luan;
    
    // Guardando valores nos campos da estrutura
    luan.matricula = 22231;
    strcpy(luan.nome, "Luan Souza");
    luan.valorMensalidade = 240.00;
    strcpy(luan.dataBacharelado, "02/12/2027");

    // Mostrando estrutura
    printf("Endereço de memória da estrutura: %p\n", &luan);
    printf("Campo matrícula: %d\n", luan.matricula);
    printf("Campo nome: %s\n", luan.nome);
    printf("Campo valor mensalidade: %f\n", luan.valorMensalidade);
    printf("Campo data bacharelado: %s\n", luan.dataBacharelado);

    printf("\n\n");


    // Monstrando dados da estutura
    exibindoEstrutura(&luan);

    printf("\n\nFim do programa.\n\n");
    return 0;
}

// Monstrando dados da estutura - const serve para não permitir alteração nos dados
void exibindoEstrutura(const struct Estudante *ptr_estudante){

    // Mostrando estrutura
    printf("Endereço de memória da estrutura: %p\n", ptr_estudante);
    printf("Campo matrícula: %d\n", ptr_estudante->matricula);
    printf("Campo nome: %s\n", ptr_estudante->nome);
    printf("Campo valor mensalidade: %f\n", ptr_estudante->valorMensalidade);
    printf("Campo data bacharelado: %s\n", ptr_estudante->dataBacharelado);
}
#include <stdio.h>

// Função para exibir conteúdo
void exibindo(int var, int *ptr);
void atualizandoValor(int *p, int valor);

int main(){
    // Variável
    int var = 15;
    // Ponteiro
    int *ptr;

    // Atribuo ao ponteiro o endereço de var
    ptr = &var;
    exibindo(var, ptr);

    // Atualizando o conteúdo que var guarda.
    *ptr = 73;
    exibindo(var, ptr);

    // Atualizando o conteúdo que var guarda.
    atualizandoValor(ptr, 100);
    exibindo(var, ptr);


    return 0;
}

// Função para exibir conteúdo
void exibindo(int var, int *ptr){

    // Mostrando variável
    printf("conteúdo de var = %d\n", var);
    printf("endereço de var = %p\n", &var);
    // Mostrando ponteiro
    printf("conteúdo apontado por ptr = %d\n", *ptr);
    printf("endereço apontado por ptr = %p\n", ptr);
    // Mostrando o endereço de memória do ponteiro
    printf("endereço do ponteiro ptr = %p\n\n", &ptr);
}

void atualizandoValor(int *ptr, int valor){
    *ptr = valor;
}
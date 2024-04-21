//
// Created by Vitor Frango on 21/04/2024.
//

/*
 * Os testes de unidade verificam funcionalidades individuais para garantir que cada parte f
 * uncione como esperado. Vamos definir um arquivo separado para cada módulo e criar
 * funções de teste para validar cada função ou recurso.

Para gestao_livros.c:

 testes para funções como adicionar_livro, remover_livro, listar_livros
 * */


#include <stdio.h>
#include <string.h>


#include <assert.h>
#include "gestao_livros.h"

void test_adicionar_livro() {
    // Configuração
    Livro livro;
    livro.id = 1;
    strcpy(livro.titulo, "Livro de Teste");
    strcpy(livro.autor, "Autor de Teste");

    // Teste
    int resultado = adicionar_livro(&livro);
    assert(resultado == 0); // Espera-se que a adição seja bem-sucedida

    // Teardown (opcional, se necessário)
}

int main() {
    test_adicionar_livro();
    return 0; // Indica sucesso
}

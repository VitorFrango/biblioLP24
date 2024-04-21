//
// Created by Vitor Frango on 21/04/2024.
//


/*

 * Os testes de unidade verificam funcionalidades individuais para garantir que cada parte f
 * uncione como esperado. Vamos definir um arquivo separado para cada módulo e criar
 * funções de teste para validar cada função ou recurso.

Para gestao_emprestimos.c:

 testes para funções como adicionar_livro, remover_livro, listar_livros
 * */
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "gestao_emprestimos.h"
#include "gestao_livros.h"

void test_empresta_livro() {
    Livro livro;
    livro.id = 1;

    Livro *livros = (Livro *) malloc(sizeof(Livro));
    *livros = livro;

    int contador_livro = 1;

    Emprestimo *emprestimos = NULL;
    int contador_emprestimo = 0;

    empresta_livro(livros, 1, &emprestimos, &contador_emprestimo);

    assert(contador_emprestimo == 1);
}

int main() {
    test_empresta_livro();
    return 0;
}
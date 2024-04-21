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

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "gestao_emprestimos.h"
#include "gestao_livros.h"

void test_adicionar_livro() {
    Livro livro;
    livro.id = 1;

    // Supõe que tem um conjunto inicial de 5 livros
    Livro *livros = (Livro *) malloc(sizeof(Livro) * 5);

    int contador_livro = 5;

    adicionar_livro(&livros, &livro, &contador_livro);

    // verifica se o livro foi adicionado com sucesso
    assert(contador_livro == 6);
    assert(livros[5].id == 1);
}

int main() {
    test_adicionar_livro();
    return 0;
}
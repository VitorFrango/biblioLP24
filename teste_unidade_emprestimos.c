//
// Created by Vitor Frango on 21/04/2024.
//


/*
 * /*
 * Os testes de unidade verificam funcionalidades individuais para garantir que cada parte f
 * uncione como esperado. Vamos definir um arquivo separado para cada módulo e criar
 * funções de teste para validar cada função ou recurso.

Para gestao_emprestimos.c:

 testes para funções como adicionar_livro, remover_livro, listar_livros
 * */

#include <stdio.h>
#include <string.h>

#include <assert.h>
#include "gestao_emprestimos.h"

void test_emprestar_livro() {
    // Configuração
    Emprestimo emprestimo;
    emprestimo.livro_id = 1;
    emprestimo.usuario_id = 1;

    // Teste
    int resultado = emprestar_livro(&emprestimo);
    assert(resultado == 0); // Espera-se que o empréstimo seja bem-sucedido
}

int main() {
    test_emprestar_livro();
    return 0;
}

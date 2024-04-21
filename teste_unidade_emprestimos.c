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
#include "gestao_emprestimos.h"
#include "gestao_livros.h"

void test_emprestar_livro() {
    // Configuração
    // Criando uma lista de livros para testar
    Livro livro;
    livro.id = 1;
    Livro* livros = NULL;
    int count = 0;

    adicionar_livro(&livros, &count);

    Emprestimo* emprestimos = NULL;
    int emprestimo_count = 0;
    empresta_livro(livros, count, &emprestimos, &emprestimo_count);

    // Criando um empréstimo para testar
    Emprestimo novo_emprestimo;
    novo_emprestimo.id = 1;

    // Teste do empréstimo
    empresta_livro(
            livros,
            count,
            &emprestimos, // Apontador para a lista de empréstimos
            &emprestimo_count // Apontador para o contador de empréstimos
            &emprestimo_count // Apontador para o contador de empréstimos
    );

}

int main() {
    test_emprestar_livro(); // Executa o teste
    return 0; // Retorno indicando sucesso
}

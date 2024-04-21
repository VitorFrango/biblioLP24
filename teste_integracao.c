//
// Created by Vitor Frango on 21/04/2024.
//

/*
verifica se vários componentes funcionam juntos como esperado.
 Para isso, seria ideal criar um arquivo separado para testar interações entre módulos.

Exemplo para Testes de Integração:

Este teste integraria o processo de adicionar um livro e emprestá-lo.
 * */

#include <stdio.h>
#include <string.h>

#include <assert.h>
#include "gestao_livros.h"
#include "gestao_emprestimos.h"

void test_integra_livro_emprestimo() {
    // Configuração
    Livro livro;
    livro.id = 1;
    strcpy(livro.titulo, "Livro Integrado");
    strcpy(livro.autor, "Autor Integrado");

    adicionar_livro(&livro);

    Emprestimo emprestimo;
    emprestimo.livro_id = 1;
    emprestimo.usuario_id = 1;

    // Teste de integração
    int resultado = emprestar_livro(&emprestimo);
    assert(resultado == 0); // Espera-se que a integração funcione
}

int main() {
    test_integra_livro_emprestimo();
    return 0;
}

//
// Created by Vitor Frango on 21/04/2024.
//

/*
verifica se vários componentes funcionam juntos como esperado.
 Para isso, seria ideal criar um arquivo separado para testar interações entre módulos.

Exemplo para Testes de Integração:

Este teste integraria o processo de adicionar um livro e emprestá-lo.
 * */
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "gestao_emprestimos.h"
#include "gestao_livros.h"

void test_remover_livro() {
    Livro livro;
    livro.id = 1;

    Livro *livros = (Livro *) malloc(sizeof(Livro) * 6);
    livros[5] = livro;

    int contador_livro = 6;

    remover_livro(&livros, 1, &contador_livro);

    assert(contador_livro == 5);
}

int main() {
    test_remover_livro();
    return 0;
}
//
// Created by Vitor Frango on 25/04/2024.
//

/*
 * gcc -o testes_integracao testes_integracao.c gestao_livros.c gestao_emprestimos.c gera_relatorios.c interface.c
    * ./testes_integracao

 */

#include <stdio.h>
#include "gestao_livros.h"
#include "gestao_emprestimos.h"
#include "gera_relatorios.h"
#include "interface.h"

// Teste para integração entre gestao_livros e gestao_emprestimos
void teste_integra_livro_emprestimo() {
    // Adicionar um livro
    int resultado = adicionar_livro("Livro Integração", "Autor Integração");
    imprimir_resultado("Teste de adicionar livro para integração", resultado == 0);

    // Emprestar o livro
    resultado = emprestar_livro("Livro Integração", "Usuario Integração");
    imprimir_resultado("Teste de emprestar livro para integração", resultado == 0);

    // Devolver o livro
    resultado = devolver_livro("Livro Integração");
    imprimir_resultado("Teste de devolver livro para integração", resultado == 0);
}

// Teste para integração entre gestao_emprestimos e gera_relatorios
void teste_integra_emprestimo_relatorio() {
    // Emprestar um livro
    int resultado = emprestar_livro("Livro Integração", "Usuario Integração");
    imprimir_resultado("Teste de emprestar livro para relatório", resultado == 0);

    // Gerar um relatório
    resultado = gerar_relatorio();
    imprimir_resultado("Teste de gerar relatório para integração", resultado == 1);
}

// Função principal para executar testes de integração
int main() {
    printf("Executando testes de integração...\n");

    teste_integra_livro_emprestimo();
    teste_integra_emprestimo_relatorio();

    return 0;
}

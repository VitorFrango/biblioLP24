//
// Created by Vitor Frango on 25/04/2024.
//

/*
 * Para executar os testes unitários, execute o seguinte comando:
    gcc -o testes_unitarios testes_unitarios.c gestao_livros.c gestao_emprestimos.c gera_relatorios.c interface.c
    ./testes_unitarios
 */

#include <stdio.h>
#include "gestao_livros.h"
#include "gestao_emprestimos.h"
#include "gera_relatorios.h"
#include "interface.h"

// Função auxiliar para imprimir resultados dos testes
void imprimir_resultado(char *descricao, int resultado) {
    if (resultado) {
        printf("SUCESSO: %s\n", descricao);
    } else {
        printf("FALHA: %s\n", descricao);
    }
}

// Testes para gestao_livros.c
void teste_adicionar_livro() {
    // Implementação do teste para adicionar um livro
    // Exemplo: Se a função deve retornar 0 para sucesso
    int resultado = adicionar_livro("Livro Teste", "Autor Teste");
    imprimir_resultado("Teste de adicionar livro", resultado == 0);
}

void teste_remover_livro() {
    // Implementação do teste para remover um livro
    // Exemplo: Se a função deve retornar 0 para sucesso
    int resultado = remover_livro("Livro Teste");
    imprimir_resultado("Teste de remover livro", resultado == 0);
}

// Testes para gestao_emprestimos.c
void teste_emprestar_livro() {
    // Implementação do teste para emprestar um livro
    // Exemplo: Se a função deve retornar 0 para sucesso
    int resultado = emprestar_livro("Livro Teste", "Usuario Teste");
    imprimir_resultado("Teste de emprestar livro", resultado == 0);
}

void teste_devolver_livro() {
    // Implementação do teste para devolver um livro
    // Exemplo: Se a função deve retornar 0 para sucesso
    int resultado = devolver_livro("Livro Teste");
    imprimir_resultado("Teste de devolver livro", resultado == 0);
}

// Testes para gera_relatorios.c
void teste_gerar_relatorio() {
    // Implementação do teste para gerar um relatório
    // Exemplo: Se a função deve retornar um valor específico
    int resultado = gerar_relatorio();
    imprimir_resultado("Teste de gerar relatório", resultado == 1);
}

// Função principal para executar testes unitários
int main() {
    printf("Executando testes unitários...\n");

    teste_adicionar_livro();
    teste_remover_livro();
    teste_emprestar_livro();
    teste_devolver_livro();
    teste_gerar_relatorio();

    return 0;
}

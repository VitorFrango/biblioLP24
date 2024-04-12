//
// Created by Vitor Frango on 12/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gera_relatorios.h"
#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include "io_dados.h"
#include "principal.h"

#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_GENERO 50

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int copias;
} Livro;


int main() {
    livro*livros = NULL;
    int livro_count = 0;

    emprestimo *emprestimos = NULL;
    int emprestimo_count = 0;

    inicializar_biblioteca("livros.csv", &livros, &livro_count);

    int choice;
    do {
        printf("1. Adicionar Livro\n"
               "2. Listar Livros\n"
               "3. Emprestar Livro\n"
               "4. Devolver Livro\n"
               "5. Renovar Empréstimo\n"
               "6. Relatório de Livros Mais Emprestados\n"
               "7. Relatório de Livros Não Devolvidos\n"
               "8. Relatório de Maiores Locatários\n"
               "9. Salvar Alterações\n"
               "0. Sair e Salvar\n"
               "Escolha uma opção: ");

        scanf("%d", &choice);
        getchar();  // Limpa buffer do stdin

        switch (choice) {
            case 1:
                adicionar_livro(&livros, &livro_count);
                break;
            case 2:
                pesquisar_livros(livros, livro_count);
                break;
            case 3:
                inicializar_emprestimos(livros, livro_count, &emprestimos, &emprestimo_count);
                registrar_emprestimo(livros, emprestimos, emprestimo_count, livro_count);
                break;
            case 4:
                printf("Digite o ID do empréstimo para devolução: ");
                int emprestimo_id;
                scanf("%d", &emprestimo_id);
                devolver_livro(livros, emprestimos, &emprestimo_count, emprestimo_id);
                break;
            case 5:
                printf("Digite o ID do empréstimo para renovação: ");
                scanf("%d", &emprestimo_id);
                renovar_emprestimo(emprestimos, emprestimo_count, emprestimo_id);
                break;
            case 6:
                relatorio_livros_mais_emprestados(livros, livro_count);
                break;
            case 7:
                relatorio_livros_nao_devolvidos(emprestimos, emprestimo_count, livros);
                break;
            case 8:
                relatorio_usuarios_com_mais_emprestimos(emprestimos, emprestimo_count);
                break;
            case 9:
                gravar_biblioteca("livros.csv", livros, livro_count);
                finalizar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count, livros);
                printf("Dados salvos com sucesso!\n");
                break;
            case 0:
                gravar_biblioteca("livros.csv", livros, livro_count);
                finalizar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count, livros);
                printf("Saindo e salvando dados...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (choice != 0);

    free(livros);
    free(emprestimos);
    return 0;
}

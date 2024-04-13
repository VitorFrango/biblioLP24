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
    Livro *livros = NULL;
    int livro_count = 0;
    Emprestimo *emprestimos = NULL;
    int emprestimo_count = 0;

    inicializar_biblioteca("livros.csv", &livros, &livro_count);

    int choice;
    do {
        printf("1. Adicionar Livro\n2. Listar Livros\n3. Emprestar Livro\n4. Devolver Livro\n5. Renovar Empréstimo\n6. Relatório de Livros Mais Emprestados\n7. Relatório de Livros Não Devolvidos\n8. Relatório de Maiores Locatários\n9. Salvar Alterações\n0. Sair e Salvar\nEscolha uma opção: ");
        scanf("%d", &choice);
        getchar();  // Limpa buffer do stdin

        switch (choice) {
            case 1:
                adicionar_livro(&livros, &livro_count);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                printf("Digite o ID do empréstimo para devolução: ");
                int loan_id;
                scanf("%d", &loan_id);

                break;
            case 5:
                printf("Digite o ID do empréstimo para renovação: ");
                scanf("%d", &loan_id);

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
            case 9:

                printf("Dados salvos com sucesso!\n");
                break;
            case 0:
                savelivrosToFile("livros.csv", livros, livro_count);
                saveLoansToFile("loans.csv", emprestikmos, emprestimo_count, livros);
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
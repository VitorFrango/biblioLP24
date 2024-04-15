//
// Created by Vitor Frango on 12/04/2024.
//

#include <stdio.h>
#include <stdlib.h>

#include "principal.h"




int main() {
        Livro *livros; // Ponteiro para array de livros
        livros = NULL; // Inicializa ponteiro com NULL
        int livro_count = 0; // Contador de livros
        Emprestimo *emprestimos = NULL; // Ponteiro para array de empréstimos
        int emprestimo_count = 0; // Contador de empréstimos

    // Inicializa a biblioteca com os dados do arquivo livros.csv
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
               "0. Sair e Salvar\nEscolha uma opção: ");

        scanf("%d", &choice);
        getchar();  // Limpa buffer do stdin

        switch (choice) {
            case 1:
                adicionar_livro(&livros, &livro_count);
                break;
            case 2:
                pesquisar_livros("livros.csv");
                break;
            case 3:
                empresta_livro(livros, livro_count, &emprestimos, &emprestimo_count);

                break;
            case 4:
                devolver_livro(livros, livro_count, &emprestimos, &emprestimo_count);
                break;
            case 5:
                renovar_emprestimo(emprestimos, emprestimo_count);;
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
                guardar_livros("livros.csv", livros, livro_count);
                guardar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count);
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
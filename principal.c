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

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_GENRE 50

typedef struct {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char genre[MAX_GENRE];
    int copies;
} Book;


int main() {
    Book *books = NULL;
    int book_count = 0;
    Loan *loans = NULL;
    int loan_count = 0;

    loadBooksFromFile("books.csv", &books, &book_count);

    int choice;
    do {
        printf("1. Adicionar Livro\n2. Listar Livros\n3. Emprestar Livro\n4. Devolver Livro\n5. Renovar Empréstimo\n6. Relatório de Livros Mais Emprestados\n7. Relatório de Livros Não Devolvidos\n8. Relatório de Maiores Locatários\n9. Salvar Alterações\n0. Sair e Salvar\nEscolha uma opção: ");
        scanf("%d", &choice);
        getchar();  // Limpa buffer do stdin

        switch (choice) {
            case 1:
                addBook(&books, &book_count);
                break;
            case 2:
                printBooks(books, book_count);
                break;
            case 3:
                loanBook(books, book_count, &loans, &loan_count);
                updateLoanCount(books, loans, loan_count, book_count);
                break;
            case 4:
                printf("Digite o ID do empréstimo para devolução: ");
                int loan_id;
                scanf("%d", &loan_id);
                returnBook(books, loans, &loan_count, loan_id);
                break;
            case 5:
                printf("Digite o ID do empréstimo para renovação: ");
                scanf("%d", &loan_id);
                renewLoan(loans, loan_count, loan_id);
                break;
            case 6:
                reportMostLoanedBooks(books, book_count);
                break;
            case 7:
                reportUnreturnedBooks(loans, loan_count, books);
                break;
            case 8:
                reportTopBorrowers(loans, loan_count);
                break;
            case 9:
                saveBooksToFile("books.csv", books, book_count);
                saveLoansToFile("loans.csv", loans, loan_count, books);
                printf("Dados salvos com sucesso!\n");
                break;
            case 0:
                saveBooksToFile("books.csv", books, book_count);
                saveLoansToFile("loans.csv", loans, loan_count, books);
                printf("Saindo e salvando dados...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (choice != 0);

    free(books);
    free(loans);
    return 0;
}

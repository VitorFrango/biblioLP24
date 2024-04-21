//
// Created by Vitor Frango on 12/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gera_relatorios.h"


void livros_mais_emprestados(Emprestimo *emprestimos, int emprestimo_count) {

    // Carregar emprestimos
    carregar_emprestimos("emprestimos.csv", &emprestimos, &emprestimo_count);

    LivroCount *counts = NULL;
    int num_livros = 0;
    for(int i = 0; i < emprestimo_count; i++) {
        int found = 0;
        for(int j = 0; j < num_livros; j++) {
            if(strcmp(emprestimos[i].titulo, counts[j].titulo) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if(!found) {
            counts = (LivroCount *) realloc(counts, (num_livros + 1) * sizeof(LivroCount));
            strcpy(counts[num_livros].titulo, emprestimos[i].titulo);
            counts[num_livros].count = 1;
            num_livros++;
        }
    }

    // encontrar o livro com o maior número de empréstimos
    int max_emprestimos = 0;
    for(int i = 0; i < num_livros; i++) {
        if(counts[i].count > max_emprestimos) {
            max_emprestimos = counts[i].count;
        }
    }

    // imprimir os livros com o maior número de empréstimos
    for(int i = 0; i < num_livros; i++) {
        if(counts[i].count == max_emprestimos) {
            printf("Livro: %s\n", counts[i].titulo);
            printf("Quantidade de emprestimos: %d\n", counts[i].count);
        }
    }

    free(counts); // Liberação de memória
}


void relatorio_livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count) {
    printf("Livros não devolvidos:\n");
    for (int i = 0; i < emprestimo_count; i++){
        if (emprestimos[i].is_devolvido == 0)
            printf("Livro: %s\n", emprestimos[i].titulo);
        printf("Usuario: %s\n", emprestimos[i].user);
    }
}

void locatarios_com_mais_livros_emprestados(Emprestimo *emprestimos, int emprestimo_count) {
    UserCount *counts = NULL;
    int num_users = 0;
    for(int i = 0; i < emprestimo_count; i++) {
        int found = 0;
        for(int j = 0; j < num_users; j++) {
            if(strcmp(emprestimos[i].user, counts[j].nome) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if(!found) {
            counts = (UserCount *) realloc(counts, (num_users + 1) * sizeof(UserCount));
            strcpy(counts[num_users].nome, emprestimos[i].user);
            counts[num_users].count = 1;
            num_users++;
        }
    }

    // encontrar o locatario com o maior número de empréstimos
    int max_emprestimos = 0;
    for(int i = 0; i < num_users; i++) {
        if(counts[i].count > max_emprestimos) {
            max_emprestimos = counts[i].count;
        }
    }

    // imprimir os locatarios  com o maior número de empréstimos
    for(int i = 0; i < num_users; i++) {
        if(counts[i].count == max_emprestimos) {
            printf("Usuário: %s\n", counts[i].nome);
            printf("Quantidade de emprestimos: %d\n", counts[i].count);
        }
    }

    free(counts); // Liberação de memória
}
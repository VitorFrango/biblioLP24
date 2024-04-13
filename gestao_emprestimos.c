//
// Created by Vitor Frango on 12/04/2024.
// Funções para gerir empréstimos.

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestao_livros.h"
#include "principal.h"
#include "gera_relatorios.h"
#include "io_dados.h"
#include "gestao_emprestimos.h"

typedef struct {
    char titulo[MAX_TITULO];
    char usuario[MAX_USUARIO];
    time_t data_emprestimo;
    time_t data_devolucao;
} Emprestimo;

void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    int livro_id;
    printf("Digite o ID do livro a ser emprestado: ");
    scanf("%d", &livro_id);
    getchar();  // Clear the stdin buffer
    if (livro_id < 0 || livro_id >= count) {
        printf("ID de livro inválido.\\n");
        return;
    }
    if (livros[livro_id].copias <= 0) {
        printf("Livro sem cópias disponíveis.\\n");
        return;
    }
    livros[livro_id].copias--;
    *emprestimos = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
    if (*emprestimos == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o empréstimo.\\n");
        return;  // Avoid using exit(1); handle error gracefully
    }
    strcpy((*emprestimos)[*emprestimo_count].titulo, livros[livro_id].titulo);
    printf("Digite o nome do usuário: ");
    fgets((*emprestimos)[*emprestimo_count].usuario, MAX_USUARIO, stdin);
    (*emprestimos)[*emprestimo_count].usuario[strcspn((*emprestimos)[*emprestimo_count].usuario, "\\n")] = '\\0';  // Remove newline
    time_t current_time;
    time(&current_time);
    (*emprestimos)[*emprestimo_count].data_emprestimo = current_time;
    (*emprestimos)[*emprestimo_count].data_devolucao = current_time + 604800;  // 7 days
    (*emprestimo_count)++;
}


void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    char titulo[MAX_TITULO];
    printf("Digite o título do livro a ser devolvido: ");
    fgets(titulo, MAX_TITULO, stdin);
    titulo[strcspn(titulo, "\\n")] = '\\0';  // Remove newline
    for (int i = 0; i < *emprestimo_count; i++) {
        if (strcmp((*emprestimos)[i].titulo, titulo) == 0) {
            for (int j = 0; j < count; j++) {
                if (strcmp(livros[j].titulo, (*emprestimos)[i].titulo) == 0) {
                    livros[j].copias++;
                    break;
                }
            }
            // Remove the returned loan from the array
            for (int k = i; k < *emprestimo_count - 1; k++) {
                (*emprestimos)[k] = (*emprestimos)[k + 1];
            }
            *emprestimos = realloc(*emprestimos, (*emprestimo_count - 1) * sizeof(Emprestimo));
            if (*emprestimos == NULL) {
                fprintf(stderr, "Erro ao alocar memória para ajustar o empréstimo.\\n");
                return;  // Avoid using exit(1); handle error gracefully
            }
            (*emprestimo_count)--;
            return;
        }
    }
    printf("Livro não encontrado.\\n");
}


void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count, int emprestimo_id) {
    if (emprestimo_id >= 0 && emprestimo_id < emprestimo_count) {
        emprestimos[emprestimo_id].data_devolucao += 604800;  // Renew for an additional 7 days
    } else {
        printf("ID de empréstimo inválido.\\n");
    }
}


void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count) {
    time_t current_time;
    time(&current_time);
    for (int i = 0; i < *emprestimo_count; i++) {
        if (current_time > (*emprestimos)[i].data_devolucao) {
            for (int j = 0; j < livro_count; j++) {
                if (strcmp(livros[j].titulo, (*emprestimos)[i].titulo) == 0) {
                    livros[j].copias++;
                    break;
                }
            }
            // Remove the overdue loan from the array
            for (int k = i; k < *emprestimo_count - 1; k++) {
                (*emprestimos)[k] = (*emprestimos)[k + 1];
            }
            *emprestimos = realloc(*emprestimos, (*emprestimo_count - 1) * sizeof(Emprestimo));
            if (*emprestimos == NULL) {
                printf("Erro ao alocar memória para o empréstimo.\n");
                exit(1);
            }
            (*emprestimo_count)--;
        }
    }
};

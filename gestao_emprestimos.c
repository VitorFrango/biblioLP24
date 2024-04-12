//
// Created by Vitor Frango on 12/04/2024.
//Funções para gerIR empréstimos.

#include <time.h>
#include "gestao_emprestimos.h"
#include <stdio.h>
#include <stdlib.h>

#include "gestao_livros.h"
#include "principal.h"
#include "gera_relatorios.h"
#include "io_dados.h"
#include "gestao_emprestimos.h"

void inicializar_emprestimos(void empresta_livro(Livro *livro, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    int livro_id;
    printf("Digite o ID do livro a ser emprestado: ");
    scanf("%d", &livro_id);
    getchar();  // Limpa buffer do stdin

    if (livro_id >= 0 && livro_id < count) {
        *emprestimos = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
        if (*emprestimos == NULL) {
            printf("Erro ao alocar memória para o empréstimo.\n");
            exit(1);
        }

        printf("Digite o nome do locatario: ");
        fgets((*emprestimos)[*emprestimo_count].usuario, MAX_USUARIO, stdin);
        (*emprestimos)[*emprestimo_count].data_emprestimo = time(NULL);
        (*emprestimos)[*emprestimo_count].data_devolucao =
                (*emprestimos)[*emprestimo_count].data_emprestimo + 604800;  // 7 dias
        strcpy((*emprestimos)[*emprestimo_count].titulo, livro[livro_id].titulo);
        (*emprestimo_count)++;
    } else {
        printf("ID de livro inválido.\n");
    }
}

void devolver_livro(Livro *Livro, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    char titulo[MAX_TITULO];
    printf("Digite o título do livro a ser devolvido: ");
    fgets(titulo, MAX_TITULO, stdin);
    for (int i = 0; i < *emprestimo_count; i++) {
        if (strcmp((*emprestimos)[i].titulo, titulo) == 0) {
            for (int j = i; j < *emprestimo_count - 1; j++) {
                (*emprestimos)[j] = (*emprestimos)[j + 1];
            }
            *emprestimos = realloc(*emprestimos, (*emprestimo_count - 1) * sizeof(Emprestimo));
            if (*emprestimos == NULL) {
                printf("Erro ao alocar memória para o empréstimo.\n");
                exit(1);
            }
            (*emprestimo_count)--;
            return;
        }
    }
    printf("Livro não encontrado.\n");
}


void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count) {
    if (emprestimo.count >= 0 && emprestimo_count < emprestimo_count) {
        emprestimos[emprestimo_count].data_devolucao += 604800;  // renova por mais 7 dias
    } else {
        printf("ID de empréstimo inválido.\n");
    }



typedef struct {
    char titulo[MAX_TITULO];
    char usuario[MAX_USUARIO];
    time_t data_emprestimo;
    time_t data_devolucao;
} Emprestimo;


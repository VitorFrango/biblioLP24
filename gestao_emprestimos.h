//
// Created by Vitor Frango on 12/04/2024.
//

#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

#include "gestao_emprestimos.h"
#include "principal.h"
#include "gera_relatorios.h"
#include "io_dados.h"
#include "gestao_livros.h"

#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_GENERO 50

// Define the Livro struct
typedef struct {
    char titulo[100];
    char autor[100];
    char genero[100];
    int copias;
} Livro;

// Define the Emprestimo struct
typedef struct {
    char titulo[100];
    char usuario[100];
    time_t data_emprestimo;
    time_t data_devolucao;
} Emprestimo;

void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);
void finalizar_emprestimo();
void expandir_emprestimos();
void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count, int emprestimo_id);
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);

#endif
// Path: gestao_emprestimos.c
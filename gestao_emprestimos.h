#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

#include <time.h>
#include "gestao_livros.h"  // Asumindo que esse cabeçalho contém a definição de 'Livro'

#define MAX_TITULO 100
#define MAX_AUTOR 50
#define MAX_GENERO 30
#define MAX_UTILIZADOR 50

typedef struct {
    char titulo[MAX_TITULO];
    char user[MAX_UTILIZADOR];
    int is_devolvido;
    time_t data_emprestimo;
    time_t data_devolucao;
} Emprestimo;

typedef struct {
    char nome[MAX_UTILIZADOR];
    int count;
} UserCount;

void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);
void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count);
void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count);
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);

#endif // GESTAO_EMPRESTIMOS_H

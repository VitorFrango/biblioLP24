#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

#include <time.h> // Para o uso de time_t
#include "gestao_livros.h"

// Declaração das estruturas


#define MAX_UTILIZADOR 50


typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int copias_emprestadas;
    int copias;
    char user[MAX_UTILIZADOR];
    int copias_atuais;
    int is_devolvido;
    time_t data_emprestimo;
    time_t data_devolucao;
} Emprestimo;

typedef struct {
    char nome[100];
    int count;
} UserCount;

// Prototipo da função para copiar dados de livros para emprestimos
void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath);

void inicializar_emprestimos(const char *filename, Livro **livros, int *count);
void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);
void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count);
//void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count);
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);
int copias_atuais(int copias, int copias_emprestadas);

#endif // GESTAO_EMPRESTIMOS_H

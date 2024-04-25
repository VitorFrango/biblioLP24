#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

#include <time.h> // Para o uso de time_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestao_livros.h"


// Declaração das estruturas


#define MAX_UTILIZADOR 50


typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int copias;
    int copias_emprestadas;
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

typedef struct {
    char titulo[50];
    int count;
} LivroCount;

void fechar_arquivos(FILE *f1, FILE *f2, FILE *f3);


// Prototipo da função para emprestar livro
void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);


// prototipo carrergar emprestimos
void carregar_emprestimos(const char *filename, Emprestimo **emprestimos, int *emprestimo_count);

// Prototipo da função para copiar dados de livros para emprestimos
void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath, const char *posFilePath, int emprestimo_count);

//void inicializar_emprestimos(const char *filename, Livro **livros, int *count);
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);
void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count);
//void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count);
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);
int copias_atuais(int copias, int copias_emprestadas);

#endif // GESTAO_EMPRESTIMOS_H

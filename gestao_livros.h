//
// Created by Vitor Frango on 12/04/2024.
//
#ifndef GESTAO_LIVROS_H
#define GESTAO_LIVROS_H

#define MAX_LINHA_TAM 100
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_GENERO 50
#define MAX_LINHA_TAM 100

typedef struct Livro {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int copias;
    int copias_emprestadas;
} Livro;

void inicializar_biblioteca(const char *filename, Livro **livros, int *count);
void pesquisar_livros(const char *filename, const char *titulo_procura);
void guardar_livros(const char *filename, Livro *livros, int count);
void adicionar_livro(Livro **livros, int *count);
void remover_livro_por_id(Livro **livros, int *count, int id);
void editar_livro(Livro *livros, int count, int id);


#endif //GESTAO_LIVROS_H
//
// Created by Vitor Frango on 12/04/2024.
//
#include <time.h>

#ifndef GESTAO_LIVROS_H
#define GESTAO_LIVROS_H

#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_GENERO 50




void inicializar_biblioteca(const char *filename, Livro **livros, int *count);
void adicionar_livro(Livro **livros, int *count);
void pesquisar_livros(Livro *livros, int count, const char *termo_pesquisa);
void guardar_livros(const char *filename, Livro *livros, int count);
void editar_livro(Livro *livros, int count, const char *titulo);


#endif
//INC_21178LABPRO_GESTAO_LIVROS_H
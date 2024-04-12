//
// Created by Vitor Frango on 12/04/2024.
//Funções para gerIR livros.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestao_livros.h"

#define MAX_LINHA_TAM 300


void inicializar_biblioteca(const char *filename, Livro **livros, int *count){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        exit(1);
    }
    char linha[MAX_LINHA_TAM];
    *count = 0;
    while (fgets(linha, MAX_LINHA_TAM, file) != NULL) {
        *livros = realloc(*livros, (*count + 1) * sizeof(Livro));
        if (*livros == NULL) {
            printf("Erro ao alocar memória para o livro.\n");
            exit(1);
        }
        sscanf(linha, "%[^,],%[^,],%[^,],%d\n",
               (*livros)[*count].titulo,
               (*livros)[*count].autor,
               (*livros)[*count].genero,
               &(*livros)[*count].copias);
        (*count)++;
    }
    fclose(file);
}

void adicionar_livro(Livro **livros, int *count){
    *livros = realloc(*livros, (*count + 1) * sizeof(Livro));
    if (*livros == NULL) {
        printf("Erro ao alocar memória para o livro.\n");
        exit(1);
    }
    printf("Digite o título do livro: ");
    fgets((*livros)[*count].titulo, MAX_TITULO, stdin);
    printf("Digite o autor do livro: ");
    fgets((*livros)[*count].autor, MAX_AUTOR, stdin);
    printf("Digite o gênero do livro: ");
    fgets((*livros)[*count].genero, MAX_GENERO, stdin);
    printf("Digite o número de cópias do livro: ");
    scanf("%d", &(*livros)[*count].copias);
    getchar();  // Limpa buffer do stdin
    (*count)++;
};

void guardar_livros(const char *filename, Livro *livros, int count){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%d\n",
                livros[i].titulo,
                livros[i].autor,
                livros[i].genero,
                livros[i].copias);
    }
    fclose(file);
};

void pesquisar_livros(Livro *livros, int count, const char *termo_pesquisa){
    for (int i = 0; i < count; i++) {
        if (strstr(livros[i].titulo, termo_pesquisa) != NULL ||
            strstr(livros[i].autor, termo_pesquisa) != NULL ||
            strstr(livros[i].genero, termo_pesquisa) != NULL) {
            printf("Título: %s\nAutor: %s\nGênero: %s\nCópias: %d\n\n",
                   livros[i].titulo, livros[i].autor, livros[i].genero, livros[i].copias);
        }
    }
};


void remover_livro(const char *titulo);
void editar_livro(const char *titulo);



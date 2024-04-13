//
// Created by Vitor Frango on 12/04/2024.
// Funções para gerir livros.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHA_TAM 100

#include "gestao_livros.h"


void inicializar_biblioteca(const char *filename, Livro **livros, int *count){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        return;
    }
    char linha[MAX_LINHA_TAM];
    *count = 0;
    while (fgets(linha, MAX_LINHA_TAM, file) != NULL) {
        *livros = realloc(*livros, (*count + 1) * sizeof(Livro));
        if (*livros == NULL) {
            fprintf(stderr, "Erro ao alocar memória para o livro.\n");
            fclose(file);
            return;
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
        fprintf(stderr, "Erro ao alocar memória para o livro.\n");
        return;
    }
    printf("Digite o título do livro: ");
    fgets((*livros)[*count].titulo, MAX_TITULO, stdin);
    (*livros)[*count].titulo[strcspn((*livros)[*count].titulo, "\n")] = '\0';
    printf("Digite o autor do livro: ");
    fgets((*livros)[*count].autor, MAX_AUTOR, stdin);
    (*livros)[*count].autor[strcspn((*livros)[*count].autor, "\n")] = '\0';
    printf("Digite o gênero do livro: ");
    fgets((*livros)[*count].genero, MAX_GENERO, stdin);
    (*livros)[*count].genero[strcspn((*livros)[*count].genero, "\n")] = '\0';
    printf("Digite o número de cópias do livro: ");
    scanf("%d", &(*livros)[*count].copias);
    getchar();  // Clear stdin buffer
    (*count)++;
}


void pesquisar_livros(Livro *livros, int count, const char *termo_pesquisa){
    for (int i = 0; i < count; i++) {
        if (strstr(livros[i].titulo, termo_pesquisa) != NULL ||
            strstr(livros[i].autor, termo_pesquisa) != NULL ||
            strstr(livros[i].genero, termo_pesquisa) != NULL) {
            printf("Título: %s\nAutor: %s\nGênero: %s\nCópias: %d\n\n",
                   livros[i].titulo, livros[i].autor, livros[i].genero, livros[i].copias);
        }
    }
}

void guardar_livros(const char *filename, Livro *livros, int count){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\\n", filename);
        return;  // Handling file opening error gracefully
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%d\\n",
                livros[i].titulo,
                livros[i].autor,
                livros[i].genero,
                livros[i].copias);
    }
    fclose(file);
}


void remover_livro(Livro **livros, int *count, const char *titulo) {

    int i;
    for (i = 0; i < *count; i++) {
        if (strcmp((*livros)[i].titulo, titulo) == 0) {
            break;
        }
    }
    if (i == *count) {
        printf("Livro não encontrado.\\n");
        return;
    }
    for (; i < *count - 1; i++) {
        (*livros)[i] = (*livros)[i + 1];
    }
    *livros = realloc(*livros, (*count - 1) * sizeof(Livro));
    if (*livros == NULL && *count > 1) {
        fprintf(stderr, "Erro ao realocar memória.\\n");
        return;  // Handle error in reallocation
    }
    (*count)--;
}

void editar_livro(Livro *livros, int count, const char *titulo){
    for (int i = 0; i < count; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            printf("Editando livro: %s\\n", titulo);
            printf("Novo título: ");
            fgets(livros[i].titulo, MAX_TITULO, stdin);
            livros[i].titulo[strcspn(livros[i].titulo, "\\n")] = '\0';
            printf("Novo autor: ");
            fgets(livros[i].autor, MAX_AUTOR, stdin);
            livros[i].autor[strcspn(livros[i].autor, "\\n")] = '\0';
            printf("Novo gênero: ");
            fgets(livros[i].genero, MAX_GENERO, stdin);
            livros[i].genero[strcspn(livros[i].genero, "\\n")] = '\0';
            printf("Nova quantidade de cópias: ");
            scanf("%d", &livros[i].copias);
            getchar();  // Clear stdin buffer
            return;
        }
    }
    printf("Livro não encontrado.\\n");
}


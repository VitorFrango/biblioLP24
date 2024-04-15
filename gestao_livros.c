// Created by Vitor Frango on 12/04/2024.
// Funções para gerir livros.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    Livro *temp = realloc(*livros, (*count + 1) * sizeof(Livro));
    if (temp == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o livro.\n");
        return; // Exiting function without changing *livros or *count
    }
    *livros = temp; // Use temp, now that we know it's not NULL
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

    // Save the updated library to the file
    guardar_livros("livros.csv", *livros, *count);
}

void pesquisar_livros(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }
    char linha[MAX_LINHA_TAM];
    while (fgets(linha, MAX_LINHA_TAM, file) != NULL) {
        char titulo[MAX_TITULO];
        char autor[MAX_AUTOR];
        char genero[MAX_GENERO];
        int copias;
        sscanf(linha, "%[^,],%[^,],%[^,],%d\n", titulo, autor, genero, &copias);
        printf("Título: %s\n", titulo);
        printf("Autor: %s\n", autor);
        printf("Gênero: %s\n", genero);
        printf("Cópias: %d\n", copias);
    }
    if (fclose(file) != 0) {
        perror("Erro ao fechar o arquivo");
    }
}




void guardar_livros(const char *filename, Livro *livros, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }
    for (int i = 0; i < count; i++) {
        if (fprintf(file, "%s,%s,%s,%d\n",
                    livros[i].titulo,
                    livros[i].autor,
                    livros[i].genero,
                    livros[i].copias) < 0) {
            perror("Erro ao escrever no arquivo");
            break;
        }
    }
    if (fclose(file) != 0) {
        perror("Erro ao fechar o arquivo");
    }
}

void remover_livro(Livro **livros, int *count, const char *titulo) {
    int i;
    for (i = 0; i < *count; i++) {
        if (strcmp((*livros)[i].titulo, titulo) == 0) {
            break;
        }
    }
    if (i == *count) {
        printf("Livro não encontrado.\n");
        return;
    }
    for (; i < *count - 1; i++) {
        (*livros)[i] = (*livros)[i + 1];
    }
    *livros = realloc(*livros, (*count - 1) * sizeof(Livro));
    if (*livros == NULL && *count > 1) {
        fprintf(stderr, "Erro ao realocar memória.\n");
        return;
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


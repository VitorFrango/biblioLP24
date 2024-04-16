// Created by Vitor Frango on 12/04/2024.
// Funções para gerir livros.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gestao_livros.h"

void inicializar_biblioteca(const char *filename, Livro **livros, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    char linha[MAX_LINHA_TAM];
    *count = 0;
    *livros = NULL;  // Garantir que o ponteiro inicial seja NULL

    Livro *temp;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = 0;  // Remover o caractere de nova linha

        temp = realloc(*livros, (*count + 1) * sizeof(Livro));
        if (temp == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os livros.\n");
            break;  // Sair do loop para limpeza e fechamento
        }
        *livros = temp;

        memset(&(*livros)[*count], 0, sizeof(Livro));  // Inicializar a nova entrada

        int itemsRead = sscanf(linha, "%99[^,],%99[^,],%49[^,],%d",
                               (*livros)[*count].titulo,
                               (*livros)[*count].autor,
                               (*livros)[*count].genero,
                               &(*livros)[*count].copias);

        if (itemsRead != 4) {
            fprintf(stderr, "Linha malformada: %s\n", linha);
            continue;  // Pula para a próxima linha se esta está malformada
        }

        (*count)++;
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo");
        free(*livros);  // Liberar a memória alocada em caso de erro de leitura
        *livros = NULL;
        *count = 0;
    }

    fclose(file);  // Fechar o arquivo em qualquer saída
}

void adicionar_livro(Livro **livros, int *count){
    Livro *temp = realloc(*livros, (*count + 1) * sizeof(Livro));
    if (temp == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o livro.\n");
        return;
    }
    *livros = temp; // utiliza o ponteiro realocado
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
    getchar();  // limpa o buffer do stdin
    (*count)++;

    // guarda os livros no arquivo
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
        printf("----------------\n");
        printf("Título: %s\n", titulo);
        printf("Autor: %s\n", autor);
        printf("Gênero: %s\n", genero);
        printf("Cópias: %d\n", copias);
        printf("----------------\n");
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


//
// Created by Vitor Frango on 12/04/2024.
//Funções para gerIR livros.


#include <stdio.h>
#include <stdlib.h>

#include "gestao_livros.h"
#include "principal.h"
#include "gera_relatorios.h"
#include "io_dados.h"
#include "gestao_emprestimos.h"

#define MAX_LINHA_TAM 300
#define MAX_TITULO 100
#define MAX_USUARIO 50


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
};
void expandir_biblioteca();

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


void remover_livro(const char *titulo);
void editar_livro(const char *titulo);
void pesquisar_livros(const char *termo_pesquisa);
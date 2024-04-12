//
// Created by Vitor Frango on 12/04/2024.
//Funções para gerar relatórios.


#include <stdio.h>
#include <stdlib.h>

#include "gestao_emprestimos.h"

void carregar_livros_csv(const char *nome_arquivo) {
    FILE *arquivo = fopen(livros.csv, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(1);
    }
};

void salvar_livros_csv(const char *nome_arquivo);

void salvar_emprestimos_csv(const char *nome_arquivo);

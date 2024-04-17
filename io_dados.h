//
// Created by Vitor Frango on 12/04/2024.
//Funções para entrada e saída de dados (leitura e escrita de CSV).

//


#ifndef IO_DADOS_H
#define IO_DADOS_H

#include "gestao_livros.h"
#include "gestao_emprestimos.h"


void carregar_livros_csv(const char *nome_arquivo);
void salvar_livros_csv(const char *nome_arquivo);
void salvar_emprestimos_csv(const char *nome_arquivo);

#endif

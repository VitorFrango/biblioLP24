//
// Created by Vitor Frango on 12/04/2024.
//



#ifndef GERA_RELATORIOS_H
#define GERA_RELATORIOS_H

#include "gestao_emprestimos.h"
#include "gestao_livros.h"


// Estruturas necessárias para o código


typedef struct {
    char titulo[100];
    int count;
    char autor[100]; // Incluímos autor aqui para exibir o autor mais tarde
} LivroCount;



void relatorio_carregar_emprestimos(const char *filename, Emprestimo **emprestimos, int *emprestimo_count);
void livros_mais_emprestados(Emprestimo *emprestimos, int emprestimo_count);
void locatarios_com_mais_livros_emprestados(Emprestimo **emprestimos, int *emprestimo_count);
void livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count);



#endif

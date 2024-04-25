//
// Created by Vitor Frango on 12/04/2024.
//



#ifndef GERA_RELATORIOS_H
#define GERA_RELATORIOS_H

#include "gestao_emprestimos.h"
#include "gestao_livros.h"

typedef struct LivroCount {
    char titulo[MAX_TITULO];
    int count;
} LivroCount;


void livros_mais_emprestados(Emprestimo *emprestimos, int emprestimo_count);
void locatarios_com_mais_livros_emprestados(Emprestimo *emprestimos, int emprestimo_count);
void relatorio_livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count);



#endif

//
// Created by Vitor Frango on 12/04/2024.
//



#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include "io_dados.h"
#include "gera_relatorios.h"



void inicializar_biblioteca(const char *filename, Livro **livros, int *count);
void empresta_livro(Livro *livro, int count, Emprestimo **emprestimos, int *emprestimo_count);

#endif //BIBLIOTECA_PRINCIPAL_H
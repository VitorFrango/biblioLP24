//
// Created by Vitor Frango on 12/04/2024.
//

#ifndef BIBLIOTECA_PRINCIPAL_H
#define BIBLIOTECA_PRINCIPAL_H

#include "gestao_livros.h"
#include "gestao_emprestimos.h"
#include "io_dados.h"

void inicializar_biblioteca(const char *filename, Livro **livros, int *count);
void empresta_livro(Livro *livro, int count, Emprestimo **emprestimos, int *emprestimo_count);

#endif //BIBLIOTECA_PRINCIPAL_H
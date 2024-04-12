//
// Created by Vitor Frango on 12/04/2024.
//Funções para gerIR empréstimos.


#include "gestao_emprestimos.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_emprestimos(int tamanho);
void expandir_emprestimos();
void registrar_emprestimo();
void renovar_emprestimo(const char *titulo, const char *usuario);
void devolver_livro(const char *titulo, const char *usuario);
//
// Created by Vitor Frango on 12/04/2024.
//

#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H

void inicializar_emprestimos(int tamanho);
void expandir_emprestimos();
void registrar_emprestimo();
void renovar_emprestimo(const char *titulo, const char *usuario);
void devolver_livro(const char *titulo, const char *usuario);

#endif

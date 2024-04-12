//
// Created by Vitor Frango on 12/04/2024.
//

#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H


void inicializar_emprestimos(void empresta_livro(Livro *livro, int count, Emprestimo **emprestimos, int *emprestimo_count);
void finalizar_emprestimo();
void expandir_emprestimos();
void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count);
void devolver_livro(Livro *Livro, int count, Emprestimo **emprestimos, int *emprestimo_count);

#endif

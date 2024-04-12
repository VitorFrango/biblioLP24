//
// Created by Vitor Frango on 12/04/2024.
//

#ifndef GESTAO_LIVROS_H
#define GESTAO_LIVROS_H

void inicializar_biblioteca(int tamanho);
void expandir_biblioteca();
void adicionar_livro();
void remover_livro(const char *titulo);
void editar_livro(const char *titulo);
void pesquisar_livros(const char *termo_pesquisa);

#endif

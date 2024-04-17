//
// Created by Vitor Frango on 17/04/2024.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include "gestao_livros.h"
#include "gestao_emprestimos.h"
#include "gera_relatorios.h"



void exibir_menu_principal(Livro **livros, int *livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void menu_gestao_livros(Livro **livros, int *livro_count);
void menu_gestao_emprestimos(Livro **livros, int *livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void menu_relatorios(Emprestimo **emprestimos, int *emprestimo_count);


// Protótipos de funções para a gestão de livros
void adicionar_livro(Livro **livros, int *livro_count);
void remover_livro_por_id(Livro **livros, int *count, int id);
void editar_livro(Livro *livros, int count, const char *titulo);
void pesquisar_livros(const char *arquivo);

// Protótipos de funções para a gestão de empréstimos
void remover_livro_por_id(Livro **livros, int *count, int id);
void devolver_livro(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count);
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count);

// Protótipos de funções para relatórios
void livros_mais_emprestados(Emprestimo *emprestimos, int emprestimo_count);
void relatorio_livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count);
void locatarios_com_mais_emprestimos(Emprestimo *emprestimos, int emprestimo_count);

// Funções para salvar dados
void guardar_livros(const char *arquivo, Livro *livros, int livro_count);
void guardar_emprestimo(const char *arquivo, Emprestimo *emprestimos, int emprestimo_count);

#endif // INTERFACE_H
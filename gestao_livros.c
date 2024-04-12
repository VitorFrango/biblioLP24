//
// Created by Vitor Frango on 12/04/2024.
//Funções para gerIR livros.


#include <stdio.h>
#include <stdlib.h>

#include "gestao_livros.h"
#include "principal.h"
#include "gera_relatorios.h"
#include "io_dados.h"
#include "gestao_emprestimos.h"


void inicializar_biblioteca(int tamanho);
void expandir_biblioteca();
void adicionar_livro();
void remover_livro(const char *titulo);
void editar_livro(const char *titulo);
void pesquisar_livros(const char *termo_pesquisa);
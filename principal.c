/*
// Created by Vitor Frango on 12/04/2024.

 Desenvolva um programa em linguagem C para gerir o acervo de uma biblioteca. Ao iniciar,
 o programa deve ler um ficheiro CSV contendo os dados dos livros (título, autor, género,
 número de exemplares existentes) e armazená-los em memória. O programa deve permitir que
 o utilizador adicione novos livros, remova livros existentes, edite informação sobre os
 livros e pesquise por título, autor ou género.

Recorrendo a outro ficheiro CSV e atualizando os dados em memória, o programa deve ser capaz
 de registar empréstimos de livros para os utilizadores da biblioteca, mantendo o controlo dos
 exemplares disponíveis e da data de devolução. Também deve permitir a renovação de empréstimos
 e a devolução de livros.

O programa deve ter um sistema de relatórios que mostre informação sobre os livros mais
 emprestados, os livros não devolvidos e os utilizadores com mais empréstimos.

O programa deve usar memória dinâmica. Ao fechar o programa ou quando solicitado,
 o programa deve gravar os dados, em memória, nos respetivos ficheiros CSV.

O programa deve ser modular, com cada funcionalidade implementada num módulo separado,
 como leitura de dados, escrita de dados, empréstimos, relatórios, etc. O código deve
 ser organizado e documentado de acordo com as melhores práticas de programação em C,
 implementando testes de unidade e de integração.
*/




#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include "interface.h"


int main() {
        Livro *livros; // Ponteiro para array de livros
        livros = NULL; // Inicializa ponteiro com NULL
        int livro_count = 0; // Contador de livros
        Emprestimo *emprestimos = NULL; // Ponteiro para array de empréstimos
        int emprestimo_count = 0; // Contador de empréstimos

    // Inicializa a biblioteca com os dados do arquivo livros.csv
    inicializar_biblioteca("livros.csv", &livros, &livro_count);

    exibir_menu_principal(&livros, &livro_count, &emprestimos, &emprestimo_count);
    menu_gestao_livros(&livros, &livro_count);
    menu_gestao_emprestimos(&livros, &livro_count, &emprestimos, &emprestimo_count);
    menu_relatorios(&emprestimos, &emprestimo_count);


}
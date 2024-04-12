//
// Created by Vitor Frango on 12/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gera_relatorios.h"
#include "gestao_livros.h"
#include "gestao_emprestimos.h"
#include "principal.h"


void relatorio_usuarios_com_mais_emprestimos(Livro *livros, int livro_count) {
    printf("Livros mais emprestados:\n");
    for (int i = 0; i < livro_count; i++){
        if (Livros[i].empprestimos_count > 0)
            printf("Livro: %s\n", livros[i].titulo);
            printf("Quantidade de emprestimos: %d\n", livros[i].emprestimos_count);
    }
}

void relatorio_livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count) {
    printf("Livros não devolvidos:\n");
    for (int i = 0; i < emprestimo_count; i++){
        if (emprestimos[i].devolvido == 0)
            printf("Livro: %s\n", emprestimos[i].livro.titulo);
            printf("Usuario: %s\n", emprestimos[i].usuario.nome);
    }
}

void locatarios_com_mais_emprestimos(Emprestimo *emprestimos, int emprestimo_count) {
    printf("Locatários com mais empréstimos:\n");
    typedef struct {
        char nome[100];
        int count;
    } UsuarioCount;

    UsuarioCount *counts = NULL;
    int num_locatarios = 0;

    for(int i = 0; i < emprestimo_count; i++){
        int found = 0;
        for(int j = 0; j < num_locatarios; j++){
            if(strcmp(emprestimos[i].usuario.nome, counts[j].nome) == 0){
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if(!found){
            counts = (UsuarioCount *) realloc(counts, (num_locatarios + 1) * sizeof(UsuarioCount));
            strcpy(counts[num_locatarios].nome, emprestimos[i].usuario.nome);
            counts[num_locatarios].count = 1;
            num_locatarios++;
        }
    }
    for(int i = 0; i < num_locatarios; i++){
        printf("Usuário: %s\n", counts[i].nome);
        printf("Quantidade de empréstimos: %d\n", counts[i].count);
    }
    free(counts);
}
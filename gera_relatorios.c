//
// Created by Vitor Frango on 12/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gera_relatorios.h"


void relatorio_livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count) {
    printf("Livros não devolvidos:\n");
    for (int i = 0; i < emprestimo_count; i++){
        if (emprestimos[i].is_devolvido == 0)
            printf("Livro: %s\n", emprestimos[i].titulo);
        printf("Usuario: %s\n", emprestimos[i].user);
    }
}

void locatarios_com_mais_emprestimos(Emprestimo *emprestimos, int emprestimo_count) {
    UserCount *counts = NULL;
    int num_locatarios = 0;
    for(int i = 0; i < emprestimo_count; i++) {
        int found = 0;
        for(int j = 0; j < num_locatarios; j++) {
            if(strcmp(emprestimos[i].user, counts[j].nome) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if(!found) {
            counts = (UserCount *) realloc(counts, (num_locatarios + 1) * sizeof(UserCount));
            strcpy(counts[num_locatarios].nome, emprestimos[i].user);
            counts[num_locatarios].count = 1;
            num_locatarios++;
        }
    }
    for(int i = 0; i < num_locatarios; i++) {
        printf("Usuário: %s\\n", counts[i].nome);
        printf("Quantidade de emprestimos: %d\\n", counts[i].count);
    }
    free(counts); // Liberação de memória
}
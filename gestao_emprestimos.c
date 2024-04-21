#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath) {
    FILE *livrosFile = fopen(livrosFilePath, "r");
    FILE *emprestimosFile = fopen(emprestimosFilePath, "a");

    if (!livrosFile || !emprestimosFile) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Livro livro;
    Emprestimo emprestimo;

    while (fscanf(livrosFile, "%d,%99[^,],%99[^,],%49[^,],%d\n", &livro.id, livro.titulo, livro.autor, livro.genero, &livro.copias) == 5) {
        emprestimo.id = livro.id;
        strcpy(emprestimo.titulo, livro.titulo);
        strcpy(emprestimo.autor, livro.autor);
        strcpy(emprestimo.genero, livro.genero);
        emprestimo.copias = livro.copias;
        emprestimo.copias_emprestadas = 0;
        strcpy(emprestimo.user, "Desconhecido");
        emprestimo.copias_atuais = livro.copias;
        emprestimo.is_devolvido = 0;
        emprestimo.data_emprestimo = time(NULL);
        emprestimo.data_devolucao = 0;

        fprintf(
                emprestimosFile,
                "%d,%s,%s,%s,%d,%d,%d,%s,%d,%ld,%ld\n",
                emprestimo.id,
                emprestimo.titulo,
                emprestimo.autor,
                emprestimo.genero,
                emprestimo.copias_emprestadas,
                emprestimo.copias,
                emprestimo.copias_atuais,
                emprestimo.user,
                emprestimo.is_devolvido,
                emprestimo.data_emprestimo,
                emprestimo.data_devolucao
        );
    }

    fclose(livrosFile);
    fclose(emprestimosFile);
}


void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    char buffer_emprestimo[20], buffer_devolucao[20];  // Para armazenar as datas formatadas
    for (int i = 0; i < emprestimo_count; i++) {
        // Formata a data de empréstimo
        strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d %H:%M:%S", localtime(&emprestimos[i].data_emprestimo));
        // Formata a data de devolução
        strftime(buffer_devolucao, sizeof(buffer_devolucao), "%Y-%m-%d %H:%M:%S", localtime(&emprestimos[i].data_devolucao));

        // Grava no arquivo
        fprintf(file, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n",
                emprestimos[i].titulo,
                emprestimos[i].autor,
                emprestimos[i].genero,
                buffer_emprestimo,
                emprestimos[i].copias,
                emprestimos[i].copias_emprestadas,
                emprestimos[i].user,
                emprestimos[i].copias_atuais,
                emprestimos[i].is_devolvido);
    }

    fclose(file);
}

void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    int livro_id;
    printf("Digite o ID do livro a ser emprestado: ");
    scanf("%d", &livro_id);
    getchar();  // Limpa o buffer do stdin
    if (livro_id < 0 || livro_id >= count) {
        printf("ID de livro inválido.\n");
        return;
    }
    if (livros[livro_id].copias <= 0) {
        printf("Livro sem cópias disponíveis.\n");
        return;
    }
    livros[livro_id].copias--;
    Emprestimo *temp = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
    if (temp == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o empréstimo.\n");
        return;
    }
    *emprestimos = temp;
    strcpy((*emprestimos)[*emprestimo_count].titulo, livros[livro_id].titulo);
    printf("Digite o nome do usuário: ");
    fgets((*emprestimos)[*emprestimo_count].user, MAX_UTILIZADOR, stdin);
    (*emprestimos)[*emprestimo_count].user[strcspn((*emprestimos)[*emprestimo_count].user, "\n")] = '\0';  // Remove newline
    time_t current_time;
    time(&current_time);
    (*emprestimos)[*emprestimo_count].data_emprestimo = current_time;
    (*emprestimos)[*emprestimo_count].data_devolucao = current_time + 604800;  // 7 dias
    (*emprestimo_count)++;

    // Grava os empréstimos atualizados no arquivo
    guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
}

void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    char titulo[MAX_TITULO];
    printf("Digite o título do livro a ser devolvido: ");
    fgets(titulo, MAX_TITULO, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';  // Remove newline
    for (int i = 0; i < *emprestimo_count; i++) {
        if (strcmp((*emprestimos)[i].titulo, titulo) == 0) {
            for (int j = 0; j < count; j++) {
                if (strcmp(livros[j].titulo, titulo) == 0) {
                    livros[j].copias++;
                    break;
                }
            }
            // Remove o empréstimo devolvido do array
            for (int k = i; k < *emprestimo_count - 1; k++) {
                (*emprestimos)[k] = (*emprestimos)[k + 1];
            }
            Emprestimo *temp = realloc(*emprestimos, (*emprestimo_count - 1) * sizeof(Emprestimo));
            if (temp == NULL && *emprestimo_count > 1) {
                fprintf(stderr, "Erro ao ajustar memória para o empréstimo.\n");
                return;
            }
            *emprestimos = temp;
            (*emprestimo_count)--;
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count) {
    int emprestimo_id;
    printf("Digite o ID do empréstimo a ser renovado: ");
    scanf("%d", &emprestimo_id);
    getchar();  // Limpa o buffer do stdin

    if (emprestimo_id >= 0 && emprestimo_id < emprestimo_count) {
        emprestimos[emprestimo_id].data_devolucao += 604800;  // Renova por mais 7 dias
    } else {
        printf("ID de empréstimo inválido.\n");
    }
}

void atualizar_emprestimo(Livro *livros, int livro_count, Emprestimo **emprestimos, int *emprestimo_count) {
    time_t current_time;
    time(&current_time);
    for (int i = 0; i < *emprestimo_count; i++) {
        if (current_time > (*emprestimos)[i].data_devolucao) {
            for (int j = 0; j < livro_count; j++) {
                if (strcmp(livros[j].titulo, (*emprestimos)[i].titulo) == 0) {
                    livros[j].copias++;
                    break;
                }
            }
            // Remove o empréstimo vencido do array
            for (int k = i; k < *emprestimo_count - 1; k++) {
                (*emprestimos)[k] = (*emprestimos)[k + 1];
            }
            Emprestimo *temp = realloc(*emprestimos, (*emprestimo_count - 1) * sizeof(Emprestimo));
            if (temp == NULL && *emprestimo_count > 1) {
                printf("Erro ao alocar memória para o empréstimo.\n");
                exit(1);
            }
            *emprestimos = temp;
            (*emprestimo_count)--;
        }
    }
}


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestao_emprestimos.h"  // Assume que esse cabeçalho define 'Livro' e 'Emprestimo'
#include "gestao_livros.h"


void inicializar_enorestimos(const char *filename, Livro **livros, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    char linha[MAX_LINHA_TAM];
    *count = 0;
    *livros = NULL;

    Livro *temp;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = 0;

        temp = realloc(*livros, (*count + 1) * sizeof(Livro));
        if (temp == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os livros.\n");
            free(*livros);  // Liberar memória antes alocada
            *livros = NULL;
            goto cleanup;
        }
        *livros = temp;

        memset(&(*livros)[*count], 0, sizeof(Livro));

        int itemsRead = sscanf(linha, "%d, %[^,],%[^,],%[^,],%d",
                               &(*livros)[*count].id,
                               (*livros)[*count].titulo,
                               (*livros)[*count].autor,
                               (*livros)[*count].genero,
                               &(*livros)[*count].copias);
        if (itemsRead != 5) {
            fprintf(stderr, "Linha malformada: %s\n", linha);
            continue;
        }

        (*count)++;
    }

    cleanup:
    if (ferror(file)) {
        perror("Erro ao ler o arquivo");
        free(*livros);
        *livros = NULL;
        *count = 0;
    }

    fclose(file);  // Fechar o arquivo em qualquer saída
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
        fprintf(file, "%s,%s,%s,%s\n",
                emprestimos[i].titulo,
                emprestimos[i].user,
                buffer_emprestimo,
                buffer_devolucao);
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


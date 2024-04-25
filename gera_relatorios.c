//
// Created by Vitor Frango on 12/04/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>  // Para `strerror`
#include "gera_relatorios.h" // Certifique-se de incluir corretamente o cabeçalho necessário



// Função para carregar os empréstimos do arquivo CSV
void relatorio_carregar_emprestimos(const char *filename, Emprestimo **emprestimos, int *emprestimo_count) {
    // Inicialização do array de empréstimos
    *emprestimos = NULL;
    *emprestimo_count = 0;

    // Tentar abrir o arquivo
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    Emprestimo temp;
    char buffer_emprestimo[20], buffer_devolucao[20];

    // Loop para ler cada linha do arquivo CSV
    while (fscanf(file, "%d,%99[^,],%99[^,],%49[^,],%d,%99[^,],%d,%d,%d,%19[^,],%19[^,],%d\n",
                  &temp.id,
                  temp.titulo,
                  temp.autor,
                  temp.genero,
                  &temp.copias,
                  temp.user,
                  &temp.copias_atuais,
                  &temp.copias_emprestadas,
                  &temp.is_devolvido,
                  buffer_emprestimo,
                  buffer_devolucao,
                  &temp.is_devolvido) != EOF) {



        // Converte as datas de string para time_t
        struct tm tm = {0};
        if (strptime(buffer_emprestimo, "%Y-%m-%d %H:%M:%S", &tm) == NULL) {
            printf("Erro ao converter data de empréstimo.\n");
            continue;
        }
        temp.data_emprestimo = mktime(&tm);

        if (strptime(buffer_devolucao, "%Y-%m-%d %H:%M:%S", &tm) == NULL) {
            printf("Erro ao converter data de devolução.\n");
            continue;
        }
        temp.data_devolucao = mktime(&tm);

        // Realoca memória para adicionar um novo registro ao array
        Emprestimo *new_ptr = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
        if (new_ptr == NULL) {
            fprintf(stderr, "Erro ao realocar memória: %s\n", strerror(errno));
            fclose(file);
            return;
        }

        *emprestimos = new_ptr; // Atualiza o ponteiro para o novo array
        (*emprestimos)[*emprestimo_count] = temp;
        (*emprestimo_count)++;
    }

    fclose(file); // Fecha o arquivo após leitura
}

// Função para encontrar livros mais emprestados
void livros_mais_emprestados(Emprestimo *emprestimos, int emprestimo_count) {
    if (emprestimo_count == 0) {
        printf("Nenhum empréstimo encontrado.\n");
        return;
    }

    LivroCount *counts = NULL; // Array para contar livros
    int num_livros = 0;

    // Contar empréstimos por título
    for (int i = 0; i < emprestimo_count; i++) {
        if (emprestimos[i].is_devolvido == 1) {
            continue; // Ignora livros devolvidos
        }

        int found = 0; // Flag para verificar se o livro já está na lista
        for (int j = 0; j < num_livros; j++) {
            if (strcmp(emprestimos[i].titulo, counts[j].titulo) == 0) {
                counts[j].count++; // Incrementa o contador
                found = 1; // Marca como encontrado
                break;
            }
        }

        if (!found) {
            LivroCount *new_counts = (LivroCount *)realloc(counts, (num_livros + 1) * sizeof(LivroCount));
            if (new_counts == NULL) {
                printf("Erro ao realocar memória para a lista de livros.\n");
                free(counts); // Liberação de memória para evitar vazamentos
                return;
            }

            counts = new_counts; // Atualiza o ponteiro para o novo array
            strcpy(counts[num_livros].titulo, emprestimos[i].titulo); // Copia o título
            counts[num_livros].count = 1; // Inicializa com 1
            num_livros++;
        }
    }

    // Encontrar o número máximo de empréstimos
    int max_emprestimos = 0;
    for (int i = 0; i < num_livros; i++) {
        if (counts[i].count > max_emprestimos) {
            max_emprestimos = counts[i].count;
        }
    }

    printf("Livros mais emprestados:\n");
    for (int i = 0; i < num_livros; i++) {
        if (counts[i].count == max_emprestimos) {
            printf("Título: %s\n", counts[i].titulo);
            printf("Quantidade de empréstimos: %d\n", counts[i].count);
        }
    }

    free(counts); // Libera memória para evitar vazamentos
}

// Função para listar livros não devolvidos
void livros_nao_devolvidos(Emprestimo *emprestimos, int emprestimo_count) {
    if (emprestimo_count == 0) {
        printf("Nenhum empréstimo encontrado.\n");
        return;
    }

    printf("Livros não devolvidos:\n");
    for (int i = 0; i < emprestimo_count; i++) {
        if (emprestimos[i].is_devolvido == 0) {
            printf("Título: %s\n", emprestimos[i].titulo);
            printf("Usuário: %s\n", emprestimos[i].user);
            printf("Data de empréstimo: %s", ctime(&(emprestimos[i].data_emprestimo)));
            printf("Data de devolução: %s", ctime(&(emprestimos[i].data_devolucao)));
        }
    }
}

void locatarios_com_mais_livros_emprestados(Emprestimo **emprestimos, int *emprestimo_count) {
    relatorio_carregar_emprestimos("emprestimos.csv", emprestimos, emprestimo_count);
    UserCount *counts = NULL;
    int num_users = 0;

    // Contar empréstimos por usuário
    for (int i = 0; i < *emprestimo_count; i++) {
        int found = 0;
        for (int j = 0; j < num_users; j++) {
            if (strcmp((*emprestimos)[i].user, counts[j].nome) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            UserCount *new_counts = (UserCount *)realloc(counts, (num_users + 1) * sizeof(UserCount));
            if (new_counts == NULL) {
                printf("Erro ao realocar a lista de usuários.\n");
                free(counts);
                return;
            }

            counts = new_counts;
            strncpy(counts[num_users].nome, (*emprestimos)[i].user, sizeof(counts[num_users].nome) - 1);
            counts[num_users].nome[sizeof(counts[num_users].nome) - 1] = '\0';
            counts[num_users].count = 1;
            num_users++;
        }
    }

    int max_emprestimos = 0;
    for (int i = 0; i < num_users; i++) {
        if (counts[i].count > max_emprestimos) {
            max_emprestimos = counts[i].count;
        }
    }

    printf("Locatários com mais livros emprestados:\n");
    for (int i = 0; i < num_users; i++) {
        if (counts[i].count == max_emprestimos) {
            printf("Usuário: %s\n", counts[i].nome);
            printf("Quantidade de empréstimos: %d\n", counts[i].count);
        }
    }

    free(counts);
}

#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>  // For `strerror`


int copias_atuais(int copias, int copias_emprestadas) {
    return copias - copias_emprestadas;
}

int id_exists_in_emprestimos(FILE *emprestimosFile, int id) {
    rewind(emprestimosFile);  // Reposiciona o ponteiro do arquivo para o início
    Emprestimo emprestimo;
    while (fscanf(emprestimosFile, "%d,%99[^,],%99[^,],%49[^,],%d,%d,%d,%49[^,],%d,%ld,%ld\n",
                  &emprestimo.id,
                  emprestimo.titulo,
                  emprestimo.autor,
                  emprestimo.genero,
                  &emprestimo.copias_emprestadas,
                  &emprestimo.copias,
                  &emprestimo.copias_atuais,
                  emprestimo.user,
                  &emprestimo.is_devolvido,
                  &emprestimo.data_emprestimo,  // `time_t` should use `%ld`
                  &emprestimo.data_devolucao    // `time_t` should use `%ld`
    ) == 11) {
        if (emprestimo.id == id) {
            return 1;  // ID encontrado
        }
    }
    return 0;  // ID não encontrado
}

void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath) {
    FILE *livrosFile = fopen(livrosFilePath, "r");
    FILE *emprestimosFile = fopen(emprestimosFilePath, "a+"); // Modo append e leitura para verificar duplicações

    if (!livrosFile || !emprestimosFile) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Livro livro;
    char buffer_emprestimo[20];  // Buffer para a data no formato YYYY-MM-DD
    char buffer_devolucao[20];   // Buffer para a data no formato YYYY-MM-DD

    while (fscanf(livrosFile, "%d,%99[^,],%99[^,],%49[^,],%d\n", &livro.id, livro.titulo, livro.autor, livro.genero, &livro.copias) == 5) {
        if (!id_exists_in_emprestimos(emprestimosFile, livro.id)) {  // Verifica se o ID já existe
            Emprestimo emprestimo;
            emprestimo.id = livro.id;
            strcpy(emprestimo.titulo, livro.titulo);
            strcpy(emprestimo.autor, livro.autor);
            strcpy(emprestimo.genero, livro.genero);
            emprestimo.copias_emprestadas = 0;
            emprestimo.copias = livro.copias;
            emprestimo.copias_atuais = livro.copias;
            strcpy(emprestimo.user, "Desconhecido");
            emprestimo.is_devolvido = 0;
            emprestimo.data_emprestimo = time(NULL);
            emprestimo.data_devolucao = 0;

            // Converte time_t para struct tm
            struct tm *tm_emprestimo = localtime(&emprestimo.data_emprestimo);
            struct tm *tm_devolucao = localtime(&emprestimo.data_devolucao);

            // Formata as datas como strings
            strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d", tm_emprestimo);
            strftime(buffer_devolucao, sizeof(buffer_devolucao), "%Y-%m-%d", tm_devolucao);

            // Adiciona ao arquivo de empréstimos
            fprintf(
                    emprestimosFile,
                    "%d,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n",
                    emprestimo.id,
                    emprestimo.titulo,
                    emprestimo.autor,
                    emprestimo.genero,
                    emprestimo.copias_emprestadas,
                    emprestimo.copias,
                    emprestimo.copias_atuais,
                    emprestimo.user,
                    emprestimo.is_devolvido,
                    buffer_emprestimo,
                    buffer_devolucao
            );
        }
    }

    fclose(livrosFile);
    fclose(emprestimosFile);
}


void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    char buffer_emprestimo[11];  // Buffer to hold date in YYYY-MM-DD format
    char buffer_devolucao[11];   // Buffer to hold date in YYYY-MM-DD format

    for (int i = 0; i < emprestimo_count; i++) {
        strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d", localtime(&emprestimos[i].data_emprestimo));
        strftime(buffer_devolucao, sizeof(buffer_devolucao), "%Y-%m-%d", localtime(&emprestimos[i].data_devolucao));

        fprintf(file, "%d,%s,%s,%s,%d,%d,%s,%d,%s,%s\n",
                emprestimos[i].id,
                emprestimos[i].titulo,
                emprestimos[i].autor,
                emprestimos[i].genero,
                emprestimos[i].copias,
                emprestimos[i].copias_emprestadas,
                emprestimos[i].user,
                emprestimos[i].copias_atuais,
                buffer_emprestimo,
                buffer_devolucao);
    }

    fclose(file);
}

void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    char titulo[MAX_TITULO];
    char user[MAX_UTILIZADOR];

    printf("Digite o título do livro a ser emprestado: \n");
    while(getchar() != '\n');  // limpa o buffer do stdin
    scanf("%[^\n]", titulo);
    getchar();  // limpa o buffer do stdin
    printf("Digite o nome do locatario: \n");
    scanf("%[^\n]", user);


    int book_found = 0;  // Flag to check if the book was found

    for (int i = 0; i < count; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            book_found = 1;  // Book was found
            if (livros[i].copias > 0) {
            }
        }
        if (strcmp(livros[i].titulo, titulo) == 0) {
            if (livros[i].copias > 0) {
                livros[i].copias--;
                Emprestimo *temp = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
                if (temp == NULL) {
                    fprintf(stderr, "Erro ao alocar memória para o empréstimo: %s\n", strerror(errno));
                    return;
                }
                *emprestimos = temp;


                (*emprestimos)[*emprestimo_count].id = livros[i].id;
                strcpy((*emprestimos)[*emprestimo_count].titulo, livros[i].titulo);
                strcpy((*emprestimos)[*emprestimo_count].autor, livros[i].autor);
                strcpy((*emprestimos)[*emprestimo_count].genero, livros[i].genero);
                (*emprestimos)[*emprestimo_count].copias = livros[i].copias;
                (*emprestimos)[*emprestimo_count].copias_emprestadas = 1;
                strcpy((*emprestimos)[*emprestimo_count].user, user);
                (*emprestimos)[*emprestimo_count].copias_atuais = copias_atuais(livros[i].copias, 1);
                (*emprestimos)[*emprestimo_count].is_devolvido = 0;
                (*emprestimos)[*emprestimo_count].data_emprestimo = time(NULL);
                (*emprestimos)[*emprestimo_count].data_devolucao = time(NULL) + 604800;  // 7 dias
                (*emprestimo_count)++;

                // Save the updated emprestimos to the file
                guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
                return;
            } else {
                printf("Livro não disponível para empréstimo.\n");
                return;
            }
        }
            }

            if (!book_found) {
                printf("Livro não encontrado.\n");
            }
        }

void carregar_emprestimos(const char *filename, Emprestimo **emprestimos, int *emprestimo_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    Emprestimo temp;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%d,%[^,],%d,%ld,%ld\n",
                  &temp.id, temp.titulo, temp.autor, temp.genero, &temp.copias,
                  &temp.copias_emprestadas, temp.user, &temp.copias_atuais,
                  &temp.data_emprestimo, &temp.data_devolucao) == 10) {
        Emprestimo *new_emprestimos = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
        if (new_emprestimos == NULL) {
            printf("Erro ao alocar memória para o empréstimo.\n");
            fclose(file);
            return;
        }
        *emprestimos = new_emprestimos;
        (*emprestimos)[*emprestimo_count] = temp;
        (*emprestimo_count)++;
    }

    fclose(file);
}
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    carregar_emprestimos("emprestimos.csv", emprestimos, emprestimo_count);
    printf("Digite o título do livro a ser devolvido: ");
    char titulo[MAX_TITULO];
    while(getchar() != '\n');  // limpa o buffer do stdin
    scanf("%[^\n]", titulo);
    getchar();  // limpa o buffer do stdin
    if (*emprestimo_count == 0) {
        printf("Nenhum livro emprestado.\n");
        return;
    } else {
        int book_found_in_livros = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(livros[j].titulo, titulo) == 0) {
                livros[j].copias++;
                book_found_in_livros = 1;
                break;
            }
        }
        if (!book_found_in_livros) {
            printf("Livro não encontrado na biblioteca.\n");
            return;
        }
        for (int i = 0; i < *emprestimo_count; i++) {
            if (strcmp((*emprestimos)[i].titulo, titulo) == 0) {
                // Remove o empréstimo do array
                for (int k = i; k < *emprestimo_count - 1; k++) {
                    (*emprestimos)[k] = (*emprestimos)[k + 1];
                }
                Emprestimo *temp = realloc(*emprestimos, (*emprestimo_count - 1) * sizeof(Emprestimo));
                if (temp == NULL && *emprestimo_count > 1) {
                    printf("Erro ao alocar memória para o empréstimo: %s\n", strerror(errno));
                    exit(1);
                }
                *emprestimos = temp;

                (*emprestimo_count)--;
                printf("Livro devolvido com sucesso.\n");
                guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
                return;
            }
        }
        printf("Livro não encontrado nos empréstimos.\n");
        guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
    }
}

void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count) {
    carregar_emprestimos("emprestimos.csv", &emprestimos, &emprestimo_count);
    printf("Digite o título do livro a ser renovado: ");
    char titulo[MAX_TITULO];
    while(getchar() != '\n');  // limpa o buffer do stdin
    scanf("%[^\n]", titulo);
    getchar();  // limpa o buffer do stdin
    if (emprestimo_count == 0) {
        printf("Nenhum livro emprestado.\n");
        return;
    } else {
        for (int i = 0; i < emprestimo_count; i++) {
            if (strcmp(emprestimos[i].titulo, titulo) == 0) {
                emprestimos[i].data_devolucao += 604800;  // Adiciona mais 7 dias
                printf("Empréstimo renovado com sucesso.\n");
                guardar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count);
                return;
            }
        }
        printf("Livro não encontrado nos empréstimos.\n");
        guardar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count);
    }
}

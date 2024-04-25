#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>  // For `strerror`#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>  // For `strerror`


int copias_atuais(int copias, int copias_emprestadas) {
    return copias - copias_emprestadas;
}

// Função para fechar arquivos e garantir limpeza em caso de erro
void fechar_arquivos(FILE *livrosFile, FILE *emprestimosFile, FILE *posFile) {
    if (livrosFile) fclose(livrosFile);
    if (emprestimosFile) fclose(emprestimosFile);
    if (posFile) fclose(posFile);
}


// Função para verificar se um ID já existe no arquivo de empréstimos
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
                  &emprestimo.data_emprestimo,
                  &emprestimo.data_devolucao) == 11) {
        if (emprestimo.id == id) {
            return 1;
        }
    }
    return 0;
}

// Função para copiar dados de livros para empréstimos
void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath, const char *posFilePath, int emprestimo_count) {
    FILE *livrosFile = fopen(livrosFilePath, "r");
    FILE *emprestimosFile = fopen(emprestimosFilePath, "w");
    FILE *posFile = fopen(posFilePath, "r+");

    if (!livrosFile || !emprestimosFile || !posFile) {
        printf("Erro ao abrir os arquivos.\n");
        fechar_arquivos(livrosFile, emprestimosFile, posFile);
        return;
    }

    long lastPos = 0;
    if (fscanf(posFile, "%ld", &lastPos) != 1) {
        lastPos = 0;
    }

    fseek(livrosFile, lastPos, SEEK_SET);

    Livro livro;
    char buffer_emprestimo[20];
    char buffer_devolucao[20];

    for (int i = 0; i < emprestimo_count; i++) {
        if (fscanf(livrosFile, "%d,%99[^,],%99[^,],%49[^,],%d\n", &livro.id, livro.titulo, livro.autor, livro.genero, &livro.copias) != 5) {
            printf("Erro na leitura dos dados do livro.\n");
            fechar_arquivos(livrosFile, emprestimosFile, posFile);
            return;
        }

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
        emprestimo.data_emprestimo = time(NULL); // Data do empréstimo

        // Formatação da data do empréstimo
        struct tm *tm_emprestimo = localtime(&emprestimo.data_emprestimo);
        strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d", tm_emprestimo);

        // Para data de devolução, usamos uma string vazia, já que ela não é configurada
        strcpy(buffer_devolucao, "N/A"); // Se a devolução não estiver definida

        fprintf(emprestimosFile,
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
                buffer_devolucao);
    }

    lastPos = ftell(livrosFile); // Atualiza a posição do arquivo após a leitura
    rewind(posFile); // Reposiciona para reescrever a posição
    fprintf(posFile, "%ld", lastPos);

    fechar_arquivos(livrosFile, emprestimosFile, posFile); // Garante fechamento dos arquivos
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

void guardar_emprestimo(const char *filePath, Emprestimo *emprestimos, int emprestimo_count) {
    FILE *file = fopen(filePath, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < emprestimo_count; i++) {
        // Write the emprestimo data to the file
        // This is just a placeholder, replace with your actual code
        fprintf(file, "%d,%s,%s,%s,%d,%d,%d,%s,%d,%ld,%ld\n",
                emprestimos[i].id,
                emprestimos[i].titulo,
                emprestimos[i].autor,
                emprestimos[i].genero,
                emprestimos[i].copias_emprestadas,
                emprestimos[i].copias,
                emprestimos[i].copias_atuais,
                emprestimos[i].user,
                emprestimos[i].is_devolvido,
                emprestimos[i].data_emprestimo,
                emprestimos[i].data_devolucao);
    }

    fclose(file);
}


int copias_atuais(int copias, int copias_emprestadas) {
    return copias - copias_emprestadas;
}

// Função para fechar arquivos e garantir limpeza em caso de erro
void fechar_arquivos(FILE *livrosFile, FILE *emprestimosFile, FILE *posFile) {
    if (livrosFile) fclose(livrosFile);
    if (emprestimosFile) fclose(emprestimosFile);
    if (posFile) fclose(posFile);
}


// Função para verificar se um ID já existe no arquivo de empréstimos
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
                  &emprestimo.data_emprestimo,
                  &emprestimo.data_devolucao) == 11) {
        if (emprestimo.id == id) {
            return 1;
        }
    }
    return 0;
}

// Função para copiar dados de livros para empréstimos
void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath, const char *posFilePath, int emprestimo_count) {
    FILE *livrosFile = fopen(livrosFilePath, "r");
    FILE *emprestimosFile = fopen(emprestimosFilePath, "w");
    FILE *posFile = fopen(posFilePath, "r+");

    if (!livrosFile || !emprestimosFile || !posFile) {
        printf("Erro ao abrir os arquivos.\n");
        fechar_arquivos(livrosFile, emprestimosFile, posFile);
        return;
    }

    long lastPos = 0;
    if (fscanf(posFile, "%ld", &lastPos) != 1) {
        lastPos = 0;
    }

    fseek(livrosFile, lastPos, SEEK_SET);

    Livro livro;
    char buffer_emprestimo[20];
    char buffer_devolucao[20];

    for (int i = 0; i < emprestimo_count; i++) {
        if (fscanf(livrosFile, "%d,%99[^,],%99[^,],%49[^,],%d\n", &livro.id, livro.titulo, livro.autor, livro.genero, &livro.copias) != 5) {
            printf("Erro na leitura dos dados do livro.\n");
            fechar_arquivos(livrosFile, emprestimosFile, posFile);
            return;
        }

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
        emprestimo.data_emprestimo = time(NULL); // Data do empréstimo

        // Formatação da data do empréstimo
        struct tm *tm_emprestimo = localtime(&emprestimo.data_emprestimo);
        strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d", tm_emprestimo);

        // Para data de devolução, usamos uma string vazia, já que ela não é configurada
        strcpy(buffer_devolucao, "N/A"); // Se a devolução não estiver definida

        fprintf(emprestimosFile,
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
                buffer_devolucao);
    }

    lastPos = ftell(livrosFile); // Atualiza a posição do arquivo após a leitura
    rewind(posFile); // Reposiciona para reescrever a posição
    fprintf(posFile, "%ld", lastPos);

    fechar_arquivos(livrosFile, emprestimosFile, posFile); // Garante fechamento dos arquivos
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

void guardar_emprestimo(const char *filePath, Emprestimo *emprestimos, int emprestimo_count) {
    FILE *file = fopen(filePath, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < emprestimo_count; i++) {
        // Write the emprestimo data to the file
        // This is just a placeholder, replace with your actual code
        fprintf(file, "%d,%s,%s,%s,%d,%d,%d,%s,%d,%ld,%ld\n",
                emprestimos[i].id,
                emprestimos[i].titulo,
                emprestimos[i].autor,
                emprestimos[i].genero,
                emprestimos[i].copias_emprestadas,
                emprestimos[i].copias,
                emprestimos[i].copias_atuais,
                emprestimos[i].user,
                emprestimos[i].is_devolvido,
                emprestimos[i].data_emprestimo,
                emprestimos[i].data_devolucao);
    }

    fclose(file);
}
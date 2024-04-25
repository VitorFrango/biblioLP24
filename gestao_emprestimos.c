#include "gestao_emprestimos.h"
#include "gestao_livros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>  // Para `strerror`



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
    rewind(emprestimosFile);
    char line[256];
    int idFromFile;
    while (fgets(line, sizeof(line), emprestimosFile) != NULL) {
        sscanf(line, "%d", &idFromFile);
        if (id == idFromFile) {
            return 1;
        }
    }
    return 0;
}

// Função para copiar dados de livros para empréstimos
void copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath, const char *posFilePath, int emprestimo_count) {
    FILE *livrosFile = fopen(livrosFilePath, "r");
    FILE *emprestimosFile = fopen(emprestimosFilePath, "a+");
    FILE *posFile = fopen(posFilePath, "r+");

    if (!livrosFile || !emprestimosFile || !posFile) {
        fprintf(stderr, "Erro ao abrir os arquivos: %s\n", strerror(errno));
        fechar_arquivos(livrosFile, emprestimosFile, posFile);
        return;
    }

    long lastPos = 0;
    if (fscanf(posFile, "%ld", &lastPos) != 1) {
        lastPos = 0; // Se falhar, começar do início
    }

    fseek(livrosFile, lastPos, SEEK_SET);

    Livro livro;
    char buffer_emprestimo[20];
    char buffer_devolucao[20];

    for (int i = 0; i < emprestimo_count; i++) {
        if (fscanf(livrosFile, "%d,%99[^,],%99[^,],%49[^,],%d\n", &livro.id, livro.titulo, livro.autor, livro.genero, &livro.copias) != 5) {
            fprintf(stderr, "Erro na leitura dos dados do livro: %s\n", strerror(errno));
            fechar_arquivos(livrosFile, emprestimosFile, posFile);
            return;
        }

        if (!id_exists_in_emprestimos(emprestimosFile, livro.id)) {
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

            struct tm *tm_emprestimo = localtime(&emprestimo.data_emprestimo);
            strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d", tm_emprestimo);

            strcpy(buffer_devolucao, "N/A"); // Data de devolução indefinida

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

            fflush(emprestimosFile); // Garantir escrita segura
        }
    }

    lastPos = ftell(livrosFile); // Atualiza a posição do arquivo após a leitura
    rewind(posFile); // Reposiciona para reescrever a posição
    fprintf(posFile, "%ld", lastPos);

    fechar_arquivos(livrosFile, emprestimosFile, posFile); // Garante fechamento seguro
}

void carregar_emprestimos(const char *filename, Emprestimo **emprestimos, int *emprestimo_count) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Emprestimo temp;
    char buffer_emprestimo[20], buffer_devolucao[20];
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%[^,],%[^,],%s\n",
                  &temp.id,
                  temp.titulo,
                  temp.autor,
                  temp.genero,
                  temp.user,
                  &temp.copias_emprestadas,
                  &temp.copias,
                  &temp.copias_atuais,
                  buffer_emprestimo,
                  buffer_devolucao) == 10) {
        // Convert the date strings to time_t
        struct tm tm;
        strptime(buffer_emprestimo, "%Y-%m-%d %H:%M:%S", &tm);
        temp.data_emprestimo = mktime(&tm);
        strptime(buffer_devolucao, "%Y-%m-%d %H:%M:%S", &tm);
        temp.data_devolucao = mktime(&tm);

        // Add the record to the array
        Emprestimo *new_ptr = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
        if (new_ptr == NULL) {
            fprintf(stderr, "Error reallocating memory: %s\n", strerror(errno));
            return;
        }
        *emprestimos = new_ptr;
        (*emprestimos)[*emprestimo_count] = temp;
        (*emprestimo_count)++;
    }

    fclose(file);
}


// Função para emprestar um livro
void empresta_livro(Livro* livros, int count, Emprestimo** emprestimos, int* emprestimo_count) {
    int livro_id;
    char user[MAX_UTILIZADOR];

    printf("Digite o ID do livro a ser emprestado: \n");
    while (getchar() != '\n'); // Limpa o buffer do stdin
    scanf("%d", &livro_id);
    getchar(); // Limpa o buffer do stdin

    printf("Digite o nome do locatário: \n");
    scanf("%[^\n]", user);
    getchar(); // Limpa o buffer do stdin

    int livro_encontrado = 0;

    for (int i = 0; i < count; i++) {
        if (livros[i].id == livro_id) {
            livro_encontrado = 1;

            if (livros[i].copias > 0) { // Verifica se há cópias disponíveis
                livros[i].copias--;

                Emprestimo* temp = realloc(*emprestimos, (*emprestimo_count + 1) * sizeof(Emprestimo));
                if (temp == NULL) {
                    fprintf(stderr, "Erro ao alocar memória para o empréstimo: %s\n", strerror(errno));
                    return;
                }

                *emprestimos = temp;
                Emprestimo* novo_emprestimo = &(*emprestimos)[*emprestimo_count];

                novo_emprestimo->id = livros[i].id;
                strcpy(novo_emprestimo->titulo, livros[i].titulo);
                strcpy(novo_emprestimo->autor, livros[i].autor);
                strcpy(novo_emprestimo->genero, livros[i].genero);
                novo_emprestimo->copias_emprestadas = 1;
                novo_emprestimo->copias_atuais = copias_atuais(livros[i].copias, 1);
                novo_emprestimo->is_devolvido = 0;
                novo_emprestimo->data_emprestimo = time(NULL); // Data do empréstimo
                novo_emprestimo->data_devolucao = time(NULL) + 604800; // 7 dias de empréstimo

                strncpy(novo_emprestimo->user, user, MAX_UTILIZADOR);
                novo_emprestimo->user[MAX_UTILIZADOR - 1] = '\0'; // Garante que o string seja terminado com '\0'

                *emprestimo_count += 1; // Aumenta a contagem de empréstimos

                // Abre o arquivo apenas uma vez
                guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);

                printf("Empréstimo realizado com sucesso.\n");
                return;
            } else {
                printf("Livro não disponível para empréstimo.\n");
                return;
            }
        }
    }

    if (!livro_encontrado) {
        printf("Livro não encontrado.\n");
    }
}


// Função para devolver um livro com base no ID e atualizar o empréstimo
void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count) {
    // Carrega empréstimos atualizados
    carregar_emprestimos("emprestimos.csv", emprestimos, emprestimo_count);

    if (*emprestimo_count < 0) {
        printf("Nenhum livro emprestado.\n");
        return;
    }

    int id;
    printf("Digite o ID do livro a ser devolvido:\n");
    while (getchar() != '\n'); // Limpa o buffer do stdin
    scanf("%d", &id);

    if (*emprestimo_count == 0) {
        printf("Nenhum livro emprestado.\n");
        return;
    }

    // Atualiza o número de cópias do livro
    int livro_encontrado = 0;
    for (int i = 0; i < count; i++) {
        if (livros[i].id == id) {
            livros[i].copias++; // Incrementa o número de cópias disponíveis
            livro_encontrado = 1;
            break;
        }
    }

    if (!livro_encontrado) {
        printf("Livro não encontrado na biblioteca.\n");
        return;
    }

    // Marca o empréstimo como devolvido
    int emprestimo_encontrado = 0;
    for (int i = 0; i < *emprestimo_count; i++) {
        if ((*emprestimos)[i].id == id) {
            (*emprestimos)[i].is_devolvido = 1; // Marca como devolvido
            emprestimo_encontrado = 1;
            printf("Livro devolvido com sucesso.\n");
            break;
        }
    }

    if (!emprestimo_encontrado) {
        printf("Empréstimo não encontrado para o ID fornecido.\n");
        return;
    }

    // Atualiza o arquivo CSV com o estado atualizado dos empréstimos
    guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
}

// Função para renovar um empréstimo
void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count) {
    carregar_emprestimos("emprestimos.csv", &emprestimos, &emprestimo_count);

    if (emprestimo_count == 0) {
        printf("Nenhum empréstimo para renovar.\n");
        return;
    }

    printf("Digite o ID do livro a ser renovado: \n");
    while (getchar() != '\n'); // Limpa o buffer do stdin
    int id;
    scanf("%d", &id);
    getchar(); // Limpa o buffer do stdin

    int emprestimo_encontrado = 0;
    for (int i = 0; i < emprestimo_count; i++) {
        if (emprestimos[i].id == id) {
            emprestimos[i].data_devolucao += 604800; // Adiciona mais 7 dias ao prazo de devolução
            emprestimo_encontrado = 1;
            printf("Empréstimo renovado com sucesso.\n");
            guardar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count); // Salva o arquivo atualizado
            return;
        }
    }

    if (!emprestimo_encontrado) {
        printf("Empréstimo com o ID fornecido não encontrado.\n");
    }

    guardar_emprestimo("emprestimos.csv", emprestimos, emprestimo_count);
}

// Função para salvar os dados de empréstimos
// Verifica se o arquivo já tem cabeçalho
int arquivo_tem_cabecalho(FILE *file) {
    fseek(file, 0, SEEK_SET); // Posiciona no início do arquivo
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return 0; // Sem cabeçalho
    }
    // Verifica se é o cabeçalho esperado
    return strstr(buffer, "id,titulo,autor,genero,user,data_emprestimo,data_devolucao") != NULL;
}

void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count) {
    FILE *file = fopen(filename, "a+"); // Modo de leitura/escrita
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Verifica se o cabeçalho já existe, e adiciona se necessário
    if (!arquivo_tem_cabecalho(file)) {
        fprintf(file, "id,titulo,autor,genero,copias,user,copias_atuais,copias_emprestadas,is_devolvido,data_emprestimo,data_devolucao\n");
    }

    char buffer_emprestimo[20], buffer_devolucao[20]; // Para armazenar as datas formatadas

    for (int i = 0; i < emprestimo_count; i++) {
        // Formata a data de empréstimo
        strftime(buffer_emprestimo, sizeof(buffer_emprestimo), "%Y-%m-%d %H:%M:%S", localtime(&emprestimos[i].data_emprestimo));

        // Formata a data de devolução
        strftime(buffer_devolucao, sizeof(buffer_devolucao), "%Y-%m-%d %H:%M:%S", localtime(&emprestimos[i].data_devolucao));

        // Grava no arquivo
        fprintf(file, "%d,%s,%s,%s,%d,%s,%d,%d,%d,%s,%s\n",
                emprestimos[i].id,
                emprestimos[i].titulo,
                emprestimos[i].autor,
                emprestimos[i].genero,
                emprestimos[i].copias,
                emprestimos[i].user,
                emprestimos[i].copias_atuais,
                emprestimos[i].copias_emprestadas,
                emprestimos[i].is_devolvido,
                buffer_emprestimo,
                buffer_devolucao);
    }

    fclose(file);
}


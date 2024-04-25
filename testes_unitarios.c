#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestao_emprestimos.h"
#include "gestao_livros.h"
#include "gera_relatorios.h"


// Função para testar se um livro é adicionado ao arquivo CSV com sucesso
void teste_adicionar_livro() {
    // Configurar o teste
    Livro livro;
    strcpy(livro.titulo, "Dom Quixote");
    strcpy(livro.autor, "Miguel de Cervantes");

    // Adicionar livro ao CSV
    int resultado = adicionar_livro_csv("livros.csv", &livro);

    // Validar resultado
    if (resultado == 0) {
        printf("Teste Adicionar Livro: Sucesso\n");
    } else {
        printf("Teste Adicionar Livro: Falha\n");
    }
}

// Função para testar se livros podem ser recuperados do arquivo CSV
void teste_obter_livros() {
    // Configurar o teste
    Livro livros[10];
    int total_livros = obter_livros_csv("livros.csv", livros, 10);

    // Validar resultado
    if (total_livros > 0 && strcmp(livros[0].titulo, "Dom Quixote") == 0) {
        printf("Teste Obter Livros: Sucesso\n");
    } else {
        printf("Teste Obter Livros: Falha\n");
    }
}

// Função para testar a integração entre adicionar e obter livros do CSV
void teste_integracao_livros_csv() {
    // Adicionar um livro ao CSV
    Livro livro;
    strcpy(livro.titulo, "Dom Quixote");
    strcpy(livro.autor, "Miguel de Cervantes");
    adicionar_livro_csv("livros.csv", &livro);

    // Obter livros do CSV para validar a integração
    Livro livros[10];
    int total_livros = obter_livros_csv("livros.csv", livros, 10);

    // Validar resultado
    if (total_livros > 0 && strcmp(livros[0].titulo, "Dom Quixote") == 0) {
        printf("Teste Integração Livros/CSV: Sucesso\n");
    } else {
        printf("Teste Integração Livros/CSV: Falha\n");
    }
}
// Função para testar se um empréstimo é adicionado com sucesso

void teste_adicionar_emprestimo() {
    Emprestimo *emprestimos = NULL;
    int count = 0;
    inicializar_emprestimos("emprestimos.csv", &emprestimos, &count);

    adicionar_emprestimo(&emprestimos, &count, "Teste", "Usuario Teste");

    if (emprestimos == NULL) {
        printf("Erro ao adicionar empréstimo.\n");
        return;
    }

    if (strcmp(emprestimos[count - 1].titulo, "Teste") != 0) {
        printf("Erro ao adicionar empréstimo: título incorreto.\n");
        return;
    }

    if (strcmp(emprestimos[count - 1].user, "Usuario Teste") != 0) {
        printf("Erro ao adicionar empréstimo: usuário incorreto.\n");
        return;
    }

    printf("Adicionar empréstimo: Sucesso.\n");
}



// Função para testar se o relatório de empréstimos é gerado corretamente

void teste_gerar_relatorio() {
    Emprestimo *emprestimos = NULL;
    int count = 0;
    inicializar_emprestimos("emprestimos.csv", &emprestimos, &count);

    adicionar_emprestimo(&emprestimos, &count, "Teste", "Usuario Teste");

    int resultado = gerar_relatorio();

    if (resultado != 1) {
        printf("Erro ao gerar relatório.\n");
        return;
    }

    printf("Gerar relatório: Sucesso.\n");
}

// Função para testar a interação entre adicionar empréstimos e gerar relatórios

void teste_integracao_emprestimo_relatorio() {
    Emprestimo *emprestimos = NULL;
    int count = 0;
    inicializar_emprestimos("emprestimos.csv", &emprestimos, &count);

    adicionar_emprestimo(&emprestimos, &count, "Teste", "Usuario Teste");

    int resultado = gerar_relatorio();

    if (resultado != 1) {
        printf("Erro ao gerar relatório.\n");
        return;
    }

    printf("Integração empréstimo e relatório: Sucesso.\n");
}


// Função principal para executar todos os testes
int main() {

    return 0;
}

cmake_minimum_required(VERSION 3.27)
project(biblioteca C)

set(CMAKE_C_STANDARD 11)

add_executable(biblioteca principal.c
        gestao_emprestimos.h
        gestao_emprestimos.c
        gera_relatorios.h
        gera_relatorios.c
        gestao_livros.c
        gestao_livros.h
        interface.c
        interface.h
        main.c
        teste_integracao.c
        teste_unidade_livros.c
        teste_unidade_emprestimos.c
)

cmake_minimum_required(VERSION 3.27)
project(biblioteca C)

set(CMAKE_C_STANDARD 11)

add_executable(biblioteca principal.c
        principal.c
        gestao_emprestimos.c
        gera_relatorios.c
        gestao_livros.c
        interface.c
        main.c)
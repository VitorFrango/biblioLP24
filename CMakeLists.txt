cmake_minimum_required(VERSION 3.27)
project(biblioteca C)

set(CMAKE_C_STANDARD 11)

add_executable(biblioteca main.c
        principal.h
        gestao_livros.h
        gestao_emprestimos.h
        gera_relatorios.h
        gera_relatorios.c
        gestao_emprestimos.c
        io_dados.h
        io_dados.c
        gestao_livros.c
        principal.c)

cmake_minimum_required(VERSION 3.27)
project(biblioteca C)

set(CMAKE_C_STANDARD 11)

add_executable(biblioteca principal.c
        principal.h
        gestao_emprestimos.h
        gestao_emprestimos.c
        gera_relatorios.h
        gera_relatorios.c
        io_dados.h
        io_dados.c
        gestao_livros.c
        gestao_livros.h
       )

cmake_minimum_required(VERSION 3.27)
project(biblioteca C)



include_directories(/opt/homebrew/Cellar/cunit/include)


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
        testes_unitarios.c
        testes_integracao.c

)
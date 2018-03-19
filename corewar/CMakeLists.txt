cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/op.h
        src/main.c
        src/main2.c
        src/vm_loop.c
        src/vm_loop1.c
        src/moving.c
        src/moving2.c
        src/log.c
        src/log1.c
        src/log2.c
        src/player_pars.c
        src/player_pars1.c
        libft/ft_printf/ft_printf.h
        src/process_init.c
        src/operation_processing.c
        src/operation_processing1.c
        src/operation_processing2.c
        src/operation_processing3.c
        src/operation_processing4.c
        src/operation_processing5.c
        src/operation_processing6.c
        src/operation_processing7.c
        )

add_subdirectory(libft)

include_directories(libft/includes libft/ft_printf)

add_executable(corewar ${SOURCE_FILES})

target_link_libraries(corewar libft.a)
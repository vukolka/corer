cmake_minimum_required(VERSION 3.9)
project(corewar C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/op.h
        src/main.c
        src/vm_loop.c
        src/moving.c
        src/log.c
        src/player_pars.c
        libft/ft_printf/ft_printf.h
        src/process_init.c
        src/operation_processing.c
        )

add_subdirectory(libft)

include_directories(libft/includes libft/ft_printf)

add_executable(corewar ${SOURCE_FILES})

target_link_libraries(corewar libft.a)
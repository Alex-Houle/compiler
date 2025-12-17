cmake_minimum_required(VERSION 3.20)

project(compiler
    VERSION 0.1
    LANGUAGES C
)

# -----------------------------
# C standard
# -----------------------------
set(CMAKE_C_STANDARD 11) 
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# -----------------------------
# Compiler warnings (strict)
# -----------------------------
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
)

# -----------------------------
# Export compile_commands.json
# (for clangd / LSP)
# -----------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Source files (frontend only)
# -----------------------------
set(FRONTEND_SOURCES
    main.c
    src/frontend/lexer.c
    src/frontend/parser.c
    src/frontend/ast.c
    src/frontend/keywords.c
    src/frontend/precedence.c
)

# -----------------------------
# Build compiler executable
# -----------------------------
add_executable(compiler ${FRONTEND_SOURCES})

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(compiler
    PRIVATE include
)

# -----------------------------
# Debug helpers
# -----------------------------
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g)
endif()

#include "frontend/lexer.h"
#include <stdio.h>
#include <stdlib.h>

void asm(Node *curr) {
    FILE *out = fopen("out.s", "w");
    if (!out) {
        perror("fopen");
        return;
    }

    fprintf(out, ".section .text\n");
    fprintf(out, ".globl _start\n\n");
    fprintf(out, "_start:\n");

    while (curr != NULL) {
        if (curr->data.type == RETURN_TOK) {
            if (curr->next != NULL && curr->next->data.type == INT_TOK) {
                fprintf(out, "    mov $60, %%rax\n"); // sys_exit
                fprintf(out, "    mov $%s, %%rdi\n",
                        curr->next->data.lexeme); // exit code
                fprintf(out, "    syscall\n");

                break; // stop after first return
            }
        }
        curr = curr->next;
    }

    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "not enough arguments\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("could not open file");
        return EXIT_FAILURE;
    }

    // Find file size
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(file);
        return EXIT_FAILURE;
    }

    long size = ftell(file);
    if (size < 0) {
        perror("ftell");
        fclose(file);
        return EXIT_FAILURE;
    }

    rewind(file);

    // Allocate buffer
    char *data = malloc((size_t)size + 1);
    if (!data) {
        perror("malloc");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read file
    size_t nread = fread(data, 1, (size_t)size, file);
    if (nread != (size_t)size && ferror(file)) {
        perror("fread");
        free(data);
        fclose(file);
        return EXIT_FAILURE;
    }

    data[nread] = '\0';

    Node *head = tokenize(data, size);
    Node *curr = head;
    asm(curr);
    system("as out.s -o out.o");
    system("ld out.o -o out");


    free(data);
    fclose(file);
    return EXIT_SUCCESS;
}

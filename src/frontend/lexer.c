#define _POSIX_C_SOURCE 200809L
#include "frontend/lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Node *tokenize(char *tokens, long size) {
    Node *head = NULL;
    Node *curr = NULL;

    for (int i = 0; i < size; i++) {
        char c = tokens[i];

        if (isalpha(c)) {
            char buf[512];
            int b = 0;
            while (i < size && isalnum(tokens[i])) {
                buf[b++] = tokens[i++];
            }
            buf[b] = '\0';
            i--;

            if (strcmp(buf, "return") == 0) {
                Node *tmp = malloc(sizeof(Node));
                tmp->data.lexeme = "return";
                tmp->data.type = RETURN_TOK;
                tmp->next = NULL;

                if (head == NULL) { head = tmp; curr = head; }
                else { curr->next = tmp; curr = tmp; }
            }
        } 
        // MOVED OUTSIDE of if(isalpha(c))
        else if (isdigit(c)) {
            char num_buf[64];
            int n = 0;
            while (i < size && isdigit(tokens[i])) {
                num_buf[n++] = tokens[i++];
            }
            num_buf[n] = '\0';
            i--;

            Node *tmp = malloc(sizeof(Node));
            tmp->data.type = INT_TOK;
            tmp->data.lexeme = strdup(num_buf);
            tmp->next = NULL;

            if (head == NULL) { head = tmp; curr = head; }
            else { curr->next = tmp; curr = tmp; }
        }
        else if (c == ';') {
            Node *tmp = malloc(sizeof(Node));
            tmp->data.type = SEMI_TOK;
            tmp->data.lexeme = ";";
            tmp->next = NULL;

            if (head == NULL) { head = tmp; curr = head; }
            else { curr->next = tmp; curr = tmp; }
        }
        else if (isspace(c)) {
            continue;
        } 
        else {
            printf("error at character: %c\n", c);
            exit(EXIT_FAILURE);
        }
    }
    return head;
}
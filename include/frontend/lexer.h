#ifndef LEXER_H
#define LEXER_H

typedef enum { RETURN_TOK, INT_TOK, SEMI_TOK } Tokentype;

typedef struct {
    Tokentype type;
    char *lexeme;
} Token;

typedef struct Node{
    Token data;
    struct Node *next;
} Node;

Node* tokenize(char *input, long size);

#endif
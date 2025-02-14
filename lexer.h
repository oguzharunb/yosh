#ifndef LEXER_H
# define LEXER_H

typedef enum { 
    TOKEN_WORD,				// Generic word // {{$ARG -> WORD}}
    TOKEN_ASSIGNMENT_WORD,	// Assignment operation (e.g., VAR=value)
    TOKEN_NAME,				// Name (e.g., function or variable name)
    TOKEN_NEWLINE,			// Newline character
    TOKEN_IO_NUMBER,		// File descriptor number

	TOKEN_GREAT,			// '>'
	TOKEN_LESS,				// '<'
    TOKEN_DLESS,			// '<<'
    TOKEN_DGREAT,			// '>>'
	TOKEN_PIPE,				// '|'

    TOKEN_EOF,				// End of file/input
    TOKEN_ERROR				// Error token
} TokenType;

typedef struct	s_token{
    TokenType	type;
    char		*value;
}			t_token;

#endif

// discuss params -> if everything is k create lexer
// checkout: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html#tag_18_10_02
// 2.10.2 Shell Grammar Rules

// in grammar rules it they gives the control sceme
// extract what is needed and what is not then implement parser.
// also check LR parser algo
// >>https://www.geeksforgeeks.org/shift-reduce-parser-compiler/

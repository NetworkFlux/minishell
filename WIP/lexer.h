#ifndef LEXER_H
# define LEXER_H

# include "wip.h"
# include "token.h"

typedef struct lexer_struct
{
	char	*src;
	size_t	src_size;
	char	c;
	unsigned int i;
}lexer_t;


lexer_t	*init_lexer(char *src);
void	lexer_advance(lexer_t *lexer);
token_t	*lexer_advanced_with(lexer_t *lexer, token_t *token);
void	lexer_skip_space(lexer_t *lexer);
token_t	*lexer_parse_id(lexer_t *lexer);
token_t	*lexer_next_token(lexer_t *lexer);

#endif
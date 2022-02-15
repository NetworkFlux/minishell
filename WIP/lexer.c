#include "lexer.h"

lexer_t	*init_lexer(char *src)
{
	lexer_t	*lexer;

	lexer = calloc(1, sizeof(lexer_t));
	lexer->src = src;
	lexer->i = 0;
	lexer->src_size = strlen(src);
	lexer->c = src[lexer->i];
	return (lexer);
}

void	lexer_advance(lexer_t *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c)
		lexer->i++;
}

token_t	*lexer_advanced_with(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}

void	lexer_skip_space(lexer_t *lexer)
{
	while (isspace(lexer->c))
		lexer_advance(lexer);
}

token_t	*lexer_parse_id(lexer_t *lexer)
{
	char	*value;

	value = calloc(1, sizeof(char));
	while (isalnum(lexer->c))
	{
		value = realloc(value, (strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]) {lexer->c, 0});
		lexer_advance(lexer);
	
	}
	return (init_token(value, TOKEN_ID));
}

token_t	*lexer_next_token(lexer_t *lexer)
{
	while (lexer->c)
	{
		if (isalnum(lexer->c))
			return (lexer_advance_with(lexer, lexer_parse_id(lexer)));
		switch (lexer->c)
		{
			case '=':
			{
				
			}break;
		}
	}
	return (0, TOKEN_EOF);
}
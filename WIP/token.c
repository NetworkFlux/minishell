#include "token.h"

token_t	*init_token(char *value, int type)
{
	token_t	*token;

	token = calloc(1, sizeof(token_t));
	token->value;
	token->type = type;
	return (token);
}
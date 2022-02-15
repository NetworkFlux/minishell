#ifndef TOKEN_H
# define TOKEN_H

# include "wip.h"

typedef struct token_struct
{
	char	*value;
	enum
	{
		TOKEN_EQUALS,
		TOKEN_ID,
		TOKEN_INT,
		TOKEN_PARENL,
		TOKEN_PARENR,
		TOKEN_EOF
	}type;
}token_t;

token_t	*init_token(char *value, int type);

#endif
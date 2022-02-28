/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:07 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/28 11:33:37 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_variable(char *str, size_t start, size_t end)
{
	char *variable;
	char *result;
	
	variable = ft_substr(str, start + 1, end - (start + 1));
	result = getenv(variable); 

	printf("result: |%s| var: |%s|\n", result, variable);

	if (getenv(variable) != NULL)
	{
		printf("<replace_variable> Should replace : |$%s| with |%s|\n", variable, result);
		printf("<replace_variable> str: |%s|\n", str);
	}
	else
	{
		printf("<replace_variable> Should remove: |%s| from |%s|\n", variable, str);
	}
	return (str);
}

/* if a variable is found $something (at least one char after $)
sends it to be replaced by its environment variable 
try:	>`export test="echo 'blabla'"`
		>$test
		>echo "hello $test"
*/
static char	*find_variable(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str && str[j])
			{
				if (!ft_isalpha((int) str[j]) && !ft_isdigit((int) str[j]))
					break;
				j++;
			}
			if (j - i  > 1)
				str = replace_variable(str, i, j);
			i = j;
		}
		i++;
	}
	return (str);
}

// look for $
// then look for its end 
// anything not [A-a,0-9] is the end
void	env_variables(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		g_fcmd->s_cmd[i]->s_cmd = find_variable(g_fcmd->s_cmd[i]->s_cmd);
		i++;
	}
	return ;
}
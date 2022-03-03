#include "minishell.h"

void	print_redir(t_scmd	*s_cmd, size_t j)
{
	size_t	i;

	printf("Current string without redir : %s\n", s_cmd->s_cmd);
	printf("Out redir in simple command %ld : %ld\n", j, s_cmd->redir->out);
	i = 0;
	while (i < s_cmd->redir->out)
	{
		printf("Out target %ld : %s\n", i + 1, s_cmd->redir->out_args[i]);
		i++;
	}
	printf("In redir in simple command %ld : %ld\n", j, s_cmd->redir->in);
	i = 0;
	while (i < s_cmd->redir->in)
	{
		printf("In target %ld : %s\n", i + 1, s_cmd->redir->in_args[i]);
		i++;
	}
	printf("Out out redir in simple command %ld : %ld\n", j, s_cmd->redir->outout);
	i = 0;
	while (i < s_cmd->redir->outout)
	{
		printf("Out out target %ld : %s\n", i + 1, s_cmd->redir->outout_args[i]);
		i++;
	}	
	printf("In in redir in simple command %ld : %ld\n", j, s_cmd->redir->inin);
	i = 0;
	while (i < s_cmd->redir->inin)
	{
		printf("In in target %ld : %s\n", i + 1, s_cmd->redir->inin_args[i]);
		i++;
	}
}

void	print_cmd(size_t i)
{
	t_scmd	*current;
	if (g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		current = g_fcmd->s_cmd[i];
		size_t o = 0;
		printf("<print_cmd> exec: %s\n", current->exec);
		while (o < current->ntokens && current->tokens[o])
		{
			// | the pipes are just there to see if there's no spaces around
			printf("<print_cmd> tk[%ld]: |%s|\n", o, current->tokens[o]->token);
			o++;
		}
		//print_redir(current, i + 1);
		printf("--------------------------\n");
		i++;
	}
}

void	debug_env(char *envv, char *str, char *result)
{
	printf("<debug_env> replace in : |%s| with |%s|\n", str, envv);
	printf("<debug_env> result: |%s|\n", result);
}

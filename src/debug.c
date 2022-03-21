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
		printf("<print_cmd> exec: %s\n", current->tokens[0]);
		while (o < current->ntokens && current->tokens[o])
		{
			// | the pipes are just there to see if there's no spaces around
			printf("<print_cmd> tk[%ld]: |%s|\n", o, current->tokens[o]);
			o++;
		}
		//print_redir(current, i + 1);
		printf("--------------------------\n");
		i++;
	}
}

void	print_tokens(t_scmd *scmd)
{
	size_t	i;

	i = 0;
	while (i < scmd->ntokens && scmd->tokens[i])
	{
		printf("token[%ld]: %s\n", i, scmd->tokens[i]);
		i++;
	}
}

void	print_env_array(char	**envp)
{
	size_t	i = 0;

	printf("--- DEBUG ENV ARRAY ---\n");

	while (envp[i] != NULL)
	{
		printf("DEBUG: %ld /%s\n", i, envp[i]);
		i++;
	}
}

void	print_env_list()
{
	g_fcmd->envp = env_first(g_fcmd->envp);
	while (g_fcmd->envp)
	{
		printf("%s=\"%s\"\n", g_fcmd->envp->name, g_fcmd->envp->value);
		if (!g_fcmd->envp->next)
			break ;
		g_fcmd->envp = g_fcmd->envp->next;
	}
}

void	print_array(char **array, char *str)
{
	printf("--- DEBUG (%s) ---\n", str);

	size_t	i;

	i = 0;
	while (i < ft_arrlen(array) && array[i])
	{
		printf("|%s|\n", array[i]);
		i++;
	}
}
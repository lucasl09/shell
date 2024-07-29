#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>
#include <stdlib.h>

static int	upgrade_args_cmds(t_token *current, int direction)
{
	if (direction == RIGHT)
	{
		while (current->next)
		{
			if (current->next->token == WORD)
				current->next->token = CMD_TOKEN;
			else
				break ;
			current = current->next;
		}
	}
	else
	{
		while (current->prev)
		{
			if (current->prev->token == WORD)
				current->prev->token = CMD_TOKEN;
			else
				break ;
			current = current->prev;
		}
	}
	return (TRUE);
}

static int	upgrade_operator(t_token *current)
{
	char	*new_content;

	if ((current->token >= 3 && current->token <= 5) && current->next)
	{
		if (current->next->token == WORD)
		{
			current->next->token = FTOKEN;
			new_content = release_quotes_expand(current->next->content);
			free(current->next->content);
			current->next->content = new_content;
		}
	}
	else if (current->token == FTOKEN && current->next)
	{
		if (current->next->token == WORD)
			upgrade_args_cmds(current, RIGHT);
	}
	if ((current->token >= 3 && current->token <= 5) && current->prev)
	{
		if (current->prev->token == WORD)
			upgrade_args_cmds(current, LEFT);
	}
	return (TRUE);
}

static int	upgrade_pipe(t_token *current)
{
	if (current->token == PIPE && current->next)
	{
		if (current->next->token == WORD)
			upgrade_args_cmds(current, RIGHT);
	}
	if (current->token == PIPE && current->prev)
	{
		if (current->prev->token == WORD)
			upgrade_args_cmds(current, LEFT);
	}
	return (TRUE);
}

static int	upgrade_dless(t_token *current)
{
	if (current->token == DLESS && current->next)
	{
		if (current->next->token == WORD)
			current->next->token = DTOKEN;
	}
	else if (current->token == DTOKEN && current->next)
	{
		if (current->next->token == WORD)
			upgrade_args_cmds(current, RIGHT);
	}
	if (current->token == DLESS && current->prev)
	{
		if (current->prev->token == WORD)
			upgrade_args_cmds(current, LEFT);
	}
	return (TRUE);
}

t_token	*manage_all_ttypes(t_token *current, int *has_operator,
				t_data *data, t_venv **envp)
{
	if (current->next == NULL)
	{
		current->token = CMD_TOKEN;
		current = manage_evar(current, envp, data);
		return (reorganize_tokens(&(data->token_list)));
	}
	while (current->next)
	{
		if ((current->token >= 3 && current->token <= 5) && current->next)
			*has_operator = upgrade_operator(current);
		else if ((current->token == DLESS || current->token == DTOKEN)
			&& current->next)
			*has_operator = upgrade_dless(current);
		else if (current->token == PIPE && current->next)
			*has_operator = upgrade_pipe(current);
		if (((current->token >= 3 && current->token <= 5)
				|| current->token == FTOKEN) && current->prev)
			*has_operator = upgrade_operator(current);
		else if (current->token == DLESS && current->prev)
			*has_operator = upgrade_dless(current);
		else if (current->token == PIPE && current->prev)
			*has_operator = upgrade_pipe(current);
		current = current->next;
	}
	return (current);
}

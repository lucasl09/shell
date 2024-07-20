#include "../../../includes/mandatory/mini_shell.h"

t_token	*get_nexttokenlst(t_data *data, t_venv **envp)
{
	t_token	*current;
	int		has_operator;

	current = data->token_list;
	has_operator = FT_ERROR;
	current = organize_eotokens(current, &has_operator, data, envp);
	if (!data->token_list || data->token_list->next == NULL)
		return (current);
	if (has_operator == FT_ERROR)
	{
		current = data->token_list;
		while (current)
		{
			current = get_envar_fornext(current, envp, data);
			if (current == NULL)
				break ;
			current->token = CMD_TOKEN;
			current = current->next;
		}
	}
	current = reorganize_tokens(&(data->token_list));
	return (current);
}

t_token	*get_envar_fornext(t_token *token, t_venv **envp, t_data *data)
{
	int		i;
	char	*final_line;
	char	*content;
	char	*env_key;
	int		has_single_quote;

	i = 0;
	final_line = NULL;
	content = token->content;
	has_single_quote = FT_ERROR;
	if (content[i] == '\'')
		has_single_quote = TRUE;
	while (content[i])
	{
		if (content[i] == '$' && has_single_quote == FT_ERROR && \
			ft_isspace(content[i + 1]) == 0 && content[i + 1])
		{
			env_key = concat_venv(&i, content, &final_line, data);
			if (env_key != NULL)
				detect_envs(env_key, &final_line, envp);
		}
		else
			concat_word(&i, content, &final_line, has_single_quote);
	}
	return (for_envtoken(token, &final_line, data));
}

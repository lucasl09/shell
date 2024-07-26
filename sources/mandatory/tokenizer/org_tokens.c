#include "../../../includes/mandatory/mini_shell.h"

t_token	*add_tlist(t_data *data, t_venv **envp)
{
	t_token	*current;
	int		has_operator;

	current = data->token_list;
	has_operator = FALSE;
	current = put_type_t(current, &has_operator, data, envp);
	if (!data->token_list || data->token_list->next == NULL)
		return (current);
	if (has_operator == FALSE)
	{
		current = data->token_list;
		while (current)
		{
			current = add_venv(current, envp, data);
			if (current == NULL)
				break ;
			current->token = CMD_TOKEN;
			current = current->next;
		}
	}
	current = reorganize_tokens(&(data->token_list));
	return (current);
}

t_token	*add_venv(t_token *token, t_venv **envp, t_data *data)
{
	int		i;
	char	*final_line;
	char	*content;
	char	*env_key;
	int		has_single_quote;

	i = 0;
	final_line = NULL;
	content = token->content;
	has_single_quote = FALSE;
	if (content[i] == '\'')
		has_single_quote = TRUE;
	while (content[i])
	{
		if (content[i] == '$' && has_single_quote == FALSE && \
			ft_isspace(content[i + 1]) == 0 && content[i + 1])
		{
			env_key = adjust_venv(&i, content, &final_line, data);
			if (env_key != NULL)
				env_entry(env_key, &final_line, envp);
		}
		else
			for_words(&i, content, &final_line, has_single_quote);
	}
	return (fixed_etokens(token, &final_line, data));
}

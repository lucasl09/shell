// #include "../../../includes/mandatory/mini_shell.h"

// static t_data	*initialize_data(int status)
// {
// 	t_data	*data;

// 	data = NULL;
// 	data = malloc(sizeof(t_data));
// 	if (!data)
// 		return (NULL);
// 	data->token_list = NULL;
// 	data->tree_lists = NULL;
// 	data->envp = NULL;
// 	data->last_status = status;
// 	data->has_env = FT_ERROR;
// 	return (data);
// }

// static int	build_data_storage(t_data *data, t_venv **envp, char *input)
// {
// 	if (build_token(input, &data->token_list) == ERROR)
// 		return (0);
// 	data->token_list = get_nexttokenlst(data, envp);
// 	if (data->token_list == NULL)
// 	{
// 		free_data(&data);
// 		return (0);
// 	}
// 	eotokens(&data->token_list, &data->tree_lists);
// 	if (!data->tree_lists)
// 		return (0);
// 	clear_tokens(&data->token_list);
// 	data->envp = *envp;
// 	return (1);
// }

// int	start_minishell(t_venv **envp, char *input, int status)
// {
// 	t_data	*data;

// 	data = initialize_data(status);
// 	signal(SIGINT, handle_new_line);
// 	if (!build_data_storage(data, envp, input))
// 		return (0);
// 	status = cmds_start(data, envp);
// 	signal(SIGINT, handle_new_line);
// 	release_heredoc(data->tree_lists);
// 	if (data)
// 		free_data(&data);
// 	return (status);
// }
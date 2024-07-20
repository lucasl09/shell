/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 16:17:51 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	ongoing_tree(t_tree *node, t_tree **tree_lists, t_token **token_list)
{
	if (node == NULL)
		return ;
	ongoing_tree(node->left, tree_lists, token_list);
	if (node->tree_type >= 4 && node->tree_type <= 8)
	{
		printf("\nINIT\n\n");
		if (execute_opr(node) == FT_ERROR)
		{
			free_list(tree_lists, token_list);
			exit(EXIT_FAILURE);
		}
		printf("\nEND\n\n");
	}
	ongoing_tree(node->right, tree_lists, token_list);
}

void	for_each_cmd(t_tree *node, t_token **token_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execute_command(node->content) == FT_ERROR)
		{
			free_list(&node, token_list);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}

void	initialize_execution(t_tree **tree_lists, t_token **token_list)
{
	t_tree	*cmd;

	if (tree_lists == NULL || *tree_lists == NULL)
		return ;
	cmd = *tree_lists;
	if (cmd->right == NULL && cmd->left == NULL)
		for_each_cmd(cmd, token_list);
	else
		ongoing_tree(cmd, tree_lists, token_list);
}

void handle_internal_command(char **args, t_data *data, t_venv **envp)
{
    t_token *current;

    current = data->token_list;
    if (ft_strcmp(current->content, "pwd") == 0)
        ft_pwd(0, current);
    else if (ft_strcmp(current->content, "clear") == 0)
        clear_screen();
    else if (ft_strcmp(current->content, "exit") == 0)
    {
        ft_free_tokens(current);
        exit(EXIT_SUCCESS);
    }
    else if (ft_strcmp(current->content, "cd") == 0)
        ft_cd(current);
    else if (ft_strcmp(current->content, "export") == 0)
        export_variable(current);
    else if (ft_strcmp(current->content, "unset") == 0)
        ft_unset(current);
    else if (ft_strcmp(current->content, "env") == 0)
        print_environment();
    else if (ft_strcmp(current->content, "echo") == 0)
        ft_echo(current);
}

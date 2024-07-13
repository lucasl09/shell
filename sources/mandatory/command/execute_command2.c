/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/29 16:58:33 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	execute_opr(t_tree *opr)
{
	if (opr->tree_type == LESS)
		return (init_redirect_input(opr));
	else if (opr->tree_type == GREAT)
		return (init_redirect_output(opr));
	else if (opr->tree_type == DGREAT)
		return (init_redirect_append(opr));
	else if (opr->tree_type == DLESS)
		return (init_heredoc(opr));
	else if (opr->tree_type == PIPE)
		return (init_pipe(opr));
	else
		return (EMPTY_OR_OT);
}

void	ongoing_tree(t_tree *node, t_tree **tree_list, t_token **token_list)
{
	if (node == NULL)
		return ;
	ongoing_tree(node->left, tree_list, token_list);
	if (node->tree_type >= 4 && node->tree_type <= 8)
	{
		printf("\nINIT\n\n");
		if (execute_opr(node) == KO)
		{
			free_list(tree_list, token_list);
			exit(EXIT_FAILURE);
		}
		printf("\nEND\n\n");
	}
	ongoing_tree(node->right, tree_list, token_list);
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
		if (execute_command(node->content) == FALSE)
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

void	initialize_execution(t_tree **tree_list, t_token **token_list)
{
	t_tree	*cmd;

	if (tree_list == NULL || *tree_list == NULL)
		return ;
	cmd = *tree_list;
	if (cmd->right == NULL && cmd->left == NULL)
		for_each_cmd(cmd, token_list);
	else
		ongoing_tree(cmd, tree_list, token_list);
}

void	handle_internal_command(t_token *tokens)
{
	if (ft_strcmp(tokens->content, "pwd") == 0)
		ft_pwd(0, tokens);
	else if (ft_strcmp(tokens->content, "clear") == 0)
		clear_screen();
	else if (ft_strcmp(tokens->content, "exit") == 0)
	{
		ft_free_tokens(tokens);
		exit(EXIT_SUCCESS);
	}
	else if (ft_strcmp(tokens->content, "cd") == 0)
		ft_cd(tokens);
	else if (ft_strcmp(tokens->content, "export") == 0)
		export_variable(tokens);
	else if (ft_strcmp(tokens->content, "unset") == 0)
		ft_unset(tokens);
	else if (ft_strcmp(tokens->content, "env") == 0)
		print_environment();
	else if (ft_strcmp(tokens->content, "echo") == 0)
		ft_echo(tokens);
}

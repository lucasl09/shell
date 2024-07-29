/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:34:32 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/07/14 16:41:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <unistd.h>
#include <stdio.h>

void	here_doc_eof(int line_num, char *content, char *line)
{
	char	*temp;
	char	*temp2;

	if (line == NULL)
	{
		temp = ft_itoa(line_num);
		temp2 = ft_strjoin("minihell: warning: here-document at line ", temp);
		free(temp);
		temp = ft_strjoin(temp2, " delimited by end-of-file (wanted `");
		free(temp2);
		temp2 = ft_strjoin(temp, content);
		free(temp);
		temp = ft_strjoin(temp2, ")\n");
		free(temp2);
		ft_putstr_fd(temp, STDERR_FILENO);
		free(temp);
	}
	else
	{
		free (line);
		line = NULL;
	}
}

int	release_heredoc(t_tree *opr)
{
	if (opr == NULL)
		return (0);
	if (ft_strncmp(opr->content, "<<", 3) == 0)
	{
		if (opr->tree_type == INPUT)
		{
			if (unlink(opr->right->content) == -1)
			{
				perror("Error unlinking file");
				return (-1);
			}
		}
	}
	if (opr->left)
		release_heredoc(opr->left);
	if (opr->right)
		release_heredoc(opr->right);
	return (0);
}

int	vheredoc_quote(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
			break ;
		i++;
	}
	if (content[i] == '\0')
		return (FALSE);
	else
		return (TRUE);
}

void	heredocwrite(char *line, int fd_heredoc,
		t_data *data, t_venv **envp)
{
	char	*full_line;
	char	*content;

	content = NULL;
	if (data->attribute == FALSE)
		content = expand_env(line, envp, data);
	if (content != NULL)
	{
		free(line);
		line = content;
	}
	full_line = ft_strjoin(line, "\n");
	ft_putstr_fd(full_line, fd_heredoc);
	free(line);
	line = NULL;
	free(full_line);
	full_line = NULL;
}

int	founded_hd(t_tree *stm, t_data *data, t_venv **envp)
{
	int			status;
	static int	index;

	status = 0;
	if (stm == NULL)
		return (status);
	if (ft_strncmp(stm->content, "<<", 3) == 0)
	{
		if (stm->tree_type == HERE_DOC)
			status = execute_heredoc(stm, data, envp, ++index);
	}
	if (stm->left)
		status = founded_hd(stm->left, data, envp);
	if (stm->right)
		status = founded_hd(stm->right, data, envp);
	return (status);
}

#include <unistd.h>
#include <stdio.h>
#include "../../../includes/mandatory/mini_shell.h"

void	endfile_heredoc(int line_num, char *content, char *line)
{
	char	*tmp;
	char	*tmp2;

	if (line == NULL)
	{
		tmp = ft_itoa(line_num);
		tmp2 = ft_strjoin("minishell: warning: here-document at line ", tmp);
		free(tmp);
		tmp = ft_strjoin(tmp2, " delimited by end-of-file (wanted `");
		free(tmp2);
		tmp2 = ft_strjoin(tmp, content);
		free(tmp);
		tmp = ft_strjoin(tmp2, ")\n");
		free(tmp2);
		ft_putstr_fd(tmp, STDERR_FILENO);
		free(tmp);
	}
	else
	{
		free (line);
		line = NULL;
	}
}

int	release_heredoc(t_tree *operator)
{
	if (operator == NULL)
		return (0);
	if (ft_strncmp(operator->content, "<<", 3) == 0)
	{
		if (operator->tree_type == INPUT)
		{
			if (unlink(operator->right->content) == -1)
			{
				perror("Error unlinking file");
				return (-1);
			}
		}
	}
	if (operator->left)
		release_heredoc(operator->left);
	if (operator->right)
		release_heredoc(operator->right);
	return (0);
}

int	has_qt_hc(char *content)
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
		return (FT_ERROR);
	else
		return (TRUE);
}

void	heredocwrite(char *line, int fd_heredoc,
		t_data *data, t_venv **envp)
{
	char	*full_line;
	char	*content;

	content = NULL;
	if (data->check_opr == FT_ERROR)
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

int	heredoc_delimiter(t_tree *stm, t_data *data, t_venv **envp)
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
		status = heredoc_delimiter(stm->left, data, envp);
	if (stm->right)
		status = heredoc_delimiter(stm->right, data, envp);
	return (status);
}

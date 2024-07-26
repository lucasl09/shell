#include "../../../includes/mandatory/mini_shell.h"

void	endfile_heredoc(int line_num, char *content, char *line)
{
	char	*temp;
	char	*temp2;

	if (line == NULL)
	{
		temp = ft_itoa(line_num);
		temp2 = ft_strjoin("minishell: warning: here-document at line ", temp);
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

int	find_hd_delimiter(t_tree *operator)
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
		find_hd_delimiter(operator->left);
	if (operator->right)
		find_hd_delimiter(operator->right);
	return (0);
}

int	verify_quotes_heredoc(char *content)
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

void	writeheredoc(char *line, int fd_heredoc,
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

int	find_heredocs(t_tree *root, t_data *data, t_venv **envp)
{
	int			status;
	static int	index;

	status = 0;
	if (root == NULL)
		return (status);
	if (ft_strncmp(root->content, "<<", 3) == 0)
	{
		if (root->tree_type == HERE_DOC)
			status = execute_heredoc(root, data, envp, ++index);
	}
	if (root->left)
		status = find_heredocs(root->left, data, envp);
	if (root->right)
		status = find_heredocs(root->right, data, envp);
	return (status);
}

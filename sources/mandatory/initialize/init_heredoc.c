#include "../../../includes/mandatory/mini_shell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	*expand_env(char *content, t_venv **envp, t_data *data)
{
	int		i;
	char	*final_line;
	char	*env_key;

	i = 0;
	final_line = NULL;
	while (content[i])
	{
		if (content[i] == '$')
		{
			env_key = adjust_venv(&i, content, &final_line, data);
			if (env_key != NULL)
				env_entry(env_key, &final_line, envp);
		}
		else
			for_words(&i, content, &final_line, FALSE);
	}
	return (final_line);
}

static int	check_loop_break(int line_num, char *content, char *line, int fd)
{
	if (!line || ft_strncmp(line, content, (ft_strlen(content) + 1)) == 0)
	{
		if (g_vsig != SIGINT)
			endfile_heredoc(line_num, content, line);
		if (g_vsig == SIGINT)
		{
			free (line);
			free (content);
			close(fd);
			return (130);
		}
		return (1);
	}
	return (0);
}

static int	loop_heredoc(t_tree *operator, int fd_heredoc, t_data *data,
		t_venv **envp)
{
	char	*content;
	int		line_num;
	char	*line;
	int		status;

	data->attribute = verify_quotes_heredoc(operator->right->content);
	content = quotes_exp(operator->right->content);
	line_num = 1;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		line_num++;
		status = check_loop_break(line_num, content, line, fd_heredoc);
		if (status == 130)
			return (status);
		else if (status == 1)
			break ;
		writeheredoc(line, fd_heredoc, data, envp);
	}
	free (content);
	return (fd_heredoc);
}

static int	open_heredoc_file(int index, char **filename)
{
	char	*num;
	int		fd_heredoc;

	num = ft_itoa(index);
	*filename = ft_strjoin("/tmp/heredoc_file", num);
	free(num);
	inheredoc(TRUE);
	fd_heredoc = open(*filename, O_CREAT | O_WRONLY, 0644);
	return (fd_heredoc);
}

int	execute_heredoc(t_tree *operator, t_data *data, t_venv **envp, int index)
{
	int		fd_heredoc;
	char	*filename;
	int		fd_in;

	filename = NULL;
	if (operator->left == NULL && operator->right == NULL)
		return (2);
	fd_heredoc = open_heredoc_file(index, &filename);
	if (fd_heredoc == -1)
		return (-1);
	fd_in = dup(STDIN_FILENO);
	fd_heredoc = loop_heredoc(operator, fd_heredoc, data, envp);
	close(fd_heredoc);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	free(operator->right->content);
	operator->right->content = filename;
	operator->tree_type = INPUT;
	inheredoc(FALSE);
	if (fd_heredoc == 130)
	{
		find_hd_delimiter(operator);
		return (fd_heredoc);
	}
	return (0);
}

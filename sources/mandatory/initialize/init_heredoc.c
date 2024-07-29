#include "../../../includes/mandatory/mini_shell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

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
			env_key = evarjoin(&i, content, &final_line, data);
			if (env_key != NULL)
				env_searched(env_key, &final_line, envp);
		}
		else
			concat_word(&i, content, &final_line, FALSE);
	}
	return (final_line);
}

static int	is_loop_checker(int line_num, char *content, char *line, int fd)
{
	if (!line || ft_strncmp(line, content, (ft_strlen(content) + 1)) == 0)
	{
		if (g_vsig != SIGINT)
			here_doc_eof(line_num, content, line);
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

static int	loop_heredoc(t_tree *opr, int fd_heredoc, t_data *data,
		t_venv **envp)
{
	char	*content;
	int		line_num;
	char	*line;
	int		status;

	data->attribute = vheredoc_quote(opr->right->content);
	content = release_quotes_expand(opr->right->content);
	line_num = 1;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		line_num++;
		status = is_loop_checker(line_num, content, line, fd_heredoc);
		if (status == 130)
			return (status);
		else if (status == 1)
			break ;
		heredocwrite(line, fd_heredoc, data, envp);
	}
	free (content);
	return (fd_heredoc);
}

static int	heredoc_opened(int index, char **filename)
{
	char	*num;
	int		fd_heredoc;

	num = ft_itoa(index);
	*filename = ft_strjoin("/tmp/heredoc_file", num);
	free(num);
	inside_heredoc(TRUE);
	fd_heredoc = open(*filename, O_CREAT | O_WRONLY, 0644);
	return (fd_heredoc);
}

int	execute_heredoc(t_tree *opr, t_data *data, t_venv **envp, int index)
{
	int		fd_heredoc;
	char	*filename;
	int		fd_in;

	filename = NULL;
	if (opr->left == NULL && opr->right == NULL)
		return (2);
	fd_heredoc = heredoc_opened(index, &filename);
	if (fd_heredoc == -1)
		return (-1);
	fd_in = dup(STDIN_FILENO);
	fd_heredoc = loop_heredoc(opr, fd_heredoc, data, envp);
	close(fd_heredoc);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	free(opr->right->content);
	opr->right->content = filename;
	opr->tree_type = INPUT;
	inside_heredoc(FALSE);
	if (fd_heredoc == 130)
	{
		release_heredoc(opr);
		return (fd_heredoc);
	}
	return (0);
}

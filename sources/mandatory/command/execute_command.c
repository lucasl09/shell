/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 14:32:08 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	print_environment(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env != NULL)
	{
		ft_printf("%s\n", *env);
		env++;
	}
}

char	**get_args(char *content)
{
	char	**quote;
	char	**has_arg;

	quote = NULL;
	has_arg = NULL;
	if (content[0] == '\'')
		quote = ft_split(content, '\'');
	else if (content[0] == '\"')
		quote = ft_split(content, '\"');
	if (quote != NULL)
	{
		has_arg = ft_split(quote[0], ' ');
		free(quote);
	}
	else
		has_arg = ft_split(content, ' ');

	return (has_arg);
}

int	execute_command(char *content)
{
	char	**has_arg;
	char	**args;
	char	*path;
	int		i;

	has_arg = get_args(content);
	path = ft_strdup("/bin/");
	if (path == NULL)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (has_arg[i])
		i++;
	args = (char **)malloc((i + 2) * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		free(path);
		exit(EXIT_FAILURE);
	}
	i = 0;
	args[0] = ft_strjoin(path, has_arg[0]);
	while (has_arg[i])
	{
		args[i + 1] = has_arg[i];
		i++;
	}
	args[i + 1] = NULL;
	if (execve(args[0], &args[1], __environ) == -1)
	{
		perror("execve");
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
		free(path);
		free(has_arg);
		return (ERROR);
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(has_arg);
	free(path);
	return (TRUE);
}

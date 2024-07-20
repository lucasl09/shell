#include "../../../includes/mandatory/mini_shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

extern volatile int	g_vsig;

void	get_term(int restore)
{
	static struct termios	terms;

	if (!restore)
		tcgetattr(STDIN_FILENO, &terms);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &terms);
}

static int	input_prompt(char *input)
{
	int	i;

	if (!input)
	{
		printf("exit\n");
		exit (0);
	}
	if (!ft_strncmp(input, "", 1))
	{
		free (input);
		return (0);
	}
	i = -1;
	while (input[++i])
	{
		if (ft_isspace(input[i]) == 0)
			break ;
	}
	if (input[i] == '\0')
	{
		free (input);
		return (0);
	}
	return (1);
}

static char	*each_user(t_venv **envp, char *tag)
{
	t_venv	*tmp;
	char		*user;

	tmp = env_lstsearch(envp, tag);
	user = NULL;
	if (!tag || !tmp)
		user = ft_strjoin("$", "/\033[1;31mMINIHELL>$\033[0m : ");
	else
		user = ft_strjoin(tmp->value, "\033[1;31mMINIHELL>$\033[0m : ");
	tmp = NULL;
	return (user);
}

static int	get_input(t_venv **envp, int status)
{
	char		*input;
	char		*in_user;
	int			valid;

	g_vsig = 0;
	in_user = each_user(envp, "USER");
	get_term(0);
	input = readline(in_user);
	free(in_user);
	valid = input_prompt(input);
	if (valid != TRUE)
		return (valid);
	add_history(input);
	if (!initialize_checker(input))
	{
		free (input);
		ft_putendl_fd("Error in syntax.", 2);
		return (2);
	}
	return (start_minishell(envp, input, status));
}

int	main(void)
{
	t_venv	*envp;
	int			status;

	for_signals();
	envp = NULL;
	status = 0;
	get_envp(&envp, __environ);
	while (1)
	{
		status = get_input(&envp, status);
		if (status == 131)
			printf("Quit (core dumped)\n");
		else if ((status == 2 || status == 0) && g_vsig == SIGINT)
		{
			printf("\n");
			status = 130;
		}
		if (status == 131 || (status == 2 && g_vsig == SIGINT))
			get_term(1);
	}
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	free_envp(&envp);
	rl_clear_history();
	return (status);
}

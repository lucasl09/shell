#include "../../../includes/mandatory/mini_shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

volatile int	g_vsig;

static int	is_v_input(char *input)
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

static char	*define_user(t_venv **envp, char *tag)
{
	t_venv	*tmp;
	char		*user;

	tmp = env_lstsearch(envp, tag);
	user = NULL;
	if (!tag || !tmp)
		user = ft_strjoin("", "\033[1;31m/MH> $\033[0m ");
	else
		user = ft_strjoin(tmp->value, "\033[1;31mMH> $\033[0m ");
	tmp = NULL;
	return (user);
}

void	prop(int attribute)
{
	static struct termios	term;

	if (!attribute)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static int	sucess_input(t_venv **envp, int status)
{
	char		*input;
	char		*in_user;
	int			valid;

	g_vsig = 0;
	in_user = define_user(envp, "");
	prop(0);
	input = readline(in_user);
	free(in_user);
	valid = is_v_input(input);
	if (valid != TRUE)
		return (valid);
	add_history(input);
	if (!all_checked(input))
	{
		free (input);
		ft_putendl_fd("Error in syntax.", 2);
		return (2);
	}
	return (init_minihell(envp, input, status));
}

int	main(void)
{
	t_venv	*envp;
	int			status;

	init_signals();
	initialize();
	envp = NULL;
	status = 0;
	get_envp(&envp, __environ);
	while (1)
	{
		status = sucess_input(&envp, status);
		if (status == 131)
			printf("Quit (core dumped)\n");
		else if ((status == 2 || status == 0) && g_vsig == SIGINT)
		{
			printf("\n");
			status = 130;
		}
		if (status == 131 || (status == 2 && g_vsig == SIGINT))
			prop(1);
	}
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	free_envp(&envp);
	rl_clear_history();
	return (status);
}

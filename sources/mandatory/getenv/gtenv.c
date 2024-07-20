#include "../../../includes/mandatory/mini_shell.h"

static char	*get_tlen(char *envp, int *len)
{
	char	*checked;

	*len = 0;
	while (envp[*len] != '=')
		(*len)++;
	checked = ft_strndup(envp, *len);
	*len += 1;
	return (checked);
}

void	get_envp(t_venv **envp, char **environ)
{
	char	*lenenv;
	char	*value;
	int		index;
	int		tlen;

	index = 0;
	tlen = 0;
	while (environ[index])
	{
		lenenv = get_tlen(environ[index], &tlen);
		value = ft_strdup(environ[index] + tlen);
		env_lstadd_back(envp, env_lstnew(lenenv, value));
		index++;
		free (lenenv);
		free (value);
	}
}
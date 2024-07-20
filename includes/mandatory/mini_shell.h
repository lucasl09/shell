/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 18:21:46 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <grp.h>
# include <limits.h>
# include <linux/limits.h>
# include <pwd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PATH_LEN 1024
# define ARG_MAX 4096 // Máximo do próprio shell//

typedef enum e_tokens		t_tokens;
enum						e_tokens
{
	DELIMITER_TOKEN = -3,
	CMD_TOKEN = -2,
	FILE_TOKEN = -1,
	NONE = 0,
	WORD,
	EXPANSION,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	PIPE,
};

typedef enum e_for_return (t_type_r);
enum						e_for_return
{
	END = 666,
	ERROR = -1,
	FT_ERROR = 0,
	TRUE = 1,
};

typedef enum e_sides		side;
enum						e_sides
{
	TO_LEFT = 1,
	TO_RIGHT,
};

typedef enum e_check		t_check;
enum						e_check
{
	EMPTY = -2,
	SUCESS = 0,
	CERROR = 1,
};

typedef enum e_tree_type	t_type_tree;
enum						e_tree_type
{
	STRING = 10,
	DELIMITER,
	FILENAME,
	COMMAND,
	OUTPUT,
	APPEND,
	INPUT,
	HERE_DOC,
	PIPE_LINE,
};

typedef struct s_env_var	t_venv;
struct						s_env_var
{
	char					*key;
	char					*value;
	t_venv				*next;
};

typedef struct s_token		t_token;
struct						s_token
{
	char					*content;
	t_tokens				token;
	t_token					*next;
	t_token					*prev;
};

typedef struct s_tree		t_tree;
struct						s_tree
{
	char					*content;
	t_type_tree				tree_type;
	t_token					*token_node;
	t_token					*left_token;
	t_token					*right_token;
	t_tree					*left;
	t_tree					*right;
};

// typedef struct s_mini
// {
// 	char					*name;
// 	char					*cmd_line;
// 	int						exported;
// 	int						aftercmd;
// 	struct s_mini			*next;
// }							t_mini;

typedef struct s_data		t_data;
struct						s_data
{
	t_token					*token_list;
	t_tree					*tree_lists;
	t_venv				*envp;
	int						last_status;
	int						check_opr;
	int						has_env;
	int						direction;
	int						pipe_fd[2];
	pid_t					fork[2];

};

// typedef struct s_alias
// {
// 	char					*name;
// 	char					*command;
// 	struct s_alias			*next;
// }							t_alias;

// functions not implementicio
// strndup -> ft_strndup

// Main
extern volatile int			g_vsig;
void	get_term(int restore);
int							main(void);

// Prompt
void	print_tokens(t_token *head);
void	for_signals(void);
void	handle_new_line(int signum);
void	handle_signal(int signum);
int	inside_heredoc(int inside_heredoc);

// Initialize
int	has_quotes(const char *input);
int	has_pipe(const char *input);
int	has_redirect(char const *input);
int	initialize_checker(const char *prompt);
t_tree	*cmd_found(t_tree **stm, int *count);
int	execute_mult_tree(t_tree *node, t_data *data, t_tree *cmd, int *fd);
int	initialize_cmdexec(t_data *data, t_tree *node);;
int	ongoing_exectree(t_tree *node, t_data *data);
int	cmds_start(t_data *data, t_venv **envp);
char	*expand_env(char *content, t_venv **envp, t_data *data);
int	execute_heredoc(t_tree *operator, t_data *data, t_venv **envp, int index);
int	finish_pipe(int *status, t_data *data);
int	execute_pipe(t_tree *node, t_data *data);
int	start_minishell(t_venv **envp, char *input, int status);
void	init_redirect(t_tree *opr, int fd, int redirect);
int	init_redirect_input(t_tree *opr);
int	init_redirect_output(t_tree *opr);
int	init_redirect_append(t_tree *opr);


// Tokenizer
int	build_token(char *cmd, t_token **token_list);
void	detect_envs(char *env_key, char **final_line, t_venv **envp);
char	*concat_venv(int *i, char *content, char **final_line, t_data *data);
void	concat_word(int *i, char *content, char **final_line, int has_s_quote);
t_token	*for_envtoken(t_token *token, char **final_line, t_data *data);
t_token	*reorganize_tokens(t_token **token_list);
t_token	*reorganize_redirect_tokens(t_token *stm);
int	initialize_parsetoken(char *cmd_line, int *size, int has_quote);
t_token	*newtoken(char *content, t_tokens type);
void	token_to_back(t_token **lst, t_token *new);
t_token	*last_token(t_token *lst);


// Expansion
char	*remove_quotes_expansion(char *content);
char	*in_quote_getarg(char *content);
char	*get_cmds_args_word(char *content);


// Command
int	execute_command(t_tree *node, t_data *data, t_venv **envp, int direction);
void handle_internal_command(char **args, t_data *data, t_venv **envp);
int	open_redir_input(t_tree *operator);
int	open_redir_output(t_tree *operator);
int	consume_rdirect(t_tree *node, t_tree **cmd);
int	open_redir_append(t_tree *operator);
char	**get_path(t_venv **envp, char *var, char *cmd);
char	**get_has_arg(t_tree *node, int direction);
int	ongoing_cmds(t_tree *node, t_data *data, t_venv **envp);
int	consume_rdirect(t_tree *node, t_tree **cmd);


// Builtins
int						builtins(t_token *tokens);
void						export_variable(t_token *tokens);
char						*ft_realpath(const char *path, char *resolved_path);
void						ft_pwd(int argc, t_token *tokens);
void						ft_echo(t_token *tokens);
void						clear_screen(void);
void						ft_cd(t_token *tokens);

// Utils
char	*ft_strspn_end(char *str, const char *delim);
char	*ft_strtok(char *str, const char *delim);
int	ft_lstsize_token(t_token *head);
void	ft_unset(t_token *tokens);
void	ft_valid_malloc(int *pipefds);
t_tree	*tree_new(char *content, t_tokens token_type);
size_t	ft_strcspn(const char *s, const char *reject);
size_t	ft_strspn(const char *s, const char *accept);
void	for_treeleft(t_tree **lst, t_tree *new);
void	for_treeright(t_tree **lst, t_tree *new);
t_type_r	open_file(const char *content);
t_type_tree	initialize_type(char *content, t_tokens token);
void	tree_build_nodes(t_token *new_node, t_tree **tree_list, int direction);
void	check_multi_cmd_right(t_tree *node, t_tree *current_prop);
void	check_multi_cmd_left(t_tree *node, t_tree *current_prop);
void	eotokens(t_token **token_list, t_tree **tree_list);
t_tree	*break_nodes(t_token *current, t_tree **tree_list, int direction);
void	continue_division(t_tokens operator, t_tree **tree_list,
		t_tree *current_prop, int direction);
void	for_left_node(t_tokens operator, t_tree *current_prop,
		t_tree **tree_list, int status);
void	for_right_node(t_tokens operator, t_tree *current_prop,
		t_tree **tree_list, int status);
void	endfile_heredoc(int line_num, char *content, char *line);
int	release_heredoc(t_tree *operator);
int	has_qt_hc(char *content);
void	heredocwrite(char *line, int fd_heredoc,
		t_data *data, t_venv **envp);
int	heredoc_delimiter(t_tree *stm, t_data *data, t_venv **envp);
char	*get_cmds_args_word(char *content);
void	end_evg_error(char **all_args);
int	end_evg(t_data *data, t_venv **envp, char **has_arg);
int	check_exit(char *input);
char	**exit_checkerexec(t_tree *node, int direction);
t_token	*organize_eotokens(t_token *current, int *has_operator,
				t_data *data, t_venv **envp);
t_token	*create_redirect_token(int *i, char *cmd_line, char c);
void	create_quote_token(char *cmd_line, int *size);
t_token	*find_last_cmd(t_token *current);
void	relink_tokens(t_token *target, t_token *first_cmd, t_token *last_cmd,
				t_token *input);
t_token	*redirecttoken(int *i, char *cmd_line);


// Free
void						treelst_clear(t_tree **lst);
void						clear_tokens(t_token **lst);
void						ft_free_tokens(t_token *tokens);
void						free_list(t_tree **tree_list, t_token **token_list);
void						free_data(t_data **data);
void						fkclose(int *fd, char *error);
void						free_envp(t_venv **envp);
void						free_ptargs(char **path_args, char **args);
void						free_trash(char **trash);

//ENV
t_venv	*env_lstnew(char *key, char *value);
void	env_lstadd_back(t_venv **lst, t_venv *new);
void	env_lstclear(t_venv **lst);
t_venv	*env_lstsearch(t_venv **lst, char *key);
int	env_size(t_venv **env);
void	get_envp(t_venv **envp, char **environ);

#endif
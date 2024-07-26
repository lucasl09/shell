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

typedef enum e_tree_type		t_type_tree;
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

typedef enum e_returned		t_typereturned;
enum						e_returned
{
	END = 666,
	ERROR = -1,
	FALSE = 0,
	TRUE = 1,
};

typedef enum e_sides		t_forsided;
enum						e_sides
{
	LEFT = 0,
	RIGHT,
};

typedef enum e_check		t_check;
enum						e_check
{
	OTHERS = -2,
	OK = 0,
	KO = 1,
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
	t_token					*left_token;
	t_token					*right_token;
	t_tree					*left;
	t_tree					*right;
};

typedef struct s_venv	t_venv;
struct						s_venv
{
	char					*key;
	char					*value;
	t_venv				*next;
};

typedef struct s_cmd		t_cmd;
struct						s_cmd
{
	char					*bin;
	char					**executed;
};

typedef struct s_data		t_data;
struct						s_data
{
	t_token					*token_list;
	t_tree					*tree_lists;
	t_venv				*envp;
	int						for_sts;
	int						attribute;
	int						has_env;
	int						direction;
	int						pipe_fd[2];
	pid_t					fork[2];

};

extern volatile int			g_vsig;

int							initialize_mini(t_venv **envp, char *input,
								int status);
int							inheredoc(int inheredoc);
void						putnewline(int signum);
void						handle_signal(int signum);
void						for_signals(void);
char						*ft_strndup(const char *src, int size);
void	get_envp(t_venv **envp, char **environ);
int							create_token(char *cmd_line, t_token **token_list);
t_token						*for_tredirect(int *i, char *cmd_line,
								char c);
void						for_tquote(char *cmd_line, int *size);
t_token						*last_history_cmd(t_token *current);
void						fix_ttokens(t_token *target, t_token *first_cmd,
								t_token *last_cmd,
								t_token *input);
t_token						*initialize_rdt(int *i, char *cmd_line);
t_token						*newtoken(char *content, t_tokens type);
void						put_lasttoken(t_token **lst, t_token *new);
t_token						*verify_lastlst(t_token *lst);
void						clear_tokens(t_token **lst);
t_token						*put_type_t(t_token *current,
								int *has_operator, t_data *data,
								t_venv **envp);
t_token						*add_tlist(t_data *data, t_venv **envp);
t_token						*add_venv(t_token *token, t_venv **envp,
								t_data *data);
t_token						*fix_tredirects(t_token *root);
int							parse_ttokens(char *cmd_line, int *size,
								int has_quote);
void						env_entry(char *env_key,
								char **final_line, t_venv **envp);
char						*adjust_venv(int *i, char *content,
								char **final_line, t_data *data);
void						for_words(int *i, char *content,
								char **final_line, int has_single_quote);
t_token						*fixed_etokens(t_token *token,
								char **final_line, t_data *data);
t_token						*reorganize_tokens(t_token **token_list);
void						eotokens(t_token **token_list,
								t_tree **tree_lists);
void						tree_addright(t_tree **lst, t_tree *new);
void						tree_addleft(t_tree **lst, t_tree *new);
t_tree						*tree_new(char *content, t_tokens type);
void						tree_clear(t_tree **lst);
void						initialize_treenode(t_token *new_node,
								t_tree **tree_lists, int direction);
int	return_checker(const char *input);
t_type_tree					initialize_checker(t_tokens token);
void						verify_leftcmds(t_tree *node,
								t_tree *current_tree_node);
void						verify_rightcmds(t_tree *node,
								t_tree *current_tree_node);
t_tree						*break_nodes(t_token *current, t_tree **tree_lists,
								int state);
void						for_left_cnodes(t_tokens operator,
								t_tree *ast_current_node, t_tree **tree_lists,
								int status);
void						for_right_cnodes(t_tokens operator,
								t_tree *ast_current_node, t_tree **tree_lists,
								int status);
int							initialize_builtins(char **args, t_data *data,
								t_venv **envp);
int							ft_pwd(char *input);
int							ft_cd(char **input, t_venv **envp);
int							ft_clear(char *input);
int							ft_echo(char **arg, t_data *data);
int							ft_env(t_venv **envp, int status);
int							ft_unset(t_venv **head, char *key);
void						ft_bexport(char *var, t_venv **envp);
int							print_venv(t_venv *env);
int							initialize_execs(t_data *data, t_venv **envp);
int							execute_ast(t_tree *node, t_data *data);
char						**get_cmd_args(t_tree *node, int direction);
char						**get_path(t_venv **envp, char *var, char *cmd);
t_tree						*find_cmd(t_tree **root, int *count);
int							manage_tree_rdt(t_tree *node, \
								t_tree **cmd);
int							execute_command(t_tree *node, t_data *data,
								t_venv **envp, int direction);
int							for_errors(char **cmd_args, t_venv **envp,
								int status);
t_venv					*env_lstnew(char *key, char *value);
void						env_lstadd_back(t_venv **lst, \
								t_venv *new_node);
void						env_lstclear(t_venv **lst);
t_venv					*env_lstsearch(t_venv **lst, char *key);
int							env_size(t_venv **env);
void						get_envp(t_venv **envp, char **environ);
int							verify_prompt(const char *input);
int							check_pipe(const char *input);
void						fkclose(int *fd, char *error);
void						free_evg(char **matrix);
void						free_storage(t_data **data);
void						free_envp(t_venv **envp);
void						free_onlyargs(char **path_args, char **args);
char						*ft_with_quote(char *content);
char						*ft_with_word(char *content);
char						*quotes_exp(char *content);
int							input_rdt(t_tree *operator);
int							output_rdt(t_tree *operator);
int							rdt_expand(t_tree *operator);
int							execute_heredoc(t_tree *operator, t_data *data,
								t_venv **envp, int index);
char						*expand_env(char *content, t_venv **envp,
								t_data *data);
int							end_evg(t_data *data,
								t_venv **envp, char **cmd_args);
int							if_exit(char *input);
char						**if_exit_execute(t_tree *node, int direction);
int							execute_pipe(t_tree *operator, t_data *data);
int							endpipes(int *status, t_data *data);
int							for_each_cmd(t_tree *node, t_data *data, \
								t_venv **envp);
void						endfile_heredoc(int line_num, char *content, \
								char *line);
int							find_hd_delimiter(t_tree *operator);
int							verify_quotes_heredoc(char *content);
void						writeheredoc(char *line, int fd_heredoc, \
								t_data *data, t_venv **envp);
int							find_heredocs(t_tree *root, t_data *data,
								t_venv **envp);

#endif

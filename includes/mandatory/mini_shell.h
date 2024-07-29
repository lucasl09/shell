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

# include <sys/types.h>
# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"

typedef enum e_tokens		t_tokens;
enum						e_tokens
{
	DTOKEN = -3,
	CMD_TOKEN = -2,
	FTOKEN = -1,
	NONE = 0,
	WORD,
	EXPANSION,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	PIPE,
};

typedef enum e_tree_typed		t_types_tree;
enum						e_tree_typed
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

typedef enum e_return		t_returned;
enum						e_return
{
	END = 666,
	ERROR = -1,
	FALSE = 0,
	TRUE = 1,
};

typedef enum e_fside		t_sided;
enum						e_fside
{
	LEFT = 0,
	RIGHT,
};

typedef enum e_check		t_check;
enum						e_check
{
	NFOUND = -2,
	SUCESS = 0,
	FAILED = 1,
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
	t_types_tree				tree_type;
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
	char					*flagpath;
	char					**executed;
};

typedef struct s_data		t_data;
struct						s_data
{
	t_token					*token_list;
	t_tree					*tree_listed;
	t_venv				*envp;
	int						endsts;
	int						attribute;
	int						has_env;
	int						direction;
	int						pipe_fd[2];
	pid_t					fork[2];

};

extern volatile int			g_vsig;
int							init_minihell(t_venv **envp, char *input,
								int status);
int							inside_heredoc(int inside_heredoc);
void						sig_newline(int signum);
void						handle_signal(int signum);
void						init_signals(void);
char						*ft_strndup(const char *src, int size);
int							build_token(char *cmd_line, t_token **token_list);
t_token						*create_redirect_token(int *i, char *cmd_line,
								char c);
void						create_quote_token(char *cmd_line, int *size);
t_token						*find_cmdtoken(t_token *current);
void						relink_tokens(t_token *target, t_token *first_cmd,
								t_token *last_cmd,
								t_token *input);
t_token						*build_redirect_token(int *i, char *cmd_line);
t_token						*token_lstnew(char *content, t_tokens type);
void						token_lstadd_back(t_token **lst, t_token *new);
t_token						*token_lstlast(t_token *lst);
void						tokenlst_clear(t_token **lst);
t_token						*manage_all_ttypes(t_token *current,
								int *has_operator, t_data *data,
								t_venv **envp);
t_token						*manage_tlists(t_data *data, t_venv **envp);
t_token						*manage_evar(t_token *token, t_venv **envp,
								t_data *data);
t_token						*reorganize_redirect_tokens(t_token *stm);
int							parse_created_tokens(char *cmd_line, int *size,
								int has_quote);
void						env_searched(char *env_key,
								char **final_line, t_venv **envp);
char						*evarjoin(int *i, char *content,
								char **final_line, t_data *data);
void						concat_word(int *i, char *content,
								char **final_line, int has_single_quote);
t_token						*fix_envtoken(t_token *token,
								char **final_line, t_data *data);
t_token						*reorganize_tokens(t_token **token_list);
void						eotokens(t_token **token_list,
								t_tree **tree_listed);
void						tree_addright(t_tree **lst, t_tree *new);
void						tree_addleft(t_tree **lst, t_tree *new);
t_tree						*tree_new(char *content, t_tokens type);
void						treelst_clear(t_tree **lst);
void						build_tnode(t_token *new_node,
								t_tree **tree_listed, int direction);
t_types_tree					type_check(t_tokens token);
void						has_left_cmds(t_tree *node,
								t_tree *current_tnode);
void						has_right_cmds(t_tree *node,
								t_tree *current_tnode);
t_tree						*cut_all(t_token *current, t_tree **tree_listed,
								int state);
void						cut_tleft(t_tokens opr,
								t_tree *current_node_in, t_tree **tree_listed,
								int status);
void						cut_tright(t_tokens opr,
								t_tree *current_node_in, t_tree **tree_listed,
								int status);
int							init_builtins(char **args, t_data *data,
								t_venv **envp);
int							call_pwd(char *input);
int							ft_changedir(char **input, t_venv **envp);
int							ft_clear(char *input);
int							ft_echo(char **arg, t_data *data);
int							ft_env(t_venv **envp, int status);
int							ft_unset(t_venv **head, char *key);
void						ft_exported_env(char *var, t_venv **envp);
int							ft_envprints(t_venv *env);
int							ongoing_exec(t_data *data, t_venv **envp);
int							initialize_trees(t_tree *node, t_data *data);
char						**get_cmd_args(t_tree *node, int direction);
char						**get_path(t_venv **envp, char *var, char *cmd);
t_tree						*foundedcmd(t_tree **stm, int *count);
int							rltree_redirect(t_tree *node, \
								t_tree **cmd);
int							execute_command(t_tree *node, t_data *data,
								t_venv **envp, int direction);
int							execution_error(char **cmd_args, t_venv **envp,
								int status);
t_venv					*env_lstnew(char *key, char *value);
void	env_lstadd_back(t_venv **lst, t_venv *new);
void						env_lstclear(t_venv **lst);
t_venv					*env_lstsearch(t_venv **lst, char *key);
int							env_size(t_venv **env);
void						get_envp(t_venv **envp, char **environ);
int							all_checked(const char *input);
int							has_pipe_in(const char *input);
void						fkclose(int *fd, char *error);
void						free_trash(char **trash);
void						free_data(t_data **data);
void						free_envp(t_venv **envp);
void						free_args(char **path_args, char **args);
char						*arg_with_quote(char *content);
char						*arg_just_word(char *content);
char						*release_quotes_expand(char *content);
int							put_redirect_in(t_tree *opr);
int							put_redirect_out(t_tree *opr);
int							append_redirects(t_tree *opr);
int							execute_heredoc(t_tree *opr, t_data *data,
								t_venv **envp, int index);
char						*expand_env(char *content, t_venv **envp,
								t_data *data);
int							exit_minihell(t_data *data,
								t_venv **envp, char **cmd_args);
int							check_exit(char *input);
char						**if_exited(t_tree *node, int direction);
int							execute_pipe(t_tree *opr, t_data *data);
int							endpipes(int *status, t_data *data);
int							executables_init(t_tree *node, t_data *data, \
								t_venv **envp);
void						here_doc_eof(int line_num, char *content, \
								char *line);
int							release_heredoc(t_tree *opr);
int							vheredoc_quote(char *content);
void						heredocwrite(char *line, int fd_heredoc, \
								t_data *data, t_venv **envp);
int							founded_hd(t_tree *stm, t_data *data,
								t_venv **envp);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int	execution_error(char **cmd_args, t_venv **envp, int status);
void	initialize(void);

#endif

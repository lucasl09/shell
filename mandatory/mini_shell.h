/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/29 16:00:38 by roglopes         ###   ########.fr       */
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

typedef enum e_tokens tokens;
enum	e_tokens
{
	NONE = 0,
	WORD,
	EXPANSION,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
};

typedef enum e_for_return	t_type_r;
enum	e_for_return
{
	END = 666,
	ERROR = -1,
	FALSE = 0,
	TRUE = 1,
};

typedef enum e_sides	side;
enum	e_sides
{
	TO_LEFT = 1,
	TO_RIGHT,
};

typedef enum e_check	check;
enum	e_check
{
	KO = -1,
	EMPTY_OR_OT = 0,
	SUCESS = 1,
};

typedef enum e_tree_type type_tree;
enum	e_tree_type
{
	STRING = 10,
	FILENAME,
	COMMAND,
	OUTPUT,
	INPUT,
	APPEND,
	HERE_DOC,
	PIPE_LINE,
};

typedef struct	s_token	t_token;
struct	s_token
{
	char		*content;
	tokens		token;
	t_token		*next;
	t_token		*prev;
};

typedef struct s_tree	t_tree;
struct	s_tree
{
	char		*content;
	type_tree	tree_type;
	t_token		*token_node;
	t_token		*left_token;
	t_token		*right_token; 
	t_tree		*left;
	t_tree		*right;
};


typedef struct s_mini
{
	char				*name;
	char				*cmd_line;
	int					exported;
	int					aftercmd;
	struct s_mini		*next;
}						t_mini;

typedef struct s_alias
{
	char				*name;
	char				*command;
	struct s_alias		*next;
}						t_alias;


// Main
// void					initialize(void);
// void					process_command_line(t_mini *mini);
// void					main_loop(t_mini *mini);

// Prompt
char					*prompt(void);

// Signal
void					handle_signal(int sign);
int						afterprompt(int is_after);

// Create Token
t_token	*token_for_redirect(int *i, char *cmd_line);
t_token	*is_word_token(int *i, char *cmd_line);
t_token	*token_expanded(int *i, char *cmd_line);
t_token	*is_quote_token(int *i, char *cmd_line);
int	initialize_buildtoken(char *cmd_line, t_token **token_list);

// Tokenizer
t_token	*newtoken(char *content, tokens type);
void	token_to_back(t_token **lst, t_token *new);
t_token	*last_token(t_token *lst);

// Expansions
// char					*expand_variable(const char *variable);
// void					append_variable_expanded(char **expanded,
// 							const char **cursor);
// void					append_char_expanded(char **expanded,
// 							const char **cursor);
// void					expand_token(t_token *token);
// void					expand_variables_tokens(t_token *head);
// void					append_value(char **expanded, const char *value);
// char					*get_variable_name(const char **cursor);

// Command
void					print_environment(void);
char	**get_args(char *content);
int	execute_command(char *content);

// Command 2
int	execute_opr(t_tree *opr);
void	ongoing_tree(t_tree *node, t_tree **tree_list, t_token **token_list);
void	for_each_cmd(t_tree *node, t_token **token_list);
void	initialize_execution(t_tree **tree_list, t_token **token_list);

// Builtins
void					export_variable(t_token *tokens);
char					*ft_realpath(const char *path,
							char *resolved_path);
void					ft_pwd(int argc, t_token *tokens);
void					ft_echo(t_token *tokens);
void					clear_screen(void);
void					ft_cd(t_token *tokens);
void					builtins(t_token *tokens);

// Utils
char					*ft_strtok(char *str, const char *delim);
char					*ft_strspn_end(char *str, const char *delim);
size_t					ft_strcspn(const char *s, const char *reject);
size_t					ft_strspn(const char *s, const char *accept);
int						ft_lstsize_token(t_token *head);
void					ft_unset(t_token *tokens);
t_tree					*tree_new(char *content, tokens token_type);
void					tree_add_left(t_tree **lst, t_tree *new);
void					tree_add_right(t_tree **lst, t_tree *new);
t_type_r				open_file(const char *content);
void					ft_valid_malloc(int *pipefds);
type_tree				initialize_type(char *content, tokens token);

// Free
void					ft_free_tokens(t_token *tokens);
void					clear_tokens(t_token **lst);
void					treelst_clear(t_tree **lst);
void					ft_free_tokens(t_token *tokens);
void					free_list(t_tree **tree_list, t_token **token_list);
// void					ft_free_string_array(char **array);
// char					*ft_strjoin_free(char *s1, char *s2);
// void					free_commands(char ***commands);

// Initialize
int		initialize_checker(const char *prompt);
void	initialize_node(t_token *new_node, t_tree **lists, int mode);
t_tree	*break_nodes(t_token *current, t_tree **lists, int mode);
void	for_left_node(tokens opr, t_tree *nodes_in_exec, t_tree **lists);
void	for_right_node(tokens opr, t_tree *nodes_in_exec, t_tree **lists);
int	planting_tree(t_token **token_list, tokens opr, t_tree **lists);
void	eotokens(t_token **token_list, t_tree **lists);
void	init_redirect(t_tree *opr, int fd, int redirect);
int	init_redirect_input(t_tree *opr);
int	init_redirect_output(t_tree *opr);
int	init_redirect_append(t_tree *opr);

#endif
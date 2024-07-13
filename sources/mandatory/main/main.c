/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/15 13:53:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// void	print_tokens(t_token *head)
// {
// 	while (head != NULL)
// 	{
// 		ft_printf("Recebido: %s \nToken de tipo: %d\n\n", head->text, head->type);
// 		head = head->next;
// 	}
// }

// void	process_command_line(t_mini *mini)
// {
// 	t_token	*tokens;
// 	int		input_fd = STDIN_FILENO;
// 	int		output_fd = STDIN_FILENO;

// 	if (mini->cmd_line && *mini->cmd_line)
// 	{
// 		tokens = input_tokenizer(mini->cmd_line);
// 		expand_variables_tokens(tokens);
// 		if (setup_redirection(tokens, &input_fd, &output_fd) == -1)
// 		{
// 			ft_free_tokens(tokens);
// 			return ;
// 		}
// 		//handle_redirection_and_execution(tokens, input_fd, output_fd);
// 		handle_redirection_and_execution(tokens);
// 		print_tokens(tokens);
// 		ft_free_tokens(tokens);
// 	}
// 	else
// 	{
// 		ft_printf("Failed to split command line\n");
// 	}
// }

// void	main_loop(t_mini *mini)
// {
// 	while (1)
// 	{
// 		mini->cmd_line = prompt();
// 		if (!mini->cmd_line)
// 		{
// 			ft_printf("\n");
// 			exit(EXIT_SUCCESS);
// 		}
// 		process_command_line(mini);
// 		free(mini->cmd_line);
// 	}
// }

void	initialize_lists(t_token **token_list, t_tree **tree_list)
{
	ft_printf("\033[1;33mMINIHELL started!\033[0m\n");
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_signal);
	*token_list = malloc(sizeof(t_token *) + 1);
	*tree_list = malloc(sizeof(t_tree *) + 1);
	*token_list = NULL;
	*tree_list = NULL;
}

int main(void)
{
    while (1)
    {
        if (prompt() == 0)
            break;
    }
    rl_clear_history();
    return 0;
}

#include "../../../includes/mandatory/mini_shell.h"

int	handle_heredoc(t_tree *opr)
{
	if (opr->left != NULL)
		printf("\nCOMMAND_L: %s\n", opr->left->content);
	if (opr->right != NULL)
		printf("\nCOMMAND_R: %s\n", opr->right->content);
	return (SUCESS);
}

int	handle_pipes(t_tree *opr)
{
	if (opr->left != NULL)
		printf("\nCOMMAND_L: %s\n", opr->left->content);
	if (opr->right != NULL)
		printf("\nCOMMAND_R: %s\n", opr->right->content);
	return (SUCESS);
}

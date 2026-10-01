/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_token *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	root->left = NULL;
	free_tree(root->right);
	root->right = NULL;
	if (root->txt)
		free(root->txt);
	root->txt = NULL;
	free(root);
	root = NULL;
}

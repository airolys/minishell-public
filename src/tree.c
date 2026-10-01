/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

t_token	*insert_in(t_token *token, t_token *root, t_token *root_LR)
{
	if (!root)
	{
		root_LR->left = token;
		return (root_LR);
	}
	token->left = root_LR;
	if (root->left == root_LR)
		root->left = token;
	else
		root->right = token;
	return (root);
}

void	walk_insert(t_token *root, t_token_type stop_type, t_token *token)
{
	t_token	*curr;
	t_token	*prev;

	prev = NULL;
	curr = root;
	while (curr->left && !(curr->type & stop_type))
	{
		if (curr->type & LPARENT && curr->right)
			break ;
		prev = curr;
		if (curr->type & SEPARATOR && !(token->type & SEPARATOR))
			curr = curr->right;
		else
			curr = curr->left;
	}
	insert_in(token, prev, curr);
	if (token->type & REDIRECT && token->next && token->next->type & WORDS)
	{
		token->right = token->next;
		token->next = token->next->next;
		token->right->next = NULL;
	}
}

void	insert_rparent(t_token *root, t_token *token)
{
	t_token	*lastlpar;
	t_token	*curr;

	curr = root;
	lastlpar = NULL;
	while (curr->left)
	{
		if (curr->type & LPARENT && !curr->right)
			lastlpar = curr;
		if (curr->type & SEPARATOR)
			curr = curr->right;
		else
			curr = curr->left;
	}
	lastlpar->right = token;
}

t_token	*place_in_tree(t_token *token, t_token *root)
{
	if (!token)
		return (root);
	if (root == NULL)
		root = token;
	else if (token->type & RPARENT)
		insert_rparent(root, token);
	else if (token->type & (AND_IF | OR_IF))
		walk_insert(root, PIPE | REDIRECT | WORDS | AND_IF | OR_IF, token);
	else if (token->type & PIPE)
		walk_insert(root, REDIRECT | WORDS | PIPE, token);
	else if (token->type & REDIRECT)
		walk_insert(root, WORDS, token);
	else
	{
		if (root->type & (SEPARATOR))
			root->right = place_in_tree(token, root->right);
		else
			root->left = place_in_tree(token, root->left);
	}
	return (root);
}

void	build_tree(t_data *data)
{
	t_token	*head;
	t_token	*tmp;
	int		in_cmd;

	in_cmd = 0;
	data->tree = make_token("ROOT", 4, ROOT);
	if (!data->tree)
		return ;
	head = data->tokens->first;
	tmp = head;
	while (tmp)
	{
		if (!in_cmd && tmp->type & WORDS)
		{
			in_cmd = 1;
			data->tree = place_in_tree(make_token(NULL, 0, CMD), data->tree);
		}
		if (!(tmp->type & WORDS) && !(tmp->type & REDIRECT))
			in_cmd = 0;
		data->tree = place_in_tree(tmp, data->tree);
		tmp = tmp->next;
	}
}
	//show_token_tree(data->tree, 0, NULL);

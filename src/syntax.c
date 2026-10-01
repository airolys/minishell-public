/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token *t)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	if (t)
		write(STDERR_FILENO, t->txt, ft_strlen(t->txt));
	else
		write(STDERR_FILENO, "newline", 7);
	write(STDERR_FILENO, "'\n", 2);
	return (1);
}

int	syntax_condition(t_tokens *t, t_token *curr)
{
	if (curr->type & (SEPARATOR | REDIRECT))
	{
		if (curr->type & SEPARATOR && curr == t->first)
			return (syntax_error(curr));
		if (!curr->next || curr->next->type & (SEPARATOR | REDIRECT))
			return (syntax_error(curr->next));
	}
	return (0);
}

int	syntax_check(t_tokens *t)
{
	t_token	*curr;
	int		parcount;

	parcount = 0;
	curr = t->first;
	while (curr)
	{
		if (syntax_condition(t, curr))
			return (1);
		if (curr->type & LPARENT)
		parcount++;
		if (curr->type & RPARENT)
		{
			if (!parcount)
				return (syntax_error(curr));
			parcount--;
		}
		curr = curr->next;
	}
	if (parcount)
		return (syntax_error(curr));
	return (0);
}

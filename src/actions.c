/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->argc)
	{
		free(data->args[i]);
		i++;
	}
	free(data->args);
	data->argc = 0;
}

void	handle_(__attribute__((unused))t_data *data,
				__attribute__((unused))t_token *t)
{
	return ;
}

void	handle_root(t_data *data, t_token *t)
{
	exect_tree(data, t->left);
}

int	convert(t_token_type type)
{
	int	j;

	j = 0;
	while ((int)type != 1 << j)
		j++;
	return (j);
}

void	exect_tree(t_data *data, t_token *root)
{
	int	type;

	if (!root || data->stop)
		return ;
	type = convert(root->type);
	(void (*[])(t_data *, t_token *)){
	handle_,
	handle_word,
	handle_and_if,
	handle_pipe,
	handle_or_if,
	handle_less,
	handle_dless,
	handle_great,
	handle_dgreat,
	handle_root,
	handle_root,
	handle_cmd,
	handle_root,
	}[type](data, root);
}

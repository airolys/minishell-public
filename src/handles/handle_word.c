/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@xxxxxx.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:14:47 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/09/27 16:14:47 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_args(t_data *data, char *new_arg)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (data->argc + 2));
	if (!tmp)
		return ;
	i = 0;
	tmp[0] = ft_strdup(new_arg);
	while (i < data->argc)
	{
		tmp[i + 1] = data->args[i];
		i++;
	}
	tmp[i + 1] = NULL;
	if (data->argc)
		free(data->args);
	data->args = tmp;
	data->argc++;
}

int	is_expandable(char *str)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' )
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		if ((!quote || quote == '\"') && str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

//remove quotes except when in quotes or behind a backslash
char	*quote_remove(char *str)
{
	int		i;
	int		offset;
	char	quote;

	i = 0;
	offset = 0;
	quote = '\0';
	while (str[i])
	{
		str[i + offset] = str[i];
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			offset--;
		}
		else if (quote && str[i] == quote)
		{
			quote = '\0';
			offset--;
		}
		i++;
	}
	str[i + offset] = '\0';
	return (str);
}

char	**param_expan(t_data *data, t_token *t)
{
	char	**splitted;
	char	*tmp;

	if (is_expandable(t->txt))
	{
		tmp = expand(t->txt, data);
		splitted = ft_split(tmp, ' ');
		free(tmp);
		if (!splitted)
			return (NULL);
	}
	else
	{
		tmp = ft_strdup(t->txt);
		if (!tmp)
			return (NULL);
		splitted = malloc(sizeof(char *) * 2);
		if (!splitted)
			return (free(tmp), NULL);
		splitted[0] = quote_remove(tmp);
		splitted[1] = NULL;
	}
	return (splitted);
}

void	handle_word(t_data *data, t_token *t)
{
	char	**splitted;
	char	*arg;
	int		i;

	exect_tree(data, t->left);
	if (t->txt[0] == '*')
		return (star(data));
	splitted = param_expan(data, t);
	if (!splitted)
		return ;
	i = ft_tabsize(splitted) - 1;
	while (i >= 0)
	{
		arg = splitted[i];
		if (!arg)
			return (clear_tab(splitted));
		add_to_args(data, arg);
		i--;
	}
	clear_tab(splitted);
}

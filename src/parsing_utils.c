/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:02:56 by acharra           #+#    #+#             */
/*   Updated: 2023/09/13 15:42:50 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_strcpy(void	*dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	*(char *)(dest + i) = '\0';
	return (dest);
}

t_token	*make_token(char *str, int len, int type)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	if (!out)
		return (NULL);
	out->txt = malloc(sizeof(char) * (len + 1));
	if (!out->txt)
		return (free(out), NULL);
	ft_strcpy(out->txt, str, len);
	out->type = type;
	out->next = NULL;
	out->left = NULL;
	out->right = NULL;
	return (out);
}

void	add_token_last(t_tokens *list, t_token *toadd)
{
	t_token	*tmp;

	if (!toadd)
		return ;
	if (list->amount == 0)
	{
		list->first = toadd;
		list->last = toadd;
	}
	else
	{
		tmp = list->last;
		tmp->next = toadd;
		if (toadd->next)
			toadd = toadd->next;
		list->last = toadd;
	}
	list->amount++;
}

t_tokens	*create_tokens(void)
{
	t_tokens	*out;

	out = malloc(sizeof(t_tokens));
	if (!out)
		return (NULL);
	out->first = NULL;
	out->last = NULL;
	out->amount = 0;
	return (out);
}

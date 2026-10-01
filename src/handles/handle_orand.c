/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_orand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:36:52 by acharra           #+#    #+#             */
/*   Updated: 2023/09/13 15:37:35 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_or_if(t_data *data, t_token *t)
{
	int	pid;

	exect_tree(data, t->left);
	while (1)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid < 0)
			break ;
	}
	if (!data->status)
		data->stop = 1;
	exect_tree(data, t->right);
	data->stop = 0;
}

void	handle_and_if(t_data *data, t_token *t)
{
	int	pid;

	exect_tree(data, t->left);
	while (1)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid < 0)
			break ;
	}
	if (data->status)
		data->stop = 1;
	exect_tree(data, t->right);
	data->stop = 0;
}

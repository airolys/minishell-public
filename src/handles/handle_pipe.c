/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:00:14 by acharra           #+#    #+#             */
/*   Updated: 2023/10/05 15:09:26 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lpipe_child(t_data *data, int fildes[2], t_token *t)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fildes[0]);
	dup2(fildes[1], STDOUT_FILENO);
	close(fildes[1]);
	exect_tree(data, t->left);
	free_for_all(data);
	exit(data->status);
}

void	rpipe_child(t_data *data, int fildes[2], t_token *t)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fildes[1]);
	dup2(fildes[0], STDIN_FILENO);
	close(fildes[0]);
	exect_tree(data, t->right);
	free_for_all(data);
	exit(data->status);
}

extern int	g_status;

void	handle_pipe(t_data *data, t_token *t)
{
	int	fildes[2];
	int	pid;
	int	pid2;

	if (pipe(fildes) == -1)
		return ;
	pid = fork();
	data->last_pid = pid;
	if (pid == 0)
		lpipe_child(data, fildes, t);
	pid2 = fork();
	data->last_pid = pid2;
	if (pid2 == 0)
		rpipe_child(data, fildes, t);
	close(fildes[1]);
	close(fildes[0]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else
		data->status = g_status;
}

/*
void	handle_pipe(t_data *data, t_token *t)
{
	int	fildes[2];
	int	pid;

	if (pipe(fildes) == -1)
		return ;
	pid = fork();
	data->last_pid = pid;
	if (pid == 0)
	{
		close(fildes[0]);
		dup2(fildes[1], STDOUT_FILENO);
		close(fildes[1]);
		exect_tree(data, t->left);
		free_for_all(data);
		exit(data->status);
	}
	pid = fork();
	data->last_pid = pid;
	if (pid == 0)
	{
		close(fildes[1]);
		dup2(fildes[0], STDIN_FILENO);
		close(fildes[0]);
		exect_tree(data, t->right);
		free_for_all(data);
		exit(data->status);
	}
	close(fildes[1]);
	close(fildes[0]);
}
*/
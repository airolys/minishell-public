/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_less.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:52:39 by acharra           #+#    #+#             */
/*   Updated: 2023/09/27 16:26:07 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_less(t_data *data, t_token *t)
{
	int	saved_stdin;
	int	input_fd;

	saved_stdin = dup(STDIN_FILENO);
	exect_tree(data, t->right);
	if (data->argc != 1)
	{
		printf("minishell: %s: ambiguous redirect\n", t->right->txt);
		free_args(data);
		return ;
	}
	input_fd = open(data->args[0], O_RDONLY);
	free_args(data);
	if (input_fd == -1)
	{
		printf("minishell: %s: error opening file\n", t->right->txt);
		return ;
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	exect_tree(data, t->left);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	handle_dless(t_data *data, t_token *t)
{
	int		fd[2];
	char	*line;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	line = expand(t->right->txt, data);
	if (pipe(fd) || !line)
	{
		free_for_all(data);
		if (line)
			free(line);
		return ;
	}
	write(fd[1], line, ft_strlen(line));
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exect_tree(data, t->left);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	handle_great(t_data *data, t_token *t)
{
	int	saved_stdout;
	int	output_fd;

	saved_stdout = dup(STDOUT_FILENO);
	exect_tree(data, t->right);
	if (data->argc != 1)
	{
		printf("minishell: %s: ambiguous redirect\n", t->right->txt);
		free_args(data);
		return ;
	}
	output_fd = open(data->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free_args(data);
	if (output_fd == -1)
	{
		printf("minishell: %s: error opening file\n", t->right->txt);
		return ;
	}
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	exect_tree(data, t->left);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

void	handle_dgreat(t_data *data, t_token *t)
{
	int	saved_stdout;
	int	output_fd;

	saved_stdout = dup(STDOUT_FILENO);
	exect_tree(data, t->right);
	if (data->argc != 1)
	{
		printf("minishell: %s: ambiguous redirect\n", t->right->txt);
		free_args(data);
		return ;
	}
	output_fd = open(data->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	free_args(data);
	if (output_fd == -1)
	{
		printf("minishell: %s: error opening file\n", t->right->txt);
		return ;
	}
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	exect_tree(data, t->left);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

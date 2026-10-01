/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(t_data *data)
{
	if (data->status == 0)
		data->user_input = readline("minishell "GREEN"$"END" ");
	else
		data->user_input = readline("minishell "RED"$"END" ");
	if (!data->user_input)
		return (write(2, "exit\n", 5), 1);
	if (!ft_strlen(data->user_input))
		return (free(data->user_input), 2);
	add_history(data->user_input);
	return (0);
}

void	wait_the_crowd(void)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid < 0)
			break ;
	}
	signal(SIGINT, &sig_handler);
}

void	free_for_all(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	if (data->tree)
		free_tree(data->tree);
	if (data->tokens)
		free(data->tokens);
	if (data->argc)
		free_args(data);
	clear_tab(data->env);
}

int	shell_routine(t_data *data)
{
	int	status;

	if (tcsetattr(0, TCSANOW, data->term))
		return (1);
	data->stop = 0;
	status = get_input(data);
	if (status == 1)
		return (clear_tab(data->env), 1);
	if (status == 2 || parse_input(data))
		return (0);
	build_tree(data);
	exect_tree(data, data->tree);
	wait_the_crowd();
	free_tree(data->tree);
	data->tree = NULL;
	free(data->user_input);
	data->user_input = NULL;
	free(data->tokens);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data			data[1];
	struct termios	test;

	data->term = &test;
	(void)ac;
	(void)av;
	if (init_data(data, env))
		return (1);
	start_signals(UNFORK);
	while (1)
		if (shell_routine(data))
			break ;
	return (0);
}

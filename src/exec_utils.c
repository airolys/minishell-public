/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_data *data, char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(data), 1);
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(data), 1);
	if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd(data), 1);
	if (!ft_strcmp(cmd, "export"))
		return (ft_export(data), 1);
	if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(data), 1);
	if (!ft_strcmp(cmd, "env"))
		return (ft_env(data), 1);
	if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(data), 1);
	return (0);
}

int	g_status;

void	handlerfork(int signum)
{
	g_status = 128 + signum;
	if (signum == SIGQUIT)
		write(STDOUT_FILENO, "Quit", 5);
	write(STDOUT_FILENO, "\n", 1);
}

void	exec_child(t_data *data, char *path)
{
	char	*tmp;

	shell_level(data, 1);
	data->status = 127;
	tmp = "command not found";
	if (access(path, X_OK) == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(path, data->args, data->env);
		data->status = 126;
		tmp = strerror(errno);
	}
	printf("minishell: %s: %s\n", data->args[0], tmp);
	free_for_all(data);
	exit(data->status);
}

void	exec(t_data *data, char *path)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exec_child(data, path);
	else if (pid == -1)
		return ;
	start_signals(FORK);
	waitpid(pid, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else
		data->status = g_status;
	data->last_pid = pid;
	start_signals(UNFORK);
}

int	ft_strnchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

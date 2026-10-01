/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

static void	read_input(int *fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
		{
			write(fd[1], "\0", 1);
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

static char	*retrieve_input(int *fd)
{
	char	input[BUFSIZ];
	char	*out;
	char	*tmp;
	int		nbr;

	out = NULL;
	nbr = read(fd[0], input, BUFSIZ);
	while (nbr)
	{
		input[nbr] = '\0';
		tmp = ft_strjoin(out, input);
		if (out)
			free(out);
		out = tmp;
		nbr = read(fd[0], input, BUFSIZ);
	}
	return (out);
}

static char	*get_heredoc_input(t_data *data, char *delimiter)
{
	int		fd[2];
	int		pid;
	char	*out;

	if (pipe(fd))
		exit(-1);
	pid = fork();
	if (pid == 0 && !close(fd[0]))
	{
		free_list(data->tokens->first);
		free_for_all(data);
		signal(SIGINT, &handle_ctrcinread);
		read_input(fd, delimiter);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	stop_signals();
	out = retrieve_input(fd);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (out);
}

t_token	*get_heredoc(t_data *data, char *str, int *len)
{
	char	delimiter[NAME_MAX];
	char	*txt;
	int		i;
	t_token	*out;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	*len += i + 1;
	str += i;
	out = tokenize_word(str, len);
	add_token_last(data->tokens, out);
	quote_remove(out->txt);
	ft_strlcpy(delimiter, out->txt, NAME_MAX);
	txt = get_heredoc_input(data, delimiter);
	free(out->txt);
	out->txt = txt;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:10:25 by acharra           #+#    #+#             */
/*   Updated: 2023/10/02 18:23:37 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_path(char *envpath, char *name, int *offset)
{
	char	*path;
	char	*tmp;
	int		len;
	int		namelen;

	path = envpath + *offset;
	len = ft_strnchr(path, ':');
	namelen = ft_strlen(name);
	if (len == -1 || namelen == 0)
		return (NULL);
	tmp = malloc(sizeof(char) * (len + namelen + 2));
	if (!tmp)
		return (NULL);
	ft_strcpy(tmp, path, len);
	tmp[len] = '/';
	ft_strcpy(tmp + len + 1, name, namelen);
	*offset += len;
	if (path[len])
		*offset += 1;
	return (tmp);
}

char	*search_name(t_data *data, char *name)
{
	char	*envpath;
	char	*currpath;
	int		i;

	(void)data;
	envpath = get_value(data, "PATH");
	if (!envpath)
		envpath = ft_strdup("");
	if (!envpath)
		return (NULL);
	i = 0;
	currpath = split_path(envpath, name, &i);
	while (currpath)
	{
		if (access(currpath, F_OK) == 0)
			return (free(envpath), currpath);
		if (currpath)
			free(currpath);
		currpath = split_path(envpath, name, &i);
	}
	free(envpath);
	return (name);
}

void	handle_cmd(t_data *data, t_token *t)
{
	char	*tmp;

	exect_tree(data, t->left);
	if (!data->argc)
		return ;
	tmp = search_name(data, data->args[0]);
	if (!exec_builtin(data, data->args[0]) && tmp)
		exec(data, tmp);
	if (tmp && tmp != data->args[0])
		free(tmp);
	free_args(data);
}

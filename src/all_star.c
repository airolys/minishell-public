/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	isvalid(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '.')
	{
		if (!str[1])
			return (0);
		if (str[1] == str[0])
			return (0);
	}
	return (1);
}

void	star(t_data *data)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	char			*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	pdir = opendir(cwd);
	free(cwd);
	pdirent = readdir(pdir);
	while (pdirent)
	{
		if (isvalid(pdirent->d_name))
			add_to_args(data, pdirent->d_name);
		pdirent = readdir(pdir);
	}
	closedir(pdir);
}

/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(t_data *data, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && is_keychar(s[i]))
		i++;
	if (i >= XATTR_NAME_MAX)
	{
		builtin_error(data, "minishell: export: key too long\n");
		return (1);
	}
	j = 0;
	while (s[i + j])
		j++;
	if (j >= XATTR_SIZE_MAX)
	{
		builtin_error(data, "minishell: export: value too long\n");
		return (2);
	}
	return (0);
}

void	print_env(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("export %s\n", tab[i]);
		i++;
	}
}

void	ft_export(t_data *data)
{
	if (data->argc == 1)
	{
		print_env(data->env);
		data->status = 0;
		return ;
	}
	if (data->argc != 2)
		return (builtin_error(data, "minishell: export: one arg required\n"));
	if (check_key(data, data->args[1]))
		return ;
	if (add_env(data, data->args[1]))
		return (builtin_error(data, "erreur export\n"));
	data->status = 0;
}

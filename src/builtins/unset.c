/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	rm_env(t_data *data, char *key)
{
	int		i;
	int		j;
	int		found;

	found = -1;
	i = 0;
	while (data->env[i])
	{
		if (compare_key(key, data->env[i]))
			found = i;
		i++;
	}
	if (found == -1)
		return (1);
	free(data->env[found]);
	j = 0;
	while (j < i)
	{
		if (j >= found)
			data->env[j] = data->env[j + 1];
		j++;
	}
	return (0);
}

void	ft_unset(t_data *data)
{
	if (rm_env(data, data->args[1]))
		return (builtin_error(data, "erreur unset\n"));
	data->status = 0;
}

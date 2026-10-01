/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (get_env(data, data->env[i]))
			printf("%s\n", data->env[i]);
		i++;
	}
	data->status = 0;
}

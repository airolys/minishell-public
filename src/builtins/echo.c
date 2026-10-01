/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data)
{
	int	i;
	int	nonl;

	i = 1;
	nonl = 0;
	if (data->argc > 1 && !ft_strcmp(data->args[i], "-n"))
		nonl = i++;
	while (i < data->argc)
	{
		printf("%s", data->args[i]);
		i++;
		if (i < data->argc)
			printf(" ");
	}
	if (!nonl)
		printf("\n");
	data->status = 0;
}

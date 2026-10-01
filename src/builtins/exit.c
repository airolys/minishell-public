/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *str)
{
	int	i;

	i = 0;
	while (*str)
		i = i * 10 + *str++ - '0';
	return (i);
}

void	ft_exit(t_data *data)
{
	unsigned int	status;

	if (data->argc > 1)
		status = (unsigned int)ft_atoi(data->args[1]) % 255;
	else
		status = data->status;
	printf("exit %d\n", status);
	free_for_all(data);
	exit(status);
}

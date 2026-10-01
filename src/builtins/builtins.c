/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_error(t_data *data, char *error)
{
	data->status = 1;
	write(STDERR_FILENO, error, ft_strlen(error));
}

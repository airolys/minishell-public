/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (builtin_error(data,
				"minishell: pwd: No such file or directory\n"));
	printf("%s\n", tmp);
	free(tmp);
	data->status = 0;
}

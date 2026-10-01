/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data)
{
	char	tmp[PATH_MAX];

	if (data->argc > 2)
		return (builtin_error(data, "minishell: cd: too many arguments\n"));
	if (data->argc == 1)
	{
		if (chdir(get_env(data, "HOME")))
			return (builtin_error(data, "minishell: HOME not set\n"));
	}
	else if (chdir(data->args[1]))
		return (builtin_error(data,
				"minishell: cd: No such file or directory\n"));
	data->status = 0;
	ft_strlcpy(tmp, "PWD=", 5);
	getcwd(tmp + 4, PATH_MAX - 4);
	add_env(data, tmp);
}

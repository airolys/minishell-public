/* ************************************************************************** */
/**//**//*   *//**//*   By: *//**//*   Created:   by *//*   Updated:   by *//**/
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_token *tmp)
{
	t_token	*next;

	while (tmp)
	{
		next = tmp->next;
		free(tmp->txt);
		free(tmp);
		tmp = next;
	}
}

char	**minimal_env(void)
{
	char	**env;
	char	*tmp;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("OLDPWD");
	if (!env[0])
		return (clear_tab(env), NULL);
	tmp = getcwd(NULL, 0);
	env[1] = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!env[1])
		return (clear_tab(env), NULL);
	env[2] = ft_strdup("SHLVL=0");
	if (!env[2])
		return (clear_tab(env), NULL);
	env[3] = ft_strdup("_=/usr/bin/env");
	if (!env[3])
		return (clear_tab(env), NULL);
	env[4] = NULL;
	return (env);
}

int	shell_level(t_data *data, int offset)
{
	char	*shlvl;
	char	*tmp;

	shlvl = NULL;
	shlvl = ft_itoa(ft_atoi(get_env(data, "SHLVL")) + offset);
	if (!shlvl)
		return (1);
	tmp = ft_strjoin("SHLVL=", shlvl);
	if (!tmp || add_env(data, tmp))
		return (free(shlvl), 1);
	free(shlvl);
	free(tmp);
	return (0);
}

int	init_env(t_data *data, char **env)
{
	data->env = NULL;
	if (!env[0])
		data->env = minimal_env();
	if (!data->env)
		data->env = dup_tab(env, NULL);
	if (!data->env)
		return (1);
	return (0);
}

int	init_data(t_data *data, char **env)
{
	data->status = 0;
	data->argc = 0;
	data->stop = 0;
	data->tokens = NULL;
	data->tree = NULL;
	data->args = NULL;
	data->user_input = NULL;
	if (init_env(data, env))
		return (1);
	if (tcgetattr(0, data->term))
		return (1);
	return (0);
}

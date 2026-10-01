/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	compare_key(char *key, char *line)
{
	int	i;

	i = 0;
	if (!key || !key[i] || !line)
		return (0);
	while (key[i] && line[i] && key[i] == line[i])
	{
		if (key[i] == '=')
			return (1);
		i++;
	}
	if (!is_keychar(key[i]) && (line[i] && line[i] == '='))
		return (1);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (i < n && s1[i] && s2[i])
	{
		if (s2[i] != s1[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

// returns a copy of the env var
char	*get_value(t_data *data, char *key)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = ft_strlen(key);
	if (key[0] == '?')
		return (ft_itoa(data->status));
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], key, k) && data->env[i][k] == '=')
		{
			if (data->env[i][k + 1] == '\"')
				tmp = ft_strdup(data->env[i] + k + 2);
			else
				tmp = ft_strdup(data->env[i] + k + 1);
			if (!tmp)
				return (NULL);
			if (tmp[ft_strlen(tmp) - 1] == '\"')
				tmp[ft_strlen(tmp) - 1] = '\0';
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

//returns a pointer to the value of the env var
char	*get_env(t_data *data, char *key)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (compare_key(key, data->env[i]))
			return (ft_strchr(data->env[i], '='));
		i++;
	}
	return (NULL);
}

int	add_env(t_data *data, char *line)
{
	int		i;
	char	**tmp;

	i = 0;
	while (data->env[i])
	{
		if (compare_key(line, data->env[i]))
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(line);
			if (!data->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	tmp = dup_tab(data->env, line);
	if (!tmp)
		return (1);
	clear_tab(data->env);
	data->env = tmp;
	return (0);
}

/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_key(char *value)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (value[++i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			len++;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (free(value), NULL);
	str[len] = '\0';
	while (i >= 0)
	{
		str[len--] = value[i];
		if (value[i] == '\'' && value[i] == '\"')
			str[len--] = '\\';
		i--;
	}
	free(value);
	return (str);
}

int	copy_key(t_data *data, char *key, char *expanded, int *expanded_len)
{
	int		value_len;
	char	*env_val;

	if (key[0] == '?')
		env_val = ft_itoa(data->status);
	else
		env_val = ft_strdup(get_env(data, key));
	if (!env_val)
		env_val = ft_strdup("");
	value_len = ft_strlen(env_val);
	if (*expanded_len + value_len > ARG_MAX)
		return (0);
	ft_strcpy(&expanded[*expanded_len], env_val, value_len);
	*expanded_len += value_len;
	free(env_val);
	return (1);
}

int	add_value(t_data *data, char *src, char *expanded, int *expanded_len)
{
	int	keylen;

	keylen = 1;
	while (src[keylen] && is_keychar(src[keylen]))
		keylen++;
	if (copy_key(data, src + 1, expanded, expanded_len))
		return (keylen);
	return (-1);
}

int	do_expand(t_data *data, char *src, char *exp, int exp_len)
{
	int		i;
	int		j;
	char	quote;

	quote = -1;
	i = 0;
	while (src[i])
	{
		if (src[i] == quote && ++i)
			quote = -1;
		else if (quote == -1 && (src[i] == '\'' || src[i] == '\"'))
			quote = src[i++];
		else if ((quote != '\'') && src[i] == '$')
		{
			j = add_value(data, src + i, exp, &exp_len);
			if (j == -1)
				return (free(exp), 1);
			i += j;
		}
		else
			exp[exp_len++] = src[i++];
		if (exp_len > ARG_MAX)
			return (free(exp), 1);
	}
	return (0);
}

char	*expand(char *src, t_data *data)
{
	char	*expanded;
	int		expanded_len;

	if (!src || !src[0])
		return (ft_strdup(""));
	expanded_len = 0;
	expanded = (char *)malloc(ARG_MAX + 1);
	while (expanded_len <= ARG_MAX)
		expanded[expanded_len++] = '\0';
	expanded_len = 0;
	if (!expanded)
		return (NULL);
	if (do_expand(data, src, expanded, expanded_len))
		return (NULL);
	return (expanded);
}

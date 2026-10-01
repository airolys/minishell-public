/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = 0;
	return (new);
}

void	clear_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

//dup a tab and if not NULL add the second arg at the end
char	**dup_tab(char **tab, char *add)
{
	int		i;
	char	**new;

	i = 0;
	if (!add)
		new = malloc(sizeof(char *) * (ft_tabsize(tab) + 1));
	else
		new = malloc(sizeof(char *) * (ft_tabsize(tab) + 2));
	if (!new)
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (clear_tab(new), NULL);
		i++;
	}
	if (add)
		new[i++] = ft_strdup(add);
	new[i] = NULL;
	return (new);
}

int	is_keychar(char c)
{
	if (!c)
		return (0);
	if ('0' <= c && c <= '9')
		return (1);
	if ('A' <= c && c <= 'Z')
		return (1);
	if ('a' <= c && c <= 'z')
		return (1);
	if (c == '?')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

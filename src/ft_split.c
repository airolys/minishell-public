/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wc(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_free_split(char **l, int max)
{
	int	i;

	i = 0;
	while (i <= max)
	{
		free(l[i]);
		l[i] = NULL;
		i++;
	}
	free(l);
	l = NULL;
	return (NULL);
}

static char	*createword(char const *src, char c)
{
	int		len;
	char	*dst;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, len + 1);
	return (dst);
}

static char	**fill_tab(char **l, char const *s, char c, int wc)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] && j < wc)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c)
		{
			l[j] = createword(s + i, c);
			len = ft_strlen(l[j]);
			if (!len)
			{
				ft_free_split(l, j);
				return (NULL);
			}
			j++;
			i += len;
		}
	}
	l[j] = NULL;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	**l;

	if (!s)
		return (NULL);
	wc = ft_wc(s, c);
	l = malloc(sizeof(char *) * (wc + 2));
	if (!l)
		return (NULL);
	if (!wc)
	{
		l[0] = ft_strdup("");
		if (!l[0])
			return (free(l), NULL);
		l[1] = NULL;
		return (l);
	}
	return (fill_tab(l, s, c, wc));
}

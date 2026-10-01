/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

static int	nbr_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static unsigned int	uabs(int n)
{
	if (n < 0)
		return ((unsigned int)(-n));
	return ((unsigned int)n);
}

static void	reverse(char *s, int len)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < len)
	{
		tmp = s[i];
		s[i] = s[len];
		s[len] = tmp;
		i++;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	un;
	int				i;

	s = (char *)malloc((nbr_len(n) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	un = uabs(n);
	s[0] = '\0';
	i = 1;
	while (un)
	{
		s[i] = un % 10 + '0';
		un /= 10;
		i++;
	}
	if (!n)
		s[i++] = '0';
	if (n < 0)
		s[i++] = '-';
	reverse(s, i - 1);
	return (s);
}

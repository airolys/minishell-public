/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_ope(t_data *data, char *str, int *len)
{
	int		type;

	type = 0;
	if (*str == '|')
		type = PIPE;
	if (*(str) == '&')
		type = WORD;
	if (*str == '<')
		type = LESS;
	if (*str == '>')
		type = GREAT;
	if (*str == *(str + 1))
	{
		*len += 1;
		type <<= 1;
		if (type == DLESS)
		{
			add_token_last(data->tokens, make_token(str, 2, type));
			return (get_heredoc(data, str + 2, len));
		}
		return (make_token(str, 2, type));
	}
	return (make_token(str, 1, type));
}

t_token	*tokenize_word(char *str, int *len)
{
	int	i;
	int	type;
	int	in_quote;

	in_quote = -1;
	type = WORD;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == -1 && (!i || str[i - 1] != '\\'))
				in_quote = str[i];
			else if (in_quote == str[i] && (str[i - 1] != '\\'))
				in_quote = -1;
		}
		if (in_quote == -1 && (str[i] == '|' || str[i] == '&'
				|| str[i] == '<' || str[i] == '>' || ft_isspace(str[i])
				|| str[i] == '(' || str[i] == ')'))
			break ;
		i++;
	}
	return (*len += i - 1, make_token(str, i, type));
}

t_token	*tokenize_parent(char *str)
{
	int	type;

	type = LPARENT;
	if (*str == ')')
		type = RPARENT;
	return (make_token(str, 1, type));
}

t_tokens	*tokenize_input(t_data *data, char *str)
{
	t_tokens	*out;
	int			i;
	int			j;

	out = create_tokens();
	data->tokens = out;
	if (!out)
		return (NULL);
	i = 0;
	while (*(str + i) && *(str + i) != '#')
	{
		j = 1;
		if (*(str + i) == '|' || *(str + i) == '&'
			|| *(str + i) == '<' || *(str + i) == '>')
			add_token_last(out, tokenize_ope(data, str + i, &j));
		else if (*(str + i) == '(' || *(str + i) == ')')
			add_token_last(out, tokenize_parent(str + i));
		else if (*(str + i) && !isspace(str[i]))
			add_token_last(out, tokenize_word(str + i, &j));
		i += j;
	}
	return (out);
}

int	parse_input(t_data *data)
{
	char		*str;
	t_tokens	*t;

	str = data->user_input;
	t = tokenize_input(data, str);
	if (!t || syntax_check(t))
		return (data->status = 2, 1);
	data->tokens = t;
	return (0);
}

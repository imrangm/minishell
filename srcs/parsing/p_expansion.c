/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:58:49 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/15 18:55:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_exp(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strchr(str, '$'))
		return (0);
	tmp = ft_strchr(str, '$');
	while (tmp[i])
	{
		if (tmp[i] == '$' || tmp[i] == '?' || ft_isquote(tmp[i]))
			break ;
		if (tmp[i] != '_' && !ft_isalnum(tmp[i]))
			return (0);
		i++;
	}
	if (tmp[i + 1] && (ft_isspace(tmp[i + 1]) || ft_isquote(tmp[i + 1])))
		return (0);
	return (1);
}

static int	start_param(char *value)
{
	char	*tmp;
	int		start;

	tmp = ft_strchr(value, '$');
	start = ft_strlen(value) - ft_strlen(tmp);
	return (start);
}

static int	end_param(char *value)
{
	int	i;

	i = 0;
	if (value[1] && value[1] == '?')
		return (2);
	while (value[i++])
	{
		if (i == (int) ft_strlen(value))
			break ;
		if (value[i] == '\"' || value[i] == '\'' || value[i] == '?'
			|| ft_isspace(value[i]) || value[i] == '$')
			break ;
	}
	return (i);
}

static t_exp	*find_exp(char *value)
{
	t_exp	*exp;
	char	*tmp;

	exp = malloc(sizeof(t_exp));
	ft_memset(exp, 0, sizeof(exp));
	exp->start = start_param(value);
	tmp = ft_substr(value, exp->start,
			ft_strlen(value) - exp->start);
	exp->end = end_param(tmp) + exp->start - 1;
	ft_free(tmp);
	exp->param = ft_substr(value, exp->start + 1,
			exp->end - exp->start);
	return (exp);
}

void	expansion(t_token *token, t_data *data)
{
	t_exp	*expansion;
	int		i;
	int		count;

	i = 1;
	count = count_tokens(token);
	while (token)
	{
		if (token->type == WORD || token->type == DQUOTE)
		{
			while (check_exp(token->value))
			{
				expansion = find_exp(token->value);
				if (i == count && expansion->end == expansion->start)
					break ;
				expander(token, expansion, data);
			}
		}
		token = token->next;
		i++;
	}
}

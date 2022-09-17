/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:58:49 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/17 09:51:57 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_exp(char *str)
{
	char	*tmp;

	if (!ft_strchr(str, '$'))
		return (0);
	tmp = ft_strchr(str, '$');
	if (tmp[1] && (ft_isspace(tmp[1]) || ft_isquote(tmp[1])
		|| ft_isdigit(tmp[1]) || tmp[1] == '(' || tmp[1] == '{'))
		return (0);
	return (1);
}

static int	start_param(char *str)
{
	char	*tmp;
	int		start;

	tmp = ft_strchr(str, '$');
	start = ft_strlen(str) - ft_strlen(tmp);
	return (start);
}

static int	end_param(char *str)
{
	int	i;

	i = 0;
	if (str[1] && str[1] == '?')
		return (2);
	while (str[i++])
	{
		if (i == (int) ft_strlen(str))
			break ;
		if (str[i] == '\"' || str[i] == '\'' || str[i] == '?'
			|| ft_isspace(str[i]) || str[i] == '$' || str[i] == '=')
			break ;
	}
	return (i);
}

static t_exp	*find_exp(char *str)
{
	t_exp	*exp;
	char	*tmp;

	exp = malloc(sizeof(t_exp));
	ft_memset(exp, 0, sizeof(exp));
	exp->start = start_param(str);
	tmp = ft_substr(str, exp->start,
			ft_strlen(str) - exp->start);
	exp->end = end_param(tmp) + exp->start - 1;
	ft_free(tmp);
	exp->param = ft_substr(str, exp->start + 1,
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:58:49 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/19 10:09:13 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	free_from_expansion(t_exp *expansion)
{
	ft_free(expansion->param);
	ft_free(expansion);
}

int	expansion(t_toklist *toks, t_token *token, t_data *data)
{
	t_exp	*expansion;
	int		i;

	i = 1;
	while (token)
	{
		if (token->type == WORD || token->type == DQUOTE)
		{
			while (check_exp(token->value))
			{
				expansion = find_exp(token->value);
				if (i == count_tokens(token)
					&& expansion->end == expansion->start)
				{
					free_from_expansion(expansion);
					break ;
				}
				if (expander(toks, token, expansion, data))
					return (1);
			}
		}
		token = token->next;
		i++;
	}
	return (0);
}

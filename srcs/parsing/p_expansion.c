/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:58:49 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 15:47:30 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	set_exp(t_token *token)
{
	if (token->type == REDIR)
		token->next->exp = 0;
}

int	end_exp(int i, t_exp *expansion, t_token *token)
{
	if (i == ctoks(token) && expansion->end == expansion->start)
	{
		free_expansion(expansion);
		return (1);
	}
	return (0);
}

int	expansion(t_toklist *toks, t_token *token, t_data *data)
{
	t_exp	*expansion;
	int		i;

	i = 1;
	while (token)
	{
		set_exp(token);
		if ((token->type == WORD || token->type == DQUOTE) && token->exp == 1)
		{
			while (check_exp(token->value))
			{
				expansion = find_exp(token->value);
				end_exp(i, expansion, token);
				if (expander(toks, token, expansion, data))
					return (1);
			}
		}
		token = token->next;
		i++;
	}
	return (0);
}

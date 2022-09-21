/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:26:07 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/21 14:29:16 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_param(char *str)
{
	char	*tmp;
	int		start;

	tmp = ft_strchr(str, '$');
	start = ft_strlen(str) - ft_strlen(tmp);
	return (start);
}

int	end_param(char *str)
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

void	free_expansion(t_exp *exp)
{
	ft_free(exp->param);
	ft_free(exp);
}

void	free_expansion_all(t_exp *exp)
{
	ft_free(exp->param);
	ft_free(exp->value);
	ft_free(exp);
}

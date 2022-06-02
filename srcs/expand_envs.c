/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:21:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/02 15:53:41 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_expand(char *str, int quote)
{
	(void) quote;
	return (str[1] == '(' || str[1] == ')' || str[1] == '`'
		|| ft_isalnum(str[1]));
}

void	set_quote(char *str, int i, int *q)
{
	if (str[i] == (*q))
		(*q) = 0;
	else if (!(*q) && is_quote(str[i]))
		(*q) = str[i];
}

char	*expand_envs(char *str, char **envp)
{
	int		i;
	int		q;
	int		start;
	int		end;
	char	*expanded_str;

	i = 0;
	q = 0;
	start = 0;
	end = 0;
	(void) envp;
	expanded_str = NULL;
	while (str[i])
	{
		if (str[i] == '$' && q != SQUOTE)
		{
			i++;
			start = i;
			while (str[i] && ft_isalnum(str[i]))
				i++;
			end = i;
			ft_substr(str, start, end - start);
		}
		set_quote(str, i, &q);
		i++;
	}
	return (expanded_str);
}

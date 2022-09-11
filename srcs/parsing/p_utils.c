/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/11 19:29:15 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * empty file to include addtl functions *//

int	check_io(char *prev, char *current)
{
	return ((prev[0] == GREAT && current[0] == LESS)
		|| (prev[0] == LESS && current[0] == GREAT));
}

int	check_error(t_node *node, t_data *data)
{
	if (node->type == 1)
	{
		check_error(node->left_node, data);
		check_error(node->right_node, data);
	}
	else if (node->type == 2)
	{
		ft_putstr_fd(node->value, 2);
		ft_putchar_fd('\n', 2);
		data->last_exit_status = 1;
		data->error = 1;
		return (1);
	}
	return (0);
}

int	check_expansion(char *str) //! Incomplete "'$_NAME?{}'"
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	// printf("Entered check_expansion\n");
	while (str[i])
	{
		if (ft_isquote(str[i]) && !q)
			q = str[i];
		else if (q == str[i])
			q = 0;
		else if (q != '\'')
		{
			if (ft_isquote(str[i]) || str[i] == '$')
				break ;
			if (str[i] != '_' && str[i] != '?' && !ft_isalnum(str[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	count_exp(char *value)
{
	int	i;
	int	e;
	int	q;

	i = 0;
	e = 0;
	q = 0;
	while (value[i])
	{
		if (ft_isquote(value[i]) && !q)
			q = value[i];
		else if (q == value[i])
			q = 0;
		else if (q != '\'' && value[i] == '$')
			e++;
		i++;
	}
	return (e);
}

int	next_exp(t_token **toks)
{
	int	i;

	i = 0;
	while (i < toks[0]->count)
	{
		if (toks[i]->expand)
		{
			toks[i]->expand--;
			break ;
		}
		i++;
	}
	return (i);
}
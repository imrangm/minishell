/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/10 18:16:23 by imustafa         ###   ########.fr       */
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

int	check_expansion(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] && str[i] != '$')
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?')
			i++;
		if (str[i] == '{' || str[i] == '(')
			return (0);
		if (ft_isspace(str[i]) || str[i] == '\"' || str[i] == '\'')
			break ;
	}
	return (1);
}

int	count_exp(char *value)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (value[i])
	{
		// printf("char : %c\n", value[i]);
		if (value[i] == '$')
		{
			e++;
			// printf("e: %d\n", e);
		}
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
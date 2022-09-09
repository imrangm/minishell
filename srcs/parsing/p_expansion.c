/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:17 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/09 17:00:19 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_expansions(char *line)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (line[i])
	{
		if (line[i] == '$')
			e++;
		i++;
	}
	return (e);
}

int	end_param(char *value)
{
	int	i;

	i = 1;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '\''
			|| ft_isspace(value[i]) || value[i] == '$')
			break ;
		i++;
	}
	return (i);
}

t_node	*set_location(char *rem, char *args)
{
	t_node	*loc;
	t_node	*start;
	t_node	*end;
	int		i;

	loc = malloc(sizeof(t_node));
	start = malloc(sizeof(t_node));
	end = malloc(sizeof(t_node));
	ft_memset(loc, 0, sizeof(t_node));
	ft_memset(start, 0, sizeof(t_node));
	ft_memset(end, 0, sizeof(t_node));
	loc->type = 1;
	loc->id = "LOCATION";
	start->value = ft_strchr(rem, '$');
	start->val = (int)(start->value - args);
	start->id = "START";
	i = end_param(start->value);
	end->val = start->val + i - 1;
	end->id = "END";
	loc->left_node = start;
	loc->right_node = end;
	return (loc);
}

t_node	*attach_exp(char *cmd, char *rem, char *value, int expansions)
{
	t_node	*params;
	t_node	*loc;
	int		start;
	int		end;

	params = malloc(sizeof(t_node));
	params->id = "PARAMATER";
	params->value = value;
	if (expansions > 1)
	{
		rem = ft_strnstr(rem, value, ft_strlen(rem));
		rem = ft_strchr(rem, '$');
		loc = set_location(rem, cmd);
		start = loc->left_node->val;
		end = loc->right_node->val;
		value = ft_substr(cmd, start + 1, end - start);
		params->type = 1;
		params->left_node = loc;
		params->right_node = attach_exp(cmd, rem, value, expansions - 1);
	}
	if (expansions == 1)
		params->type = 0;
	return (params);
}

t_node	*add_expansions(t_node *args)
{
	t_node	*loc;
	t_node	*param;
	char	*value;
	int		start;
	int		end;

	loc = set_location(args->value, args->value);
	start = loc->left_node->val;
	end = loc->right_node->val;
	value = ft_substr(args->value, start + 1, end - start);
	param = attach_exp(args->value, args->value, value,
			count_expansions(args->value));
	param->value = value;
	return (pair_node(loc, param, "EXPANSION"));
}

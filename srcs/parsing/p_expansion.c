/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:17 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/11 11:52:30 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_expansions(t_token **toks)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (i < toks[0]->count)
	{
		if (toks[i]->expand)
			e += toks[i]->expand;
		i++;
	}
	// printf("count: %d\n", e);
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

int	get_new_pos(char *value, int end)
{
	int	i;

	i = end;
	printf("value str: %s\n", value);
	while (value[i++])
	{
		printf("value : %c\n", value[i]);
		if (value[i] == '$')
			break ;
	}
	return (i);
}

t_node	*set_location(t_token *toks)
{
	t_node	*loc;
	t_node	*start;
	t_node	*end;
	char	*tmp;
	int		i;

	loc = malloc(sizeof(t_node));
	start = malloc(sizeof(t_node));
	end = malloc(sizeof(t_node));
	ft_memset(loc, 0, sizeof(t_node));
	ft_memset(start, 0, sizeof(t_node));
	ft_memset(end, 0, sizeof(t_node));
	loc->type = 1;
	loc->id = "LOCATION";
	if (!toks->move)
	{
		start->value = ft_strchr(toks->value, '$');
		toks->move = ft_strlen(toks->value) - ft_strlen(start->value);
		toks->pos += toks->move;
		if (!toks->move)
			toks->move = 1;
	}
	else
	{
		tmp = ft_substr(toks->value, toks->move,
				ft_strlen(toks->value) - toks->move);
		start->value = ft_strchr(tmp, '$');
		ft_free(tmp);
		toks->move = ft_strlen(toks->value) - ft_strlen(start->value);
		toks->pos += toks->move;
	}
	start->val = toks->pos;
	start->id = "START";
	i = end_param(start->value);
	end->val = start->val + i - 1;
	end->id = "END";
	loc->left_node = start;
	loc->right_node = end;
	return (loc);
}

t_node	*attach_exp(char *cmd, char *value, int expansions, t_token **toks)
{
	t_node	*params;
	t_node	*loc;
	int		start;
	int		end;
	int		i;

	params = malloc(sizeof(t_node));
	params->id = "PARAMATER";
	params->value = value;
	if (expansions > 1)
	{
		i = next_exp(toks);
		loc = set_location(toks[i]);
		start = loc->left_node->val;
		end = loc->right_node->val;
		value = ft_substr(cmd, start + 1, end - start);
		params->type = 1;
		params->left_node = loc;
		params->right_node = attach_exp(cmd, value, expansions - 1, toks);
	}
	if (expansions == 1)
		params->type = 0;
	return (params);
}

t_node	*add_expansions(t_node *args, t_token **toks)
{
	t_node	*loc;
	t_node	*param;
	char	*value;
	int		start;
	int		end;
	int		i;

	i = next_exp(toks);
	loc = set_location(toks[i]);
	start = loc->left_node->val;
	end = loc->right_node->val;
	value = ft_substr(args->value, start + 1, end - start);
	param = attach_exp(args->value, value, count_expansions(toks) + 1, toks);
	param->value = value;
	return (pair_node(loc, param, "EXPANSION"));
}

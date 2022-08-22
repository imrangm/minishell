/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/22 08:34:43 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*attach_expansion(t_node *args, char *value, int expansions)
{
	//after param value look for another dollar sign
	//save param value to its node and recurse through function 
	//with one less expansions. In last expansion, return param 
	// with type 0
	t_node	*params;
	t_node	*start;
	t_node	*end;
	t_node	*loc;
	char	*rem;
	int		len;
	int		i;
	
	params = malloc(sizeof(t_node));
	if (expansions > 1)
	{
		// printf("looping expansions\n");
		params->value = ft_strdup(value);
		start = malloc(sizeof(t_node));
		end = malloc(sizeof(t_node));
		loc = malloc(sizeof(t_node));
		loc->type = 1;
		loc->id = ft_strdup("LOCATION");
		len = ft_strlen(args->value);
		rem = ft_strnstr(args->value, value, len);
		start->id = ft_strdup("START");
		start->value = ft_strchr(rem, '$');
		start->val = (int)(start->value - args->value);
		printf("start val: %d\n", start->val);
		i = 1;
		while (ft_isalnum(start->value[i++])
			&& start->value[i]
			&& start->value[i] != '\"'
			&& !ft_isspace(start->value[i]));
		printf("i : %d\n", i);
		end->val = start->val + i - 1;
		end->id = ft_strdup("END");
		value = ft_substr(args->value, start->val + 1, i - 1);
		loc->left_node = start;
		loc->right_node = end;
		printf("str id: %s, val: %d end id: %s val: %d\n",
			start->id, start->val, end->id, end->val);
		params->type = 1;
		params->id = ft_strdup("PARAMATER");
		params->left_node = loc;
		params->right_node = malloc(sizeof(t_node));
		params->right_node = attach_expansion(args, value, expansions - 1);
	}
	if (expansions == 1)
	{
		params->type = 0;
		params->value = ft_strdup(value);
		params->id = ft_strdup("PARAMATER");
	}
	printf("X\n");
	return (params);
}
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

t_node	*add_expansions(t_node *args)
{
	t_node	*loc;
	t_node	*start;
	t_node	*end;
	t_node	*param;
	char	*value;
	int		i;
	int 	expansions;

	expansions = count_expansions(args->value);
	loc = malloc(sizeof(t_node));
	param = malloc(sizeof(t_node));
	start = malloc(sizeof(t_node));
	end = malloc(sizeof(t_node));
	loc->type = 1;
	loc->id = ft_strdup("LOCATION");
	start->value = ft_strchr(args->value, '$');
	start->val = (int)(start->value - args->value);
	start->id = ft_strdup("START");
	i = 1;
	while (ft_isalnum(start->value[i++])
		&& start->value[i]
		&& start->value[i] != '\"'
		&& !ft_isspace(start->value[i]));
	// printf("i : %d\n", i);
	end->val = start->val + i - 1;
	end->id = ft_strdup("END");
	value = ft_substr(args->value, start->val + 1, i - 1);
	loc->left_node = start;
	loc->right_node = end;
	param = attach_expansion(args, value, expansions);
	param->value = value;
	return (pair_node(loc, param, "EXPANSION"));
}

void	process_redirection(char *left, char *right)
{
	if (ft_strncmp(left, ">>", 2) == 0)
		empty_file(right);
	if (ft_strncmp(left, ">", 1) == 0)
		empty_file(right);
	if (ft_strncmp(left, "<<", 2) == 0)
		read_line(right);
	// if (ft_strncmp(left, "<", 1) == 0)
	// 	printf("check if file exists");
}
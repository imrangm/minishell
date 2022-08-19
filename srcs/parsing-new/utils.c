/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:47:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/19 17:24:59 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*add_expansion(t_node *args)
{
	t_node	*loc;
	t_node	*start;
	t_node	*end;
	t_node	*param;
	int		i;

	loc = malloc(sizeof(t_node));
	param = malloc(sizeof(t_node));
	start = malloc(sizeof(t_node));
	end = malloc(sizeof(t_node));
	loc->type = 1;
	loc->id = "LOCATION";
	start->value = ft_strchr(args->value, '$');
	start->val = (int) (start->value - args->value);
	start->id = "START";
	i = 1;
	while (ft_isalnum(start->value[i++])
		&& start->value[i]
		&& start->value[i] != '\"'
		&& start->value[i] != '*'); //random char
	// printf("i : %d\n", i);
	end->val = start->val + i - 1;
	end->id = "END";
	param->value = ft_substr(args->value, start->val + 1, i - 1);
	param->type = 0;
	param->id = "PARAMATER";
	loc->left_node = start;
	loc->right_node = end;
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
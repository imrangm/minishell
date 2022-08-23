/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:17 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/23 08:34:10 by imustafa         ###   ########.fr       */
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

t_node	*attach_expansion(t_node *args, char *value, int expansions)
{
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
		// printf("i : %d\n", i);
		end->val = start->val + i - 1;
		end->id = ft_strdup("END");
		value = ft_substr(args->value, start->val + 1, i - 1);
		loc->left_node = start;
		loc->right_node = end;
		// printf("str id: %s, val: %d end id: %s val: %d\n",
		// 	start->id, start->val, end->id, end->val);
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
	return (params);
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

void	expander(t_node	*cmd, t_data *data)
{
	t_node		*current;
	char		*param;
	char		*final;
	int			start;
	int			end;
	int			len;
	size_t		i;
	size_t		j;

	current = cmd->right_node;
	param = NULL;
	while (current && current->type == 1)
	{
		start = current->left_node->left_node->val;
		end = current->left_node->right_node->val;
		if (param)
		{
			start += (ft_strlen(param) - ft_strlen(current->value) - 1);
			end += (ft_strlen(param) - ft_strlen(current->value) - 1);
		}
		if (ft_strncmp(current->right_node->value, "?", 1) == 0)
			param = ft_itoa(data->last_exit_status);
		else
			param = get_env_value(current->right_node->value, data);
		len = ft_strlen(param) + ft_strlen(cmd->left_node->value) - (end - start);
		printf("values start:%d, end:%d, len:%d\n", start, end, len);
		printf("param: %s\n", param);
		final = malloc(sizeof(char) * len);
		i = 0;
		while (i < (size_t) start)
		{
			final[i] = cmd->left_node->value[i];
			i++;
		}
		j = 0;
		while (j < ft_strlen(param))
		{
			final[i] = param[j];
			i++;
			j++;
		}
		j = end + 1;
		while (j < ft_strlen(cmd->left_node->value))
		{
			final[i] = cmd->left_node->value[j];
			i++;
			j++;
		}
		final[i] = '\0';
		// printf("final: %s\n", final);
		// ft_free(cmd->left_node->value);
		cmd->left_node->value = ft_strdup(final);
		cmd->left_node->id = ft_strdup("FINAL");
		current = current->right_node;
	}
}

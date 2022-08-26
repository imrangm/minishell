/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:17 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/26 19:24:46 by imustafa         ###   ########.fr       */
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

t_node	*set_location(char *rem, char *args)
{
	t_node	*loc;
	t_node	*start;
	t_node	*end;
	int		i;

	loc = malloc(sizeof(t_node));
	start = malloc(sizeof(t_node));
	end = malloc(sizeof(t_node));
	loc->type = 1;
	loc->id = ft_strdup("LOCATION");
	start->value = ft_strchr(rem, '$');
	start->val = (int)(start->value - args);
	start->id = ft_strdup("START");
	i = 1;
	while (ft_isalnum(start->value[i++]) && start->value[i]
		&& start->value[i] != '\"' && !ft_isspace(start->value[i]));
	end->val = start->val + i - 1;
	end->id = ft_strdup("END");
	loc->left_node = start;
	loc->right_node = end;
	return (loc);
}

t_node	*attach_expansion(char *cmd, char *rem, char *value, int expansions)
{
	t_node	*params;
	t_node	*loc;
	int		start;
	int		end;

	params = malloc(sizeof(t_node));
	if (expansions > 1)
	{
		params->value = ft_strdup(value);
		rem = ft_strnstr(rem, value, ft_strlen(rem));
		rem = ft_strchr(rem, '$');
		loc = set_location(rem, cmd);
		start = loc->left_node->val;
		end = loc->right_node->val;
		value = ft_substr(cmd, start + 1, end - start);
		params->type = 1;
		params->id = ft_strdup("PARAMATER");
		params->left_node = loc;
		params->right_node = malloc(sizeof(t_node));
		params->right_node = attach_expansion(cmd, rem, value, expansions - 1);
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
	t_node	*param;
	char	*value;
	int		start;
	int		end;

	loc = set_location(args->value, args->value);
	start = loc->left_node->val;
	end = loc->right_node->val;
	value = ft_substr(args->value, start + 1, end - start);
	param = attach_expansion(args->value, args->value, value,
			count_expansions(args->value));
	param->value = value;
	return (pair_node(loc, param, "EXPANSION"));
}

void	expander(t_node	*cmd, t_data *data)
{
	t_node		*current;
	char		*param;
	int			count;

	current = cmd->right_node;
	param = NULL;
	count = 0;
	while (current && current->type == 1)
	{
		if (param)
		{
			current->left_node->left_node->val += current->val - 1;
			current->left_node->right_node->val += current->val - 1;
		}
		if (ft_strncmp(current->right_node->value, "?", 1) == 0)
			param = ft_itoa(data->last_exit_status);
		else
			param = get_env_value(current->right_node->value, data);
		current->right_node->val = ft_strlen(param) - ft_strlen(current->right_node->value);
		current->right_node->value = ft_strdup(param);
		if (count >= 1)
			current->right_node->val += current->val - 1;
		current = current->right_node;
		count++;
	}
	finalize(cmd);
}

char	*update_cmd(int start, int end, char *cmd, char *param)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*final;
	int		len;
	
	i = 0;
	j = 0;
	len = ft_strlen(cmd) + ft_strlen(param) - (end - start);
	final = malloc(sizeof(char) * len);
	while (i < (size_t) start)
	{
		final[i] = cmd[i];
		i++;
	}
	while (j < ft_strlen(param))
		final[i++] = param[j++];
	k = end + 1;
	while (k < ft_strlen(cmd))
		final[i++] = cmd[k++];
	final[i] = '\0';
	return (final);
}

void	finalize(t_node *cmd)
{
	t_node	*current;
	char	*final;
	int		start;
	int		end;
	char	*param;
	
	current = cmd->right_node;
	while (current && current->type == 1)
	{
		start = current->left_node->left_node->val;
		end = current->left_node->right_node->val;
		param = current->right_node->value;
		final = update_cmd(start, end, cmd->left_node->value, param);
		ft_free(cmd->left_node->value);
		cmd->left_node->value = ft_strdup(final);
		ft_free(final);
		current = current->right_node;
	}
	cmd->left_node->value = ft_strdup(final);
	cmd->left_node->id = ft_strdup("FINAL");
}

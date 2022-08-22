/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:17 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/21 17:10:20 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//process the raw node and change id to final

// t_node	*expansion(t_node *args)
// {
// 	t_node	*loc;
// 	t_node	*start;
// 	t_node	*end;
// 	t_node	*param;
// 	int		i;

// 	loc = malloc(sizeof(t_node));
// 	param = malloc(sizeof(t_node));
// 	start = malloc(sizeof(t_node));
// 	end = malloc(sizeof(t_node));
// 	loc->type = 1;
// 	loc->id = ft_strdup("LOCATION");
// 	start->value = ft_strchr(args->value, '$');
// 	start->val = (int)(start->value - args->value);
// 	start->id = ft_strdup("START");
// 	i = 1;
// 	while (ft_isalnum(start->value[i++])
// 		&& start->value[i]
// 		&& start->value[i] != '\"'
// 		&& !ft_isspace(start->value[i]));
// 	// printf("i : %d\n", i);
// 	end->val = start->val + i - 1;
// 	end->id = ft_strdup("END");
// 	param->value = ft_substr(args->value, start->val + 1, i - 1);
// 	param->type = 0;
// 	param->id = ft_strdup("PARAMATER");
// 	loc->left_node = start;
// 	loc->right_node = end;
// 	return (pair_node(loc, param, "EXPANSION"));
// }

void	expander(t_node	*cmd, t_data *data)
{
	char		*param;
	char		*final;
	int			start;
	int			end;
	int			len;
	size_t		i;
	size_t		j;

	if (ft_strncmp(cmd->right_node->right_node->value, "?", 1) == 0)
		param = ft_itoa(data->last_exit_status);
	else
		param = get_env_value(cmd->right_node->right_node->value, data);
	start = cmd->right_node->left_node->left_node->val;
	end = cmd->right_node->left_node->right_node->val;
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
	printf("final: %s\n", final);
	cmd->left_node->value = final;
	cmd->left_node->id = ft_strdup("FINAL");
}

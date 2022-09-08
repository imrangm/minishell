/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:36:54 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/08 07:28:34 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		cmd->left_node->value = final;
		current = current->right_node;
	}
	cmd->left_node->value = final;
	cmd->left_node->id = "FINAL";
}

char	*get_param(char *value, t_data *data)
{
	char	*param;

	if (ft_strncmp(value, "?", 1) == 0)
	{
		param = ft_itoa(data->last_exit_status);
		data->last_exit_status = 0;
	}
	else
		param = get_env_value(value, data);
	return (param);
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
		param = get_param(current->right_node->value, data);
		current->right_node->val = ft_strlen(param)
			- ft_strlen(current->right_node->value);
		ft_free(current->right_node->value);
		current->right_node->value = param;
		if (count >= 1)
			current->right_node->val += current->val - 1;
		current = current->right_node;
		count++;
	}
	finalize(cmd);
}
